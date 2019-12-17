#ifndef __24CXX_H
#define __24CXX_H
#include "myiic.h"   


#define AT24C01		127
#define AT24C02		255
#define AT24C04		511
#define AT24C08		1023
#define AT24C16		2047
#define AT24C32		4095
#define AT24C64	    8191
#define AT24C128	16383
#define AT24C256	32767  
//����EE_TYPE
#define EE_TYPE AT24C16
 


u8 AT24CXX_Read_Byte(u16 ReadAddr);							//ָ����ַ��ȡһ���ֽ�
void AT24CXX_Write_Byte(u16 WriteAddr,u8 DataToWrite);		//ָ����ַд��һ���ֽ�

void AT24CXX_Write_u16(u16 WriteAddr,u16 DataToWrite);
void AT24CXX_Write_u32(u16 WriteAddr,u32 DataToWrite);

u16 AT24CXX_Read_u16(u16 ReadAddr);	
u32 AT24CXX_Read_u32(u16 ReadAddr);

void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite);	//��ָ����ַ��ʼд��ָ�����ȵ�����
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead);   	//��ָ����ַ��ʼ����ָ�����ȵ�����

u8 AT24CXX_Data_Init(u16 Addr,void * arg,u16 Num);  //��ʼ������
void AT24CXX_Init(void); //��ʼ��IIC
#endif
















