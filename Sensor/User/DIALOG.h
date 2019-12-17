/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.28 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : Dialog.h
Purpose     : Dialog box include
--------------------END-OF-HEADER-------------------------------------
*/

#ifndef DIALOG_H
#define DIALOG_H

#include "WM.h"
#include "BUTTON.h"
#include "CALENDAR.h"
#include "CHECKBOX.h"
#include "CHOOSECOLOR.h"
#include "CHOOSEFILE.h"
#include "DROPDOWN.h"
#include "EDIT.h"
#include "FRAMEWIN.h"
#include "GRAPH.h"
#include "HEADER.h"
#include "ICONVIEW.h"
#include "IMAGE.h"
#include "LISTBOX.h"
#include "LISTVIEW.h"
#include "LISTWHEEL.h"
#include "MENU.h"
#include "MULTIEDIT.h"
#include "MULTIPAGE.h"
#include "PROGBAR.h"
#include "RADIO.h"
#include "SCROLLBAR.h"
#include "SLIDER.h"
#include "SPINBOX.h"
#include "TEXT.h"
#include "TREEVIEW.h"
#include "KNOB.h"
//----------------------------------------------------------------------
#define ID_WINDOW_0              (GUI_ID_USER + 0x00)
#define ID_BUTTON_0              (GUI_ID_USER + 0x01)
#define ID_BUTTON_1              (GUI_ID_USER + 0x02)
#define ID_BUTTON_2              (GUI_ID_USER + 0x03)
#define ID_BUTTON_3              (GUI_ID_USER + 0x04)
#define ID_BUTTON_4              (GUI_ID_USER + 0x05)
#define ID_WINTEXT_0             (GUI_ID_USER + 0x06)

#define ID_FRAMEWIN              (GUI_ID_USER + 0x0F)

#define ID_FRAMEKEY              (GUI_ID_USER + 0x10)
#define ID_EDIT_KEY0             (GUI_ID_USER + 0x11)
#define ID_BUTTON_KEY0           (GUI_ID_USER + 0x12)
#define ID_BUTTON_KEY1           (GUI_ID_USER + 0x13)
#define ID_BUTTON_KEY2           (GUI_ID_USER + 0x14)
#define ID_BUTTON_KEY3           (GUI_ID_USER + 0x15)
#define ID_BUTTON_KEY4           (GUI_ID_USER + 0x16)
#define ID_BUTTON_KEY5           (GUI_ID_USER + 0x17)
#define ID_BUTTON_KEY6           (GUI_ID_USER + 0x18)
#define ID_BUTTON_KEY7           (GUI_ID_USER + 0x19)
#define ID_BUTTON_KEY8           (GUI_ID_USER + 0x1A)
#define ID_BUTTON_KEY9           (GUI_ID_USER + 0x1B)
#define ID_BUTTON_KEY10          (GUI_ID_USER + 0x1C)
#define ID_BUTTON_KEY11          (GUI_ID_USER + 0x1D)
#define ID_BUTTON_KEY12          (GUI_ID_USER + 0x1E)
#define ID_BUTTON_KEY13          (GUI_ID_USER + 0x1F)

#define ID_TEXT_A0                (GUI_ID_USER + 0x20)
#define ID_EDIT_A0                (GUI_ID_USER + 0x21)
#define ID_TEXT_A1                (GUI_ID_USER + 0x22)
#define ID_TEXT_A2                (GUI_ID_USER + 0x23)
#define ID_TEXT_A3                (GUI_ID_USER + 0x24)
#define ID_EDIT_A1                (GUI_ID_USER + 0x25)
#define ID_BUTTON_A               (GUI_ID_USER + 0x26)
#define ID_TEXT_A5                (GUI_ID_USER + 0x27)
#define ID_TEXT_A6                (GUI_ID_USER + 0x28)
#define ID_TEXT_A7                (GUI_ID_USER + 0x29)
#define ID_TEXT_A4                (GUI_ID_USER + 0x2A)

#define ID_TEXT_B0                (GUI_ID_USER + 0x30)
#define ID_EDIT_B0                (GUI_ID_USER + 0x31)
#define ID_TEXT_B1                (GUI_ID_USER + 0x32)
#define ID_TEXT_B2                (GUI_ID_USER + 0x33)
#define ID_TEXT_B3                (GUI_ID_USER + 0x34)
#define ID_EDIT_B1                (GUI_ID_USER + 0x35)
#define ID_BUTTON_B               (GUI_ID_USER + 0x36)
#define ID_TEXT_B5                (GUI_ID_USER + 0x37)
#define ID_TEXT_B6                (GUI_ID_USER + 0x38)
#define ID_TEXT_B7                (GUI_ID_USER + 0x39)
#define ID_TEXT_B4                (GUI_ID_USER + 0x3A)

#define ID_TEXT_C0                (GUI_ID_USER + 0x40)
#define ID_EDIT_C0                (GUI_ID_USER + 0x41)
#define ID_TEXT_C1                (GUI_ID_USER + 0x42)
#define ID_TEXT_C2                (GUI_ID_USER + 0x43)
#define ID_TEXT_C3                (GUI_ID_USER + 0x44)
#define ID_EDIT_C1                (GUI_ID_USER + 0x45)
#define ID_BUTTON_C               (GUI_ID_USER + 0x46)
#define ID_TEXT_C5                (GUI_ID_USER + 0x47)
#define ID_TEXT_C6                (GUI_ID_USER + 0x48)
#define ID_TEXT_C7                (GUI_ID_USER + 0x49)
#define ID_TEXT_C4                (GUI_ID_USER + 0x4A)

#define ID_TEXT_D0                (GUI_ID_USER + 0x50)
#define ID_EDIT_D0                (GUI_ID_USER + 0x51)
#define ID_TEXT_D1                (GUI_ID_USER + 0x52)
#define ID_TEXT_D2                (GUI_ID_USER + 0x53)
#define ID_TEXT_D3                (GUI_ID_USER + 0x54)
#define ID_EDIT_D1                (GUI_ID_USER + 0x55)
#define ID_BUTTON_D               (GUI_ID_USER + 0x56)
#define ID_TEXT_D5                (GUI_ID_USER + 0x57)
#define ID_TEXT_D6                (GUI_ID_USER + 0x58)
#define ID_TEXT_D7                (GUI_ID_USER + 0x59)
#define ID_TEXT_D4                (GUI_ID_USER + 0x5A)

#define ID_TEXT_E0                (GUI_ID_USER + 0x60)
#define ID_EDIT_E0                (GUI_ID_USER + 0x61)
#define ID_TEXT_E1                (GUI_ID_USER + 0x62)
#define ID_TEXT_E2                (GUI_ID_USER + 0x63)
#define ID_TEXT_E3                (GUI_ID_USER + 0x64)
#define ID_EDIT_E1                (GUI_ID_USER + 0x65)
#define ID_BUTTON_E               (GUI_ID_USER + 0x66)
#define ID_TEXT_E5                (GUI_ID_USER + 0x67)
#define ID_TEXT_E6                (GUI_ID_USER + 0x68)
#define ID_TEXT_E7                (GUI_ID_USER + 0x69)
#define ID_TEXT_E4                (GUI_ID_USER + 0x6A)

#define ID_TEXT_F0                (GUI_ID_USER + 0x70)
#define ID_EDIT_F0                (GUI_ID_USER + 0x71)
#define ID_TEXT_F1                (GUI_ID_USER + 0x72)
#define ID_TEXT_F2                (GUI_ID_USER + 0x73)
#define ID_TEXT_F3                (GUI_ID_USER + 0x74)
#define ID_EDIT_F1                (GUI_ID_USER + 0x75)
#define ID_BUTTON_F               (GUI_ID_USER + 0x76)
#define ID_TEXT_F5                (GUI_ID_USER + 0x77)
#define ID_TEXT_F6                (GUI_ID_USER + 0x78)
#define ID_TEXT_F7                (GUI_ID_USER + 0x79)
#define ID_TEXT_F4                (GUI_ID_USER + 0x7A)

#define ID_TEXT_G0                (GUI_ID_USER + 0x80)
#define ID_EDIT_G0                (GUI_ID_USER + 0x81)
#define ID_TEXT_G1                (GUI_ID_USER + 0x82)
#define ID_TEXT_G2                (GUI_ID_USER + 0x83)
#define ID_TEXT_G3                (GUI_ID_USER + 0x84)
#define ID_EDIT_G1                (GUI_ID_USER + 0x85)
#define ID_BUTTON_G               (GUI_ID_USER + 0x86)
#define ID_TEXT_G5                (GUI_ID_USER + 0x87)
#define ID_TEXT_G6                (GUI_ID_USER + 0x88)
#define ID_TEXT_G7                (GUI_ID_USER + 0x89)
#define ID_TEXT_G4                (GUI_ID_USER + 0x8A)

#define ID_TEXT_H0                (GUI_ID_USER + 0x90)
#define ID_EDIT_H0                (GUI_ID_USER + 0x91)
#define ID_TEXT_H1                (GUI_ID_USER + 0x92)
#define ID_TEXT_H2                (GUI_ID_USER + 0x93)
#define ID_TEXT_H3                (GUI_ID_USER + 0x94)
#define ID_EDIT_H1                (GUI_ID_USER + 0x95)
#define ID_BUTTON_H               (GUI_ID_USER + 0x96)
#define ID_TEXT_H5                (GUI_ID_USER + 0x97)
#define ID_TEXT_H6                (GUI_ID_USER + 0x98)
#define ID_TEXT_H7                (GUI_ID_USER + 0x99)
#define ID_TEXT_H4                (GUI_ID_USER + 0x9A)

#define ID_TEXT_JK                (GUI_ID_USER + 0xA0)
#define ID_RADIO_0             (GUI_ID_USER + 0xA1)
#define ID_BUTTON_Ex              (GUI_ID_USER + 0xA2)


#define KEY_MSG                (WM_USER + 0x00)
#define UPDATA_DLG             (WM_USER + 0x01)
#define UPDATA_WIN             (WM_USER + 0x02)
#define UPDATA_KEY             (WM_USER + 0x03)

//----------------------------------------------------------------------
#define MAG         2
#define  countof(Obj) (sizeof(Obj) / sizeof(Obj[0]))
	
typedef struct {  
	U16  x0;
	U16  y0;
	U16  *PV;
	U16  *SV;
	U8  *cf;
	U8  *alarm;
    GUI_AUTODEV_INFO AutoDevInfo;  // Information about what has to be displayed
    GUI_POINT        aPoints[5];   // Polygon data
    float  Angle;
				
}PARAM;
//----------------------------------------------------------------------
typedef struct {
	U16  key;
	U16  value;
}KEY_VALUE;
//----------------------------------------------------------------------
typedef struct {
	U16  PV10;
	U16  SV10;
	U8   jk;
	U8   cf;
	U8  alarm;
}TEMPERATURE;


extern U16 reDraw,graph,winId;
extern WM_HWIN hFrame,hWin,hEnv,hGraph,hSeting;
extern TEMPERATURE temperature[8];
extern U16 Env;

extern const GUI_POINT _aNeedle[];
extern GUI_AUTODEV aAuto[8];
extern PARAM       Param[8];
void DrawPanel(U16 x0,U16 y0);
void _DrawPanel(void * p);
void dispTemPanel(void);
void dispTemGraph(void);
void dspWinIndex(U8 x);
char* int2Text(int data);
void calibrate(void);
void CreateKeyBoard(WM_HWIN hParent,int x0,int y0,int keyindex,int value);
void CreateWindow(void);
void Creategraph(void);
//---------------------------------------------------------------------------
#if GUI_WINSUPPORT

#if defined(__cplusplus)
  extern "C" {     /* Make sure we have C-declarations in C++ programs */
#endif

/*********************************************************************
*
*       WINDOW API
*/
WM_HWIN   WINDOW_CreateEx         (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, WM_CALLBACK * cb);
WM_HWIN   WINDOW_CreateUser       (int x0, int y0, int xSize, int ySize, WM_HWIN hParent, int WinFlags, int ExFlags, int Id, WM_CALLBACK * cb, int NumExtraBytes);
WM_HWIN   WINDOW_CreateIndirect   (const GUI_WIDGET_CREATE_INFO * pCreateInfo, WM_HWIN hWinParent, int x0, int y0, WM_CALLBACK * cb);
GUI_COLOR WINDOW_GetDefaultBkColor(void);
int       WINDOW_GetUserData      (WM_HWIN hObj, void * pDest, int NumBytes);
void      WINDOW_SetBkColor       (WM_HWIN hObj, GUI_COLOR Color);
void      WINDOW_SetDefaultBkColor(GUI_COLOR Color);
int       WINDOW_SetUserData      (WM_HWIN hObj, const void * pSrc, int NumBytes);

void WINDOW_Callback(WM_MESSAGE * pMsg);

#if defined(__cplusplus)
  }
#endif

#endif  // GUI_WINSUPPORT
#endif  // DIALOG_H


/*************************** End of file ****************************/
