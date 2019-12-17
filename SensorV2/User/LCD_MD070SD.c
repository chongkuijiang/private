

#include "LCD_MD070SD.h" 
#include "stm32f10x.h"

void Dealyms(uint16_t ms);
#define LCD_CLR_RESET()   GPIOC->BRR = (1<<8)
#define LCD_SET_RESET()   GPIOC->BSRR = (1<<8)
#define LCD_CLR_A0()      GPIOC->BRR = (1<<6)
#define LCD_SET_A0()      GPIOC->BSRR = (1<<6)
#define LCD_CLR_WR()      GPIOC->BRR = (1<<7)
#define LCD_SET_WR()      GPIOC->BSRR = (1<<7)
#define LCD_CLR_RD()      GPIOC->BRR = (1<<8)
#define LCD_SET_RD()      GPIOC->BSRR = (1<<8)
#define LCD_CLR_CS()      GPIOC->BRR = (1<<9)
#define LCD_SET_CS()      GPIOC->BSRR = (1<<9)

#define LCD_DATA_IN       GPIOB->IDR
#define LCD_DATA_OUT      GPIOB->ODR
#define LCD_SET_DIR_IN()  Datain()
#define LCD_SET_DIR_OUT() Dataout()
#define LCD_DELAY(ms)     Dealyms(ms)  //GUI_X_Delay(ms)


#define LCD_READ(c)                            \
  LCD_SET_DIR_IN();                              \
  LCD_CLR_RD();                                  \
  c = LCD_DATA_IN;                               \
  LCD_SET_RD();                                  \
  LCD_SET_DIR_OUT()

#define LCD_WRITE(c)                           \
  LCD_DATA_OUT = c ;                             \
  LCD_CLR_WR();                                  \
  LCD_SET_WR();                                  \



//--------------------------------------------------------------------
void LcdWriteReg(U16 Data) {
   LCD_CLR_A0();
   LCD_WRITE(Data);
}
//--------------------------------------------------------------------
void LcdWriteData(U16 Data) {
  LCD_SET_A0();
 LCD_WRITE(Data);
}
//--------------------------------------------------------------------
////Write multiple bytes to controller, with A0 = 1
//void LcdWriteDataMultiple(U16 * pData, int NumWords) {
//  LCD_SET_A0();
//  LCD_CLR_CS(); 
//  for (; NumWords; NumWords--){
//    LCD_DATA_OUT = *pData;                                                             
//    LCD_CLR_WR();                             
//    LCD_SET_WR();  
//    pData++;	  
//  }
//  LCD_SET_CS();
//}
////--------------------------------------------------------------------
////Read multiple bytes from controller, with A0 = 1
//void LcdReadDataMultiple(U16 * pData, int NumWords) {
//  LCD_SET_A0();
//  LCD_SET_DIR_IN();
//  LCD_CLR_CS();
//  for (; NumWords; NumWords--) {
//    LCD_CLR_RD();                                 
//    *pData = LCD_DATA_IN;                                                  \
//    LCD_SET_RD();      
//    pData++;
//  }
//  LCD_SET_CS();
//  LCD_SET_DIR_OUT();
//}
//--------------------------------------------------------------------
void lcdInit(void) {
  LCD_SET_DIR_OUT();
  LCD_SET_CS();
  LCD_SET_RD();
  LCD_SET_WR();
  LCD_CLR_RESET();
  LCD_DELAY(20);
  LCD_SET_RESET();
  LCD_DELAY(20);
  LCD_CLR_CS();
//  LcdWriteReg(0x01); //打开背光	
 // LcdWriteData(16);  //背光亮度：0-16	
  LCD_SET_CS();	
}
//-------------------------------------------------------------------
void lcdLight(U16 val)
{
	LCD_CLR_CS();
	LcdWriteReg(0x01); 
    LcdWriteData(val);  
	LCD_SET_CS();	
}
//-------------------------------------------------------------------
//设置起始地址与结束地址
void LcdSetAddress(U16 x0,U16 y0,U16 x1,U16 y1)
{ 	
	LcdWriteReg(0x02);//开始y
	LcdWriteData(y0); 
	LcdWriteReg(0x03);//开始x
	LcdWriteData(x0);	    
   	LcdWriteReg(0x06);//结束y
	LcdWriteData(y1); 
	LcdWriteReg(0x07);//结束x
	LcdWriteData(x1);   
	LcdWriteReg(0x0f);	   	
}
//-------------------------------------------------------------------
//画点
void lcdDrawPoint(U16 x,U16 y,U16 color)
{
	LCD_CLR_CS();
	LcdSetAddress(x,y,x,y);	
	LcdWriteData(color); 
	LCD_SET_CS();
} 
//-------------------------------------------------------------------
U16 lcdReadPoint(U16 x,U16 y)
{
	U16 color;
	LCD_CLR_CS();
	LcdSetAddress(x,y,x,y);
	LCD_READ(color); 
	LCD_SET_CS();
	return color;
} 	 
//-------------------------------------------------------------------
//在指定区域内填充指定颜色
void lcdFill(U16 x0,U16 y0,U16 x1,U16 y1,U16 color)
{          
	U16 i,j; 
	LCD_CLR_CS();
	LcdSetAddress(x0,y0,x1,y1);   
	for(i=y0;i<=y1;i++)
	{													   	 	
		for(j=x0;j<=x1;j++)
		LcdWriteData(color);
	} 		
    LCD_SET_CS();	
}
//Color:要清屏的填充色
void LCD_Clear(U16 Color)
{
	lcdFill(0,0,800-1,480-1,Color);	
}

void Dataout(void){
  GPIO_InitTypeDef GPIO_InitStruct;
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void Datain(void){
  GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOB, &GPIO_InitStruct);
}
void WritePage(unsigned char  index)//设置当前操作页，上电默认为0
{
	LCD_CLR_CS();
	LcdWriteReg(0x05);
	LcdWriteData(index); 
	LCD_SET_CS();
}
void ShowPage(unsigned char  index)//设置当前显示页，上电默认为0
{
	LCD_CLR_CS();
	LcdWriteReg(0x04);
	LcdWriteData(index); 
    LCD_SET_CS();	
}
//_DrawBitLine16BPP
void drawLine16BPP(int x, int y, U16 const * p, int xsize)
{
	LCD_CLR_CS();
	LcdSetAddress(x,y,x+xsize,y); 
	for (;xsize > 0; xsize--, p++)
	{
        LcdWriteData(*p);
	}
	LCD_SET_CS();
}
