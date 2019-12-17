

#include "GUI.h"
#include "main.h"
/********************************************************************
*
*       Static data
*
*********************************************************************
*/

static const char * _acPos[] = {
  "(upper left position)",
  "(lower right position)"
};

/*********************************************************************
*
*       Static code
*
**********************************************************************
*/
/*********************************************************************
*
*       _WaitForPressedState
*
* Function description
*   Waits until the touch is in the given pressed state for at least 250 ms
*/
 void _WaitForPressedState(int Pressed) {
  GUI_PID_STATE State;

  do {
    GUI_TOUCH_GetState(&State);
    GUI_Delay(1);
    if (State.Pressed == Pressed) {
      int TimeStart = GUI_GetTime();
      do {
        GUI_TOUCH_GetState(&State);
        GUI_Delay(1);
        if (State.Pressed != Pressed) {
          break;
        } else if ((GUI_GetTime() - 50) > TimeStart) {
          return;
        }
      } while (1);
    }
  } while (1);
}

/*********************************************************************
*
*       _DispStringCentered
*
* Function description
*   Shows the given text horizontally and vertically centered
*/
static void _DispStringCentered(const char * pString) {
  GUI_RECT Rect;

  Rect.x0 = Rect.y0 = 0;
  Rect.x1 = LCD_GetXSize() - 1;
  Rect.y1 = LCD_GetYSize() - 1;
  GUI_DispStringInRect(pString, &Rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
}

/*********************************************************************
*
*       _GetPhysValues
*
* Function description
*   Asks the user to press the touch screen at the given position
*   and returns the physical A/D values
*/
static void _GetPhysValues(int LogX, int LogY, int * pPhysX, int * pPhysY, const char * pString) {
  char acText[] = "Press here";
  GUI_RECT Rect;
  int FontSizeY;
  int Align;

  FontSizeY = GUI_GetFontSizeY();
  GUI_Clear();
  GUI_SetColor(GUI_BLACK);
  _DispStringCentered("Runtime calibration,\n"
                      "please touch the screen\n"
                      "at the center of the ring."); /* Ask user to press the touch */
  //
  // Calculate the rectangle for the string
  //
  Rect.y0 = LogY - FontSizeY;
  Rect.y1 = LogY + FontSizeY;
  if (LogX < LCD_GetXSize() / 2) {
    Rect.x0 = LogX + 15;
    Rect.x1 = LCD_GetXSize();
    Align = GUI_TA_LEFT;
  } else {
    Rect.x0 = 0;
    Rect.x1 = LogX - 15;
    Align = GUI_TA_RIGHT;
  }
  //
  // Show the text nearby the ring
  //
  GUI_DispStringInRect(acText, &Rect, Align | GUI_TA_TOP);
  GUI_DispStringInRect(pString, &Rect, Align | GUI_TA_BOTTOM);
  //
  // Draw the ring
  //
  GUI_FillCircle(LogX, LogY, 10);
  GUI_SetColor(GUI_WHITE);
  GUI_FillCircle(LogX, LogY, 5);
  GUI_SetColor(GUI_BLACK);
  //
  // Wait until touch is pressed
  //
  _WaitForPressedState(1);
  *pPhysX = GUI_TOUCH_GetxPhys();
  *pPhysY = GUI_TOUCH_GetyPhys();
  //
  // Wait until touch is released
  //
  _WaitForPressedState(0);
}

/********************************************************************
*
*       _Explain
*
* Funtion description
*   Shows a text to give a short explanation of the sample program
*/
static void _Explain(void) {
  _DispStringCentered("Please press the touch\n"
                      "screen to continue...");
  GUI_DispStringHCenterAt("TOUCH_Calibrate", LCD_GetXSize()/2, 5);
	_WaitForPressedState(0);
  _WaitForPressedState(1);
  _WaitForPressedState(0);
}
/*********************************************************************
*
*       Public code
*
**********************************************************************
*/
/*********************************************************************
*
*       MainTask
*/
void calibrate(void) {
  int aPhysX[2], aPhysY[2], aLogX[2], aLogY[2], i;
	GUI_SetBkColor(GUI_WHITE);
  GUI_Clear();
  GUI_SetColor(GUI_BLACK);
  GUI_SetFont(&GUI_Font20_ASCII);
  _Explain();
  // Set the logical values
  aLogX[0] = 15;
  aLogY[0] = 15;
  aLogX[1] = LCD_GetXSize() - 15;
  aLogY[1] = LCD_GetYSize() - 15;
  // Get the physical values of the AD converter for 2 positions 
  for (i = 0; i < 2; i++) {
    _GetPhysValues(aLogX[i], aLogY[i], &aPhysX[i], &aPhysY[i], _acPos[i]);
  }
  // Use the physical values to calibrate the touch screen 
   ParSave.Calib.top = aPhysY[1];
	ParSave.Calib.bottom = aPhysY[0];
	ParSave.Calib.left = aPhysX[1];
	ParSave.Calib.right = aPhysX[0];	
  GUI_TOUCH_Calibrate(0, aLogX[0], aLogX[1], aPhysX[0], aPhysX[1]); // Calibrate X-axis 
  GUI_TOUCH_Calibrate(1, aLogY[0], aLogY[1], aPhysY[0], aPhysY[1]); // Calibrate Y-axis 
  GUI_Clear(); 
  Ones[save].delay = 300;
}
