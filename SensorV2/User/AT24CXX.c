#include "stm32f10x.h"
#include "main.h"

#define  set_SDA   GPIOA->BSRR=GPIO_Pin_12 //0  
#define  clr_SDA   GPIOA->BRR=GPIO_Pin_12
#define  set_SCL   GPIOA->BSRR=GPIO_Pin_11 //1
#define  clr_SCL   GPIOA->BRR=GPIO_Pin_11
#define SCL_read GPIOA->IDR & GPIO_Pin_11
#define SDA_read GPIOA->IDR & GPIO_Pin_12
//=======================================================

Save_t ParSave;
uint8_t getSaveAddr(void* adr)
{
	uint8_t num=0;
	num = (uint32_t*)adr - (uint32_t*)&ParSave;
	return num;
}
//--------------------------------------------------------
void Delay(uint16_t num)
{
	uint16_t i;
	while(num--)
	{
		for(i=0;i<255;i++); //255*1.5
	}
}
void delay(uint16_t num)
{
	uint16_t i;
	while(num--)
	{
		for(i=0;i<64;i++); //63*1.5
	}
}

void I2C_delay(void)
{
	u8 i=15; //10*1.5
	while(i) { i--; } 
}
u8 Start(void)
{ 
  set_SDA;
  delay(100);
  set_SCL;
  delay(100);
  if(!SDA_read) return 1;
  clr_SDA;
  delay(100);
  if(SDA_read) return 1;
  clr_SCL;
  delay(100);
  return 0;
}
void Stop(void)
{ 
  clr_SCL;
  delay(100);
  clr_SDA;
  delay(100);
  set_SCL;
  delay(100);
  set_SDA;
  delay(100);
}

uint8_t RecAck(void)
{ 
	u8 errtime = 225;
	clr_SCL;
	I2C_delay();
	set_SDA;
	I2C_delay();
  	set_SCL;
  	I2C_delay();
  	while(SDA_read) 
	{
		if(--errtime==0) {Stop();return 1;}
	}
	clr_SCL;
	I2C_delay();
	return 0;
}

void Ack(void)
{ 
	clr_SCL;
	I2C_delay();
  	clr_SDA;
  	I2C_delay();
  	set_SCL;
  	I2C_delay();
  	clr_SCL;
  	I2C_delay();
}

void NoAck(void)
{
	clr_SCL;
	I2C_delay();
  	set_SDA;
	I2C_delay();
  	set_SCL;
  	I2C_delay();
  	clr_SCL;
	I2C_delay();
}

void Send(uint8_t sendByte)
{ 
  uint8_t j=8;
  while(j--)
  { 
	clr_SCL;
	I2C_delay();
	if(sendByte&0x80) set_SDA;
	else clr_SDA;
	I2C_delay();
	sendByte<<=1;
	set_SCL;
	I2C_delay();
  }
  clr_SCL;
}

uint8_t Receive(void)
{ 
  uint8_t receiveByte=0,i=8;
  while(i--)
  { 
  	receiveByte<<=1; 
    clr_SCL;
    I2C_delay();   
	set_SCL;
	I2C_delay(); 
    if(SDA_read) receiveByte|=0x01;
  }  
  clr_SCL;  
  return(receiveByte);
}

uint8_t CommIIC(void *data, uint16_t number,uint16_t startAddress, uint8_t WR )
{
	uint8_t deviceAddress=0,x=0,i=2,nu,*p=0;
	uint16_t address;
	while(i--)
	{
		address=startAddress;
		if(address<256) deviceAddress=0xA0;
		else if(address<512) deviceAddress=0xA2;
		else if(address<768) deviceAddress=0xA4;
		else if(address<1024) deviceAddress=0xA6;
		else if(address<1280) deviceAddress=0xA8;
		else if(address<1536) deviceAddress=0xAA;
		else if(address<1792) deviceAddress=0xAC;
		else if(address<2048) deviceAddress=0xAE;
		p=(uint8_t *)data;
		nu=number;
		x=0;
		if(WR)
		{
			while(nu--)
   	 		{
				if(address<256) deviceAddress=0xA0;
				else if(address<512) deviceAddress=0xA2;
				else if(address<768) deviceAddress=0xA4;
				else if(address<1024) deviceAddress=0xA6;
				else if(address<1280) deviceAddress=0xA8;
				else if(address<1536) deviceAddress=0xAA;
				else if(address<1792) deviceAddress=0xAC;
				else if(address<2048) deviceAddress=0xAE;	
				Start();
				Send(deviceAddress);
				x+=RecAck();
				Send((uint8_t)address);
				x+=RecAck();
				Start();
				Send(deviceAddress+1);
				x+=RecAck();
				*p++=Receive();
      			address++;
				NoAck();
				Stop();	
	    	}		
		}
		else
		{
			x+=Start();
			Send(deviceAddress);
			x+=RecAck();
			Send((uint8_t)address);
			x+=RecAck();
//			clr_WP;
	  		while(--nu)
	  		{
		  		Send(*p++);
	    		x+=RecAck(); 
	    		address++;
				if(address%16==0)
				{
					Stop();
					Delay(10);
					if(address<256) deviceAddress=0xA0;
					else if(address<512) deviceAddress=0xA2;
					else if(address<768) deviceAddress=0xA4;
					else if(address<1024) deviceAddress=0xA6;
					else if(address<1280) deviceAddress=0xA8;
					else if(address<1536) deviceAddress=0xAA;
					else if(address<1792) deviceAddress=0xAC;
					else if(address<2048) deviceAddress=0xAE;
					Start();
					Send(deviceAddress);
					x+=RecAck();
					Send((uint8_t)address);
					x+=RecAck();
				}
	 		}
			Send(*p++);
			x+=RecAck();
	 	 	Stop();
//	 	 	set_WP;
	  		Delay(10);
		}
		if(!x) break;
		
	}
	data=p;
	return x; 	
}
//----------------------------------------------------------------

//=======================================================


