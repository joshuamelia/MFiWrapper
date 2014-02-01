/*  MFiWrapper
 *  Copyright (C) 2014 - Jason Fetters
 * 
 *  MFiWrapper is free software: you can redistribute it and/or modify it under the terms
 *  of the GNU General Public License as published by the Free Software Found-
 *  ation, either version 3 of the License, or (at your option) any later version.
 *
 *  MFiWrapper is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
 *  without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
 *  PURPOSE.  See the GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along with MFiWrapper.
 *  If not, see <http://www.gnu.org/licenses/>.
 */

#import <CoreFoundation/CoreFoundation.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <map>

#include "HIDManager.h"
#include "HIDPad.h"

#include "backend.h"
#include "protocol.h"
#include "common.h"

namespace MFiWrapperBackend {

static uint32_t nextHandle = 1;
static std::map<HIDPad::Interface*, uint32_t> devices;
static pthread_t thread;
static int sockets[2] = { -1, -1 };

class BackendConnection : public MFiWrapperCommon::Connection
{
    public:
        BackendConnection(int aDescriptor) : MFiWrapperCommon::Connection(aDescriptor) { };
        
        HIDPad::Interface* FindDeviceByHandle(uint32_t aHandle)
        {
            for (auto i = devices.begin(); i != devices.end(); i ++)
                if (i->second == aHandle)
                    return i->first;
            return 0;
        }
        
        void HandlePacket(const MFiWDataPacket* aPacket)
        {
            switch(aPacket->Type)
            {
                case MFiWPacketStartDiscovery:
                    HIDManager::StartDeviceProbe();
                    return;
                
                case MFiWPacketStopDiscovery:
                    HIDManager::StopDeviceProbe();
                    return;
                
                case MFiWPacketSetPlayerIndex:
                {
                    HIDPad::Interface* device = FindDeviceByHandle(aPacket->Handle);
                    if (device)
                        device->SetPlayerIndex(aPacket->PlayerIndex.Value);
                    return;
                }
                
                default:
                    printf("Unkown packet set to backend: %d\n", aPacket->Type);
                    return;
            }        
        }
};

BackendConnection* connection;

static void* ManagerThread(void* aUnused)
{
    connection = new BackendConnection(sockets[0]);

    HIDManager::StartUp();    
    CFRunLoopRun();
    HIDManager::ShutDown();
    
    return 0;
}

void AttachController(HIDPad::Interface* aInterface)
{
    if (devices.find(aInterface) == devices.end())
    {
        uint32_t handle = nextHandle ++;
        devices[aInterface] = handle;

        MFiWConnectPacket pkt;
        memset(&pkt, 0, sizeof(pkt));
        strlcpy(pkt.VendorName, aInterface->GetVendorName(), sizeof(pkt.VendorName));
        pkt.PresentControls = aInterface->GetPresentControls();
        pkt.AnalogControls = aInterface->GetAnalogControls();
        connection->SendConnect(handle, &pkt);
    }
}

void DetachController(HIDPad::Interface* aInterface)
{
    std::map<HIDPad::Interface*, uint32_t>::iterator device;
    if ((device = devices.find(aInterface)) != devices.end())
    {
        uint32_t handle = device->second;
        devices.erase(device);
     
        connection->SendDisconnect(handle);
    }
}

void SendControllerState(HIDPad::Interface* aInterface, const MFiWInputStatePacket* aData)
{
    std::map<HIDPad::Interface*, uint32_t>::iterator device;
    if ((device = devices.find(aInterface)) != devices.end())
    {
        uint32_t handle = device->second;
        connection->SendInputState(handle, aData);
    }
}

void SendPausePressed(HIDPad::Interface* aInterface)
{
    std::map<HIDPad::Interface*, uint32_t>::iterator device;
    if ((device = devices.find(aInterface)) != devices.end())
    {
        uint32_t handle = device->second;
        connection->SendPausePressed(handle);
    }
}

}

int HACKStart()
{
    using namespace MFiWrapperBackend;

    if (!thread)
    {
        socketpair(PF_LOCAL, SOCK_STREAM, 0, sockets);
        pthread_create(&thread, 0, ManagerThread, 0);
    }
    
    return sockets[1];
}
