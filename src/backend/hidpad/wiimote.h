/*
* This file is part of iMAME4all.
*
* Copyright (C) 2010 David Valdeita (Seleuco)
*
* based on:
*
*  wiiuse
*
* Written By:
*    Michael Laforest  < para >
*    Email: < thepara (--AT--) g m a i l [--DOT--] com >
*
* Copyright 2006-2007
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
*
* In addition, as a special exception, Seleuco
* gives permission to link the code of this program with
* the MAME library (or with modified versions of MAME that use the
* same license as MAME), and distribute linked combinations including
* the two.  You must obey the GNU General Public License in all
* respects for all of the code used other than MAME.  If you modify
* this file, you may extend this exception to your version of the
* file, but you are not obligated to do so.  If you do not wish to
* do so, delete this exception statement from your version.
*/

#ifndef __WIIMOTE_H__
#define __WIIMOTE_H__

#include "HIDManager.h"

typedef unsigned char byte;
typedef char sbyte;

/* Convert to big endian */
#define BIG_ENDIAN_LONG(i)                   (htonl(i))
#define BIG_ENDIAN_SHORT(i)                  (htons(i))

#define absf(x)                              ((x >= 0) ? (x) : (x * -1.0f))
#define diff_f(x, y)                         ((x >= y) ? (absf(x - y)) : (absf(y - x)))

/* wiimote state flags*/
#define WIIMOTE_STATE_DEV_FOUND              0x0001
#define WIIMOTE_STATE_HANDSHAKE              0x0002   /* actual connection exists but no handshake yet */
#define WIIMOTE_STATE_HANDSHAKE_COMPLETE     0x0004
#define WIIMOTE_STATE_CONNECTED              0x0008
#define WIIMOTE_STATE_EXP                   0x0040

/* Communication channels */

#define WM_SET_REPORT                        0x50

/* commands */
#define WM_CMD_LED                           0x11
#define WM_CMD_REPORT_TYPE                   0x12
#define WM_CMD_RUMBLE                        0x13
#define WM_CMD_IR                            0x13
#define WM_CMD_CTRL_STATUS                   0x15
#define WM_CMD_WRITE_DATA                    0x16
#define WM_CMD_READ_DATA                     0x17
#define WM_CMD_IR_2                          0x1A

/* input report ids */
#define WM_RPT_CTRL_STATUS                   0x20
#define WM_RPT_READ                          0x21
#define WM_RPT_WRITE                         0x22
#define WM_RPT_BTN                           0x30
#define WM_RPT_BTN_ACC                       0x31
#define WM_RPT_BTN_ACC_IR                    0x33
#define WM_RPT_BTN_EXP                       0x34
#define WM_RPT_BTN_ACC_EXP                   0x35
#define WM_RPT_BTN_IR_EXP                    0x36
#define WM_RPT_BTN_ACC_IR_EXP                0x37

#define WM_BT_INPUT                         0x01
#define WM_BT_OUTPUT                        0x02

/* controller status stuff */
#define WM_MAX_BATTERY_CODE                  0xC8

#define EXP_ID_CODE_CLASSIC_CONTROLLER      0x9A1EFDFD

/* offsets in wiimote memory */
#define WM_MEM_OFFSET_CALIBRATION            0x16
#define WM_EXP_MEM_BASE                      0x04A40000
#define WM_EXP_MEM_ENABLE                    0x04A40040
#define WM_EXP_MEM_CALIBR                    0x04A40020

#define EXP_HANDSHAKE_LEN                   224

/* controller status flags for the first message byte */
/* bit 1 is unknown */
#define WM_CTRL_STATUS_BYTE1_ATTACHMENT      0x02
#define WM_CTRL_STATUS_BYTE1_SPEAKER_ENABLED 0x04
#define WM_CTRL_STATUS_BYTE1_IR_ENABLED      0x08
#define WM_CTRL_STATUS_BYTE1_LED_1           0x10
#define WM_CTRL_STATUS_BYTE1_LED_2           0x20
#define WM_CTRL_STATUS_BYTE1_LED_3           0x40
#define WM_CTRL_STATUS_BYTE1_LED_4           0x80

/* led bit masks */
#define WIIMOTE_LED_NONE                     0x00
#define WIIMOTE_LED_1                        0x10
#define WIIMOTE_LED_2                        0x20
#define WIIMOTE_LED_3                        0x40
#define WIIMOTE_LED_4                        0x80

/* button masks */
#define WIIMOTE_BUTTON_TWO                  0x0001
#define WIIMOTE_BUTTON_ONE                  0x0002
#define WIIMOTE_BUTTON_B                    0x0004
#define WIIMOTE_BUTTON_A                    0x0008
#define WIIMOTE_BUTTON_MINUS                0x0010
#define WIIMOTE_BUTTON_ZACCEL_BIT6          0x0020
#define WIIMOTE_BUTTON_ZACCEL_BIT7          0x0040
#define WIIMOTE_BUTTON_HOME                 0x0080
#define WIIMOTE_BUTTON_LEFT                 0x0100
#define WIIMOTE_BUTTON_RIGHT                0x0200
#define WIIMOTE_BUTTON_DOWN                 0x0400
#define WIIMOTE_BUTTON_UP                   0x0800
#define WIIMOTE_BUTTON_PLUS                 0x1000
#define WIIMOTE_BUTTON_ALL                   0x1F9F

#define CLASSIC_CTRL_BUTTON_UP			0x0001
#define CLASSIC_CTRL_BUTTON_LEFT		0x0002
#define CLASSIC_CTRL_BUTTON_ZR			0x0004
#define CLASSIC_CTRL_BUTTON_X			0x0008
#define CLASSIC_CTRL_BUTTON_A			0x0010
#define CLASSIC_CTRL_BUTTON_Y			0x0020
#define CLASSIC_CTRL_BUTTON_B			0x0040
#define CLASSIC_CTRL_BUTTON_ZL			0x0080
#define CLASSIC_CTRL_BUTTON_FULL_R		0x0200
#define CLASSIC_CTRL_BUTTON_PLUS		0x0400
#define CLASSIC_CTRL_BUTTON_HOME		0x0800
#define CLASSIC_CTRL_BUTTON_MINUS		0x1000
#define CLASSIC_CTRL_BUTTON_FULL_L		0x2000
#define CLASSIC_CTRL_BUTTON_DOWN		0x4000
#define CLASSIC_CTRL_BUTTON_RIGHT		0x8000

#define CLASSIC_CTRL_BUTTON_ALL              0xFEFF

/* expansion codes */
#define EXP_NONE                             0
#define EXP_CLASSIC                          2

typedef struct axis_t
{
    bool initialized;
    int32_t calibration[4];
    
    float value;
}   axis_t;

typedef struct joystick_t
{
    axis_t x;
    axis_t y;
}   joystick_t;

typedef struct classic_ctrl_t
{
    short btns;
    struct joystick_t ljs;
    struct joystick_t rjs;
}   classic_ctrl_t;

typedef struct expansion_t
{
    int type;

    union
    {
        struct classic_ctrl_t classic;
    };
}   expansion_t;

typedef struct wiimote_t
{
    int unid;

    HIDManager::Connection* connection;
    int state;
    byte leds;
    float battery_level;

    byte handshake_state;

    struct expansion_t exp;

    unsigned short btns;
} wiimote;

/* macro to manage states */
#define WIIMOTE_IS_SET(wm, s)          ((wm->state & (s)) == (s))
#define WIIMOTE_ENABLE_STATE(wm, s)    (wm->state |= (s))
#define WIIMOTE_DISABLE_STATE(wm, s)   (wm->state &= ~(s))
#define WIIMOTE_TOGGLE_STATE(wm, s)    ((wm->state & (s)) ? WIIMOTE_DISABLE_STATE(wm, s) : WIIMOTE_ENABLE_STATE(wm, s))
#define WIIMOTE_IS_CONNECTED(wm)       (WIIMOTE_IS_SET(wm, WIIMOTE_STATE_CONNECTED))

int  wiimote_handshake(struct wiimote_t* wm,  byte event, byte* data, unsigned short len);
void wiimote_status(struct wiimote_t* wm);
void wiimote_set_leds(struct wiimote_t* wm, int leds);
void wiimote_data_report(struct wiimote_t* wm, byte type);
void wiimote_pressed_buttons(struct wiimote_t* wm, byte* msg);
void wiimote_handle_expansion(struct wiimote_t* wm, byte* msg);



#endif
