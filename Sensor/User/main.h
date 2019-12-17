#ifndef __MAIN_H
#define	__MAIN_H


#include "stm32f10x.h"

enum 
{
	display=0,  //显示
	alarm,      //报警
	wait,     //等待
	Sampler,  //采样	
	TOP,      //数量化
};
extern uint16_t Times[TOP+1];
enum
{
	light=0,
	save,     //保存
	OnesTOP,
};
typedef struct
{
	uint16_t delay;
	uint16_t  msg;
}ones_t;
extern ones_t Ones[OnesTOP];

typedef struct
{
	int32_t times;
	int32_t val[3];   		
}Inertia_t;  //惯性滤波

typedef struct
{
	uint16_t sv;  
	uint8_t  cf;  
	uint8_t  jk;  
}temSave_t;
typedef struct
{
	uint16_t top;  //TOUCH_AD_TOP
	uint16_t left;
	uint16_t right;
	uint16_t bottom;
	 
}lcdCalib_t;
typedef struct
{
	uint8_t   EE;
	uint16_t  Envofs;
	temSave_t Tem[8]; 
   lcdCalib_t Calib; 	
}Save_t;

extern Save_t ParSave;
uint8_t getSaveAddr(void* adr);
uint8_t CommIIC(void *data, uint16_t number,uint16_t startAddress, uint8_t WR );
//uint8_t ee_ReadBytes(uint8_t *_pReadBuf, uint16_t _usAddress, uint16_t _usSize);
//uint8_t ee_WriteBytes(uint8_t *_pWriteBuf, uint16_t _usAddress, uint16_t _usSize);
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);
void AT24CXX_Write_Byte(u16 WriteAddr,u8 DataToWrite);
void AT24CXX_Write_u16(u16 WriteAddr,u16 DataToWrite);
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);
void JKchang(uint8_t index,uint8_t jk);
void SVchang(uint8_t index,uint16_t sv);


void GPIOx_Init(void);
void SysTickProc(void);
void onAlarm(void);
void Tem_Init(void);
void Dealyms(uint16_t ms);
void getEnv(void);


#endif


