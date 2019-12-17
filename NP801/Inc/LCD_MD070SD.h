
#ifndef _LCD_MD070SD_H
#define _LCD_MD070SD_H

#include <stdint.h>
#define U16 unsigned short


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE         	 0x001F  
#define BRED             0XF81F
#define GRED 			 0XFFE0
#define GBLUE			 0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			 0XBC40 //棕色
#define BRRED 			 0XFC07 //棕红色
#define GRAY  			 0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			 0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)



void LcdWriteReg(U16 Data);
void LcdWriteData(U16 Data);
void LcdWriteDataMultiple(U16 * pData, int NumWords);
void LcdReadDataMultiple(U16 * pData, int NumWords);
void lcdInit(void);
void lcdDrawPoint(U16 x,U16 y,U16 color);
U16 lcdReadPoint(U16 x,U16 y);
void lcdFill(U16 x0,U16 y0,U16 x1,U16 y1,U16 color);
void drawLine16BPP(int x, int y, U16 const * p, int xsize);
void lcdLight(U16 val);
void Dataout(void);
void Datain(void);

void WritePage(unsigned char  index);
void ShowPage(unsigned char  index);


uint16_t touchReadAdc_X(void);
uint16_t touchReadAdc_Y(void);
#endif 



















