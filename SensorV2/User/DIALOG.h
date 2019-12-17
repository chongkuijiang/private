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

#define ID_FRAMEWIN              (GUI_ID_USER + 0x0A)
#define ID_BUTTON_SET            (GUI_ID_USER + 0x0B)
#define ID_BUTTON_LOCK           (GUI_ID_USER + 0x0C)

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

#define ID_TEXT_ID0               (GUI_ID_USER + 0x20)
#define ID_TEXT_PV0               (GUI_ID_USER + 0x21)
#define ID_TEXT_SW0               (GUI_ID_USER + 0x22)
#define ID_BUTTON_SW0             (GUI_ID_USER + 0x23)
#define ID_BUTTON_UP0             (GUI_ID_USER + 0x24)
#define ID_BUTTON_DOWN0           (GUI_ID_USER + 0x25)
#define ID_TEXT_K0                (GUI_ID_USER + 0x26)

#define ID_TEXT_ID1               (GUI_ID_USER + 0x30)
#define ID_TEXT_PV1               (GUI_ID_USER + 0x31)
#define ID_TEXT_SW1               (GUI_ID_USER + 0x32)
#define ID_BUTTON_SW1             (GUI_ID_USER + 0x33)
#define ID_BUTTON_UP1             (GUI_ID_USER + 0x34)
#define ID_BUTTON_DOWN1           (GUI_ID_USER + 0x35)
#define ID_TEXT_K1                (GUI_ID_USER + 0x36)

#define ID_TEXT_ID2               (GUI_ID_USER + 0x40)
#define ID_TEXT_PV2               (GUI_ID_USER + 0x41)
#define ID_TEXT_SW2               (GUI_ID_USER + 0x42)
#define ID_BUTTON_SW2             (GUI_ID_USER + 0x43)
#define ID_BUTTON_UP2             (GUI_ID_USER + 0x44)
#define ID_BUTTON_DOWN2           (GUI_ID_USER + 0x45)
#define ID_TEXT_K2                (GUI_ID_USER + 0x46)

#define ID_TEXT_ID3               (GUI_ID_USER + 0x50)
#define ID_TEXT_PV3               (GUI_ID_USER + 0x51)
#define ID_TEXT_SW3               (GUI_ID_USER + 0x52)
#define ID_BUTTON_SW3             (GUI_ID_USER + 0x53)
#define ID_BUTTON_UP3             (GUI_ID_USER + 0x54)
#define ID_BUTTON_DOWN3           (GUI_ID_USER + 0x55)
#define ID_TEXT_K3                (GUI_ID_USER + 0x56)

#define ID_TEXT_ID4               (GUI_ID_USER + 0x60)
#define ID_TEXT_PV4               (GUI_ID_USER + 0x61)
#define ID_TEXT_SW4               (GUI_ID_USER + 0x62)
#define ID_BUTTON_SW4             (GUI_ID_USER + 0x63)
#define ID_BUTTON_UP4             (GUI_ID_USER + 0x64)
#define ID_BUTTON_DOWN4           (GUI_ID_USER + 0x65)
#define ID_TEXT_K4                (GUI_ID_USER + 0x66)

#define ID_TEXT_ID5               (GUI_ID_USER + 0x70)
#define ID_TEXT_PV5               (GUI_ID_USER + 0x71)
#define ID_TEXT_SW5               (GUI_ID_USER + 0x72)
#define ID_BUTTON_SW5             (GUI_ID_USER + 0x73)
#define ID_BUTTON_UP5             (GUI_ID_USER + 0x74)
#define ID_BUTTON_DOWN5           (GUI_ID_USER + 0x75)
#define ID_TEXT_K5                (GUI_ID_USER + 0x76)

#define ID_TEXT_ID6               (GUI_ID_USER + 0x80)
#define ID_TEXT_PV6               (GUI_ID_USER + 0x81)
#define ID_TEXT_SW6               (GUI_ID_USER + 0x82)
#define ID_BUTTON_SW6             (GUI_ID_USER + 0x83)
#define ID_BUTTON_UP6             (GUI_ID_USER + 0x84)
#define ID_BUTTON_DOWN6           (GUI_ID_USER + 0x85)
#define ID_TEXT_K6                (GUI_ID_USER + 0x86)

#define ID_TEXT_ID7               (GUI_ID_USER + 0x90)
#define ID_TEXT_PV7               (GUI_ID_USER + 0x91)
#define ID_TEXT_SW7               (GUI_ID_USER + 0x92)
#define ID_BUTTON_SW7             (GUI_ID_USER + 0x93)
#define ID_BUTTON_UP7             (GUI_ID_USER + 0x94)
#define ID_BUTTON_DOWN7           (GUI_ID_USER + 0x95)
#define ID_TEXT_K7                (GUI_ID_USER + 0x96)

#define ID_TEXT_JK                (GUI_ID_USER + 0xA0)
#define ID_RADIO_0             (GUI_ID_USER + 0xA1)
#define ID_BUTTON_Ex              (GUI_ID_USER + 0xA2)

#define ID_WINDOW_SET      (GUI_ID_USER + 0xA3)
#define ID_TEXT_TITLE0     (GUI_ID_USER + 0xA4)
#define ID_TEXT_TITLE1     (GUI_ID_USER + 0xA5)
#define ID_TEXT_TITLE2     (GUI_ID_USER + 0xA6)
#define ID_TEXT_TITLE3     (GUI_ID_USER + 0xA7)
#define ID_TEXT_TITLE4     (GUI_ID_USER + 0xA8)
#define ID_TEXT_TITLE5     (GUI_ID_USER + 0xA9)
#define ID_TEXT_TITLE6     (GUI_ID_USER + 0xAA)
#define ID_TEXT_TITLE7     (GUI_ID_USER + 0xAB)
#define ID_TEXT_TITLE8     (GUI_ID_USER + 0xAC)
#define ID_BUTTON_SET0     (GUI_ID_USER + 0xAD)
#define ID_BUTTON_SET1     (GUI_ID_USER + 0xAE)
#define ID_BUTTON_SET2     (GUI_ID_USER + 0xAF)
#define ID_BUTTON_SET3     (GUI_ID_USER + 0xB0)
#define ID_BUTTON_SET4     (GUI_ID_USER + 0xB1)
#define ID_BUTTON_SET5     (GUI_ID_USER + 0xB2)
#define ID_BUTTON_SET6     (GUI_ID_USER + 0xB3)
#define ID_BUTTON_SET7     (GUI_ID_USER + 0xB4)
#define ID_BUTTON_SET8     (GUI_ID_USER + 0xB5)
#define ID_BUTTON_SET9     (GUI_ID_USER + 0xB6)
#define ID_BUTTON_SET10    (GUI_ID_USER + 0xB7)
#define ID_BUTTON_SET11    (GUI_ID_USER + 0xB8)

#define ID_RADIO_SET0      (GUI_ID_USER + 0xB9)
#define ID_RADIO_SET1      (GUI_ID_USER + 0xBA)
#define ID_RADIO_SET2      (GUI_ID_USER + 0xBB)
#define ID_RADIO_SET3      (GUI_ID_USER + 0xBC)
#define ID_RADIO_SET4      (GUI_ID_USER + 0xBD)
#define ID_RADIO_SET5      (GUI_ID_USER + 0xBE)
#define ID_RADIO_SET6      (GUI_ID_USER + 0xBF)
#define ID_RADIO_SET7      (GUI_ID_USER + 0xC0)
#define ID_TEXT_SETPV0     (GUI_ID_USER + 0xC1)
#define ID_TEXT_SETPV1     (GUI_ID_USER + 0xC2)
#define ID_TEXT_SETPV2     (GUI_ID_USER + 0xC3)
#define ID_TEXT_SETPV3     (GUI_ID_USER + 0xC4)
#define ID_TEXT_SETPV4     (GUI_ID_USER + 0xC5)
#define ID_TEXT_SETPV5     (GUI_ID_USER + 0xC6)
#define ID_TEXT_SETPV6     (GUI_ID_USER + 0xC7)
#define ID_TEXT_SETPV7     (GUI_ID_USER + 0xC8)
#define ID_TEXT_SETPV8     (GUI_ID_USER + 0xC9)
#define ID_TEXT_TXTPV0     (GUI_ID_USER + 0xCA)
#define ID_TEXT_TXTPV1     (GUI_ID_USER + 0xCB)
#define ID_TEXT_TXTPV2     (GUI_ID_USER + 0xCC)
#define ID_TEXT_TXTPV3     (GUI_ID_USER + 0xCD)
#define ID_TEXT_TXTPV4     (GUI_ID_USER + 0xCE)
#define ID_TEXT_TXTPV5     (GUI_ID_USER + 0xCF)
#define ID_TEXT_TXTPV6     (GUI_ID_USER + 0xD0)
#define ID_TEXT_TXTPV7     (GUI_ID_USER + 0xD1)
#define ID_TEXT_TXTPV8     (GUI_ID_USER + 0xD2)
#define ID_EDIT_SET0       (GUI_ID_USER + 0xD3)
#define ID_EDIT_SET1       (GUI_ID_USER + 0xD4)
#define ID_EDIT_SET2       (GUI_ID_USER + 0xD5)
#define ID_EDIT_SET3       (GUI_ID_USER + 0xD6)
#define ID_EDIT_SET4       (GUI_ID_USER + 0xD7)
#define ID_EDIT_SET5       (GUI_ID_USER + 0xD8)
#define ID_EDIT_SET6       (GUI_ID_USER + 0xD9)
#define ID_EDIT_SET7       (GUI_ID_USER + 0xDA)
#define ID_EDIT_SET8       (GUI_ID_USER + 0xDB)

#define ID_BUTTON_OK       (GUI_ID_USER + 0xDC)


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
	U16  SV01;
	U8   jk;
	U8   cf;
	U8  alarm;
	U8  on_off;
}TEMPERATURE;
typedef struct
{  	
    int   x0;
    int   y0;
    int   xsize; 
    int   ysize;	
	WM_HWIN  _hFrame;
	WM_CALLBACK* pOldFrame;	
	GUI_RECT  Rect;
    int sw,distance;
}Frame_t;

extern U16 reDraw,graph,winId;
extern WM_HWIN hFrame,hWin,hEnv,hGraph,hSeting;
extern TEMPERATURE temperature[8];
extern Frame_t   Frame;
extern U8 locked;

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
void CreateSetOfs(void);
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
