
#ifndef _LCD_MD070SD_H
#define _LCD_MD070SD_H

#include <stdint.h>
#define U16 unsigned short


//������ɫ
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
#define BROWN 			 0XBC40 //��ɫ
#define BRRED 			 0XFC07 //�غ�ɫ
#define GRAY  			 0X8430 //��ɫ
//GUI��ɫ

#define DARKBLUE      	 0X01CF	//����ɫ
#define LIGHTBLUE      	 0X7D7C	//ǳ��ɫ  
#define GRAYBLUE       	 0X5458 //����ɫ
//������ɫΪPANEL����ɫ 
 
#define LIGHTGREEN     	 0X841F //ǳ��ɫ
#define LGRAY 			 0XC618 //ǳ��ɫ(PANNEL),���屳��ɫ

#define LGRAYBLUE        0XA651 //ǳ����ɫ(�м����ɫ)
#define LBBLUE           0X2B12 //ǳ����ɫ(ѡ����Ŀ�ķ�ɫ)



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



















