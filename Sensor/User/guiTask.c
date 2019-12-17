#include "GUI.h"
#include "DIALOG.h"
//#include "stm32f1xx_hal.h"
#include <math.h>
#include <stdio.h>
#include "LCD_MD070SD.h" 

//----------------------------------------------------------------

void DspLogo(void);
void calibrate(void);
void DspABIDO(void);


  U16 reDraw,graph,winId;
  WM_HWIN hFrame,hWin,hEnv,hGraph,hSeting;
  TEMPERATURE temperature[8];
  U16 Env;
  GUI_AUTODEV aAuto[8];
  PARAM  Param[8] = {  //X0,Y0,PV,SV,CF,ALARM
	    {2,32,&temperature[0].PV10,&temperature[0].SV10,&temperature[0].cf,&temperature[0].alarm},  
        {181,32,&temperature[1].PV10,&temperature[1].SV10,&temperature[1].cf,&temperature[1].alarm},  
        {360,32,&temperature[2].PV10,&temperature[2].SV10,&temperature[2].cf,&temperature[2].alarm},  
        {539,32,&temperature[3].PV10,&temperature[3].SV10,&temperature[3].cf,&temperature[3].alarm},
	    {2,255,&temperature[4].PV10,&temperature[4].SV10,&temperature[4].cf,&temperature[4].alarm},
        {181,255,&temperature[5].PV10,&temperature[5].SV10,&temperature[5].cf,&temperature[5].alarm},
        {360,255,&temperature[6].PV10,&temperature[6].SV10,&temperature[6].cf,&temperature[6].alarm},
        {539,255,&temperature[7].PV10,&temperature[7].SV10,&temperature[7].cf,&temperature[7].alarm},
  };
 const GUI_POINT _aNeedle[] = {
	{ MAG*0, MAG*3},
	{MAG*56, MAG*1},
	{MAG*65, MAG*0},
	{MAG*56, MAG*-1},
	{MAG*0,  MAG*-3}
};
//----------------------------------------------------------------
void drawTite(void)
{
	GUI_SetColor(GUI_LIGHTGRAY);
    GUI_FillRect(0, 0, 720,35);
	GUI_FillRect(0, 0, 3,480);
    GUI_FillRect(0, 477,720,480);
	GUI_FillRect(717, 0, 720,480);
	GUI_SetFont(GUI_FONT_32B_1);
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetColor(0x800040);
	GUI_DispStringHCenterAt("Leak adhesive sensor",360,17);

} 
//----------------------------------------------------------------
static unsigned index;
void dispTemGraph(void)
{
	static U8 fist;
	if(!graph){
	    if((reDraw)||(!fist)) { 
			GUI_Clear();
		    GUI_DrawGradientV(3, 35, 720, 480, 0x8080FF, GUI_DARKGREEN);
	    }
		for (index = 0; index < 8; index++) {	
			
		 // *Param[index].alarm =(*Param[index].PV > *Param[index].SV) ? 1 : 0;			
		  Param[index].Angle = 210-((*Param[index].PV-200)*240.0/4800);
          Param[index].Angle *= 3.1415926f / 180;			
		  GUI_RotatePolygon(Param[index].aPoints, _aNeedle, 5, Param[index].Angle);
		  GUI_MEMDEV_DrawAuto(&aAuto[index], &Param[index].AutoDevInfo, &_DrawPanel, &Param[index]);
				
		}
		if((reDraw)||(!fist)) { 
		   drawTite();
		   fist = 1;
		   reDraw = 0;
		}	
		GUI_Exec();
	}		
}
void MainTask(void)
{
	GUI_Init();
	
	BUTTON_SetDefaultSkin   (BUTTON_SKIN_FLEX);
	CHECKBOX_SetDefaultSkin (CHECKBOX_SKIN_FLEX);
	DROPDOWN_SetDefaultSkin (DROPDOWN_SKIN_FLEX);
	FRAMEWIN_SetDefaultSkin (FRAMEWIN_SKIN_FLEX);
	HEADER_SetDefaultSkin   (HEADER_SKIN_FLEX);
	PROGBAR_SetDefaultSkin  (PROGBAR_SKIN_FLEX);
	RADIO_SetDefaultSkin    (RADIO_SKIN_FLEX);
	SCROLLBAR_SetDefaultSkin(SCROLLBAR_SKIN_FLEX);
	SLIDER_SetDefaultSkin   (SLIDER_SKIN_FLEX);
		    
  for (int i = 0; i < countof(aAuto); i++) {
      GUI_MEMDEV_CreateAuto(&aAuto[i]);
  }
  GUI_AA_SetFactor(MAG);
  GUI_AA_EnableHiRes();
	lcdLight(16);
	GUI_SetBkColor(GUI_WHITE);
    GUI_Clear(); 
	
//	calibrate();
	WM_SetCreateFlags(WM_CF_MEMDEV);
    CreateWindow();
	Creategraph();
    
}

//----------------------------------------------------------------
void DrawArcScale(U16 x0,U16 y0) //160,180
{
	int i,x,y;
	float a;
	char ac[4];
	const U16 R=77; //78
//	
	GUI_SetPenSize( 8 );
	GUI_SetTextMode(GUI_TM_TRANS);
	GUI_SetFont(GUI_FONT_8_1);	
	GUI_SetColor(GUI_BLUE);
	
	GUI_DrawArc( x0,y0,R, R,0, 360 );//-30,210
	GUI_SetPenSize( 1 );
	GUI_SetColor(GUI_DARKGRAY);
	GUI_DrawArc( x0,y0,R-4,R-4,0,360);
	GUI_DrawArc( x0,y0,R+4,R+4,0,360);	
	GUI_SetColor(0x00d0a080);
	GUI_FillCircle(x0,y0,R-7);
	GUI_SetColor(GUI_BLUE);
	
	for (i=0; i<= 24; i++) 
	{
		a = (-30+i*10)*3.1415926/180;
		x = -(R-9) * cos(a)+x0; 
		y = -(R-9) * sin(a)+y0;
		if (i%2 == 0)
		GUI_SetPenSize( 5 );
		else
		GUI_SetPenSize( 3 );
		GUI_DrawPoint(x,y);
		if (i%2 == 0) 
		{
			x = -(R-27)*cos(a)+x0;
			y = -(R-20)*sin(a)+y0;
			sprintf(ac, "%d", 20*i+20);
			GUI_SetTextAlign(GUI_TA_VCENTER);
			GUI_DispStringHCenterAt(ac,x,y);
		}
    }	
    GUI_SetFont(GUI_FONT_16B_1);
	GUI_DispStringAt("SV:",x0-37,y0+50);
	GUI_SetFont(GUI_FONT_10_1);
	GUI_SetColor(GUI_BLACK);
	GUI_DispStringAt("Temperature",x0-33,y0+23);
	
}
//----------------------------------------------------------------
void DrawPanel(U16 x0,U16 y0)
{		
	GUI_SetColor(0x00606060);
	GUI_FillRect(x0+6,y0+10,x0+176,y0+219); 
	
	GUI_SetColor(0x00FF8080);
	GUI_FillRect(x0+6,y0+10,x0+171,y0+212); //208	
	GUI_SetColor(GUI_DARKGRAY);
   GUI_DrawRect(x0+6,y0+10,x0+171,y0+212);	
	DrawArcScale(x0+89,y0+112);
			
	GUI_SetColor(GUI_YELLOW);
	GUI_FillRect(x0+6,y0+10,x0+58,y0+34);	
	GUI_SetFont(GUI_FONT_20B_1);	
    GUI_SetColor(GUI_BLUE);		
	GUI_GotoXY(Param[index].x0+12, Param[index].y0+24);	
	GUI_DispString("NO.");
	GUI_DispDecShift(index+1, 1, 0);	

}
//---------------------------------------------------------------
void _DrawPanel(void * p)
{
	PARAM * pParam;
    pParam = (PARAM *)p;
	if ((pParam->AutoDevInfo.DrawFixed)||(reDraw)) {
		DrawPanel(pParam->x0,pParam->y0);
	}
	GUI_SetColor(GUI_DARKMAGENTA);
	GUI_AA_FillPolygon(pParam->aPoints, countof(_aNeedle), MAG*(pParam->x0+88),MAG*(pParam->y0+112));
	
	GUI_SetColor(GUI_WHITE);
	
    GUI_SetFont(GUI_FONT_13B_1);
    GUI_DispStringAt("o",pParam->x0+73,pParam->y0+70);	
	GUI_SetFont(GUI_FONT_32B_1);
	
	if(*pParam->cf ==0)
		GUI_DispStringAt("C",pParam->x0+79,pParam->y0+85);
	else
	   GUI_DispStringAt("F",pParam->x0+79,pParam->y0+85);
	
	if(*pParam->alarm ==0)
		GUI_SetColor(GUI_BLUE);
	else
	    GUI_SetColor(GUI_RED);
	
	GUI_GotoXY(pParam->x0+53, pParam->y0+112);	
	//GUI_DispDecShift(*pParam->PV, 5, 1);  //
	GUI_DispString(int2Text(*pParam->PV));
	
    GUI_SetFont(GUI_FONT_20B_1);
	GUI_SetColor(GUI_BLUE);
	GUI_GotoXY(pParam->x0+75, pParam->y0+163);
	GUI_DispDecShift(*pParam->SV, 5, 1);	
	
	
}
//---------------------------------------------------------------


//


