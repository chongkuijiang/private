
#include "24cxx.h" 


//初始化IIC接口
void AT24CXX_Init(void)
{
	IIC_Init();
}
//在AT24CXX指定地址读出一个数据
//ReadAddr:开始读数的地址  
//返回值  :读到的数据
u8 AT24CXX_Read_Byte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//产生一个停止条件	    
	return temp;
}
//在AT24CXX指定地址写入一个数据
//WriteAddr  :写入数据的目的地址    
//DataToWrite:要写入的数据
void AT24CXX_Write_Byte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//发送高地址
 	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //发送器件地址0XA0,写数据 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //发送低地址
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //发送字节							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//产生一个停止条件 
	//delay_ms(10);	 
}
//该函数用于写入16bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址

void AT24CXX_Write_u16(u16 WriteAddr,u16 DataToWrite)
{  	
	u8 t;
	for(t=0;t<2;t++)
	{
		AT24CXX_Write_Byte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
//该函数用于写入32bit的数据.
//WriteAddr  :开始写入的地址  
//DataToWrite:数据数组首地址
void AT24CXX_Write_u32(u16 WriteAddr,u32 DataToWrite)
{  	
	u8 t;
	for(t=0;t<4;t++)
	{
		AT24CXX_Write_Byte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//该函数用于读出16bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
u16 AT24CXX_Read_u16(u16 ReadAddr)
{  	
	u16 temp = 0;
	temp = AT24CXX_Read_Byte(ReadAddr+1);
	temp <<= 8;
	temp += AT24CXX_Read_Byte(ReadAddr);	
	return temp;												    
}
//该函数用于读出32bit的数据.
//ReadAddr   :开始读出的地址 
//返回值     :数据
u32 AT24CXX_Read_u32(u16 ReadAddr)
{  	
	u8 t;
	u32 temp=0;
	for(t=0;t<4;t++)
	{
		temp<<=8;
		temp+=AT24CXX_Read_Byte(ReadAddr+4-t-1); 	 				   
	}
	return temp;												    
}
//这里用了24XX的最后一个地址来存储标志字.
//返回1:检测失败
//返回0:检测成功
#define VERSION  0xa7  
u8 AT24CXX_Data_Init(u16 Addr,void * arg,u16 Num)
{
	u8 temp,err;
	static u8 init;
	u8 * buf;
	buf = (u8 *)arg;
	err = 1;
	temp=AT24CXX_Read_Byte(EE_TYPE);		   
	if((temp==VERSION)&&(init == 0))
	{
		err = 0;
		init = 0;
		AT24CXX_Read(Addr,buf,Num);
	}		
	else//排除第一次初始化的情况
	{
		AT24CXX_Write_Byte(EE_TYPE,VERSION);
	    temp=AT24CXX_Read_Byte(EE_TYPE);	  
		if(temp==VERSION)
		{
			err = 0;
			init = 1;
			AT24CXX_Write(Addr,buf,Num);
		}
	}
	return err;											  
}

//在AT24CXX里面的指定地址开始读出指定个数的数据
//ReadAddr :开始读出的地址 
//pBuffer  :数据数组首地址
//NumToRead:要读出数据的个数
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //发送写命令
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//发送高地址
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //发送器件地址0XA0,写数据 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //发送低地址
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //进入接收模式			   
	IIC_Wait_Ack();	     	
//	*pBuffer++ = IIC_Read_Byte(1);
//	NumToRead -= 2;
	while(NumToRead)
	{
		if(NumToRead ==1) *pBuffer++ = IIC_Read_Byte(0);
		else *pBuffer++ = IIC_Read_Byte(1);	
		NumToRead--;
	}
//	*pBuffer++ = IIC_Read_Byte(0);	
	IIC_Stop();
}  
//在AT24CXX里面的指定地址开始写入指定个数的数据
//WriteAddr :开始写入的地址 
//pBuffer   :数据数组首地址
//NumToWrite:要写入数据的个数
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_Write_Byte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











