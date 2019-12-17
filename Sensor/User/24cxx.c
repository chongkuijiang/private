
#include "24cxx.h" 


//��ʼ��IIC�ӿ�
void AT24CXX_Init(void)
{
	IIC_Init();
}
//��AT24CXXָ����ַ����һ������
//ReadAddr:��ʼ�����ĵ�ַ  
//����ֵ  :����������
u8 AT24CXX_Read_Byte(u16 ReadAddr)
{				  
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
	IIC_Wait_Ack();	 
    temp=IIC_Read_Byte(0);		   
    IIC_Stop();//����һ��ֹͣ����	    
	return temp;
}
//��AT24CXXָ����ַд��һ������
//WriteAddr  :д�����ݵ�Ŀ�ĵ�ַ    
//DataToWrite:Ҫд�������
void AT24CXX_Write_Byte(u16 WriteAddr,u8 DataToWrite)
{				   	  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	    //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(WriteAddr>>8);//���͸ߵ�ַ
 	}else
	{
		IIC_Send_Byte(0XA0+((WriteAddr/256)<<1));   //����������ַ0XA0,д���� 
	}	 
	IIC_Wait_Ack();	   
    IIC_Send_Byte(WriteAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack(); 	 										  		   
	IIC_Send_Byte(DataToWrite);     //�����ֽ�							   
	IIC_Wait_Ack();  		    	   
    IIC_Stop();//����һ��ֹͣ���� 
	//delay_ms(10);	 
}
//�ú�������д��16bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ

void AT24CXX_Write_u16(u16 WriteAddr,u16 DataToWrite)
{  	
	u8 t;
	for(t=0;t<2;t++)
	{
		AT24CXX_Write_Byte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}
//�ú�������д��32bit������.
//WriteAddr  :��ʼд��ĵ�ַ  
//DataToWrite:���������׵�ַ
void AT24CXX_Write_u32(u16 WriteAddr,u32 DataToWrite)
{  	
	u8 t;
	for(t=0;t<4;t++)
	{
		AT24CXX_Write_Byte(WriteAddr+t,(DataToWrite>>(8*t))&0xff);
	}												    
}

//�ú������ڶ���16bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
u16 AT24CXX_Read_u16(u16 ReadAddr)
{  	
	u16 temp = 0;
	temp = AT24CXX_Read_Byte(ReadAddr+1);
	temp <<= 8;
	temp += AT24CXX_Read_Byte(ReadAddr);	
	return temp;												    
}
//�ú������ڶ���32bit������.
//ReadAddr   :��ʼ�����ĵ�ַ 
//����ֵ     :����
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
//��������24XX�����һ����ַ���洢��־��.
//����1:���ʧ��
//����0:���ɹ�
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
	else//�ų���һ�γ�ʼ�������
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

//��AT24CXX�����ָ����ַ��ʼ����ָ������������
//ReadAddr :��ʼ�����ĵ�ַ 
//pBuffer  :���������׵�ַ
//NumToRead:Ҫ�������ݵĸ���
void AT24CXX_Read(u16 ReadAddr,u8 *pBuffer,u16 NumToRead)
{
	u8 temp=0;		  	    																 
    IIC_Start();  
	if(EE_TYPE>AT24C16)
	{
		IIC_Send_Byte(0XA0);	   //����д����
		IIC_Wait_Ack();
		IIC_Send_Byte(ReadAddr>>8);//���͸ߵ�ַ
		IIC_Wait_Ack();		 
	}else IIC_Send_Byte(0XA0+((ReadAddr/256)<<1));   //����������ַ0XA0,д���� 	 

	IIC_Wait_Ack(); 
    IIC_Send_Byte(ReadAddr%256);   //���͵͵�ַ
	IIC_Wait_Ack();	    
	IIC_Start();  	 	   
	IIC_Send_Byte(0XA1);           //�������ģʽ			   
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
//��AT24CXX�����ָ����ַ��ʼд��ָ������������
//WriteAddr :��ʼд��ĵ�ַ 
//pBuffer   :���������׵�ַ
//NumToWrite:Ҫд�����ݵĸ���
void AT24CXX_Write(u16 WriteAddr,u8 *pBuffer,u16 NumToWrite)
{
	while(NumToWrite--)
	{
		AT24CXX_Write_Byte(WriteAddr,*pBuffer);
		WriteAddr++;
		pBuffer++;
	}
}
 











