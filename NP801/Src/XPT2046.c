

/* ����ͷ�ļ� ----------------------------------------------------------------*/

#include "stm32f1xx_hal.h"

//-------------------------------------------------------------------
#define TOUCH_CLR_CS()        GPIOC->BRR = (1<<11)
#define TOUCH_SET_CS()        GPIOC->BSRR = (1<<11)
#define TOUCH_CLR_MOSI()      GPIOA->BRR = (1<<7)
#define TOUCH_SET_MOSI()      GPIOA->BSRR = (1<<7)
#define TOUCH_MISO()          HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_6)
#define TOUCH_CLR_CLK()       GPIOA->BRR = (1<<5)
#define TOUCH_SET_CLK()       GPIOA->BSRR = (1<<5)
#define	CHANNEL_Y 	          0x90 	          //ͨ��Y+��ѡ�������	
#define	CHANNEL_X 	          0xd0	          //ͨ��X+��ѡ�������



//-------------------------------------------------------------------
	
static void TOUCH_Delay (void)
{	
	uint8_t uc = 12;     //����ֵΪ12����Լ��1΢��  	      
	while ( uc -- );     //��1΢��	
}

//-------------------------------------------------------------------
static void touchWriteCMD ( uint8_t ucCmd ) 
{
	uint8_t i;
  
	TOUCH_CLR_MOSI();	
	TOUCH_CLR_CLK();

	for ( i = 0; i < 8; i ++ ) 
	{
		if(ucCmd&0x80) TOUCH_SET_MOSI();  
		else TOUCH_CLR_MOSI();   
		ucCmd<<=1;  	
	    TOUCH_Delay();		
		TOUCH_SET_CLK();
	    TOUCH_Delay();
		TOUCH_CLR_CLK();
	}	
}

//-------------------------------------------------------------------

static uint16_t touchReadCMD ( void ) 
{
	uint8_t i;
	uint16_t usBuf;
    usBuf=0;
	TOUCH_CLR_MOSI();
	TOUCH_SET_CLK();
	for ( i=0;i<16;i++ ) 
	{		
		TOUCH_CLR_CLK();
		usBuf <<= 1;
        TOUCH_SET_CLK();		
        if(TOUCH_MISO()) usBuf++;			       		
	}	
	usBuf >>= 4;
	return usBuf;
}
//---------------------------------------------------------------
//��ȡһ������ֵ
//������ȡREAD_TIMES������,����Щ������������,
//Ȼ��ȥ����ͺ����LOST_VAL����,ȡƽ��ֵ 
#define READ_TIMES 7 //��ȡ����
#define LOST_VAL 1	  //����ֵ
uint16_t touchReadAdc(uint8_t channel)
{
	uint16_t i, j;
	uint16_t buf[READ_TIMES];
	uint16_t sum=0;
	uint16_t temp;
	for(i=0;i<READ_TIMES;i++)
	{		
        TOUCH_CLR_CS();
        touchWriteCMD(channel);
        buf[i] = touchReadCMD();  
        TOUCH_SET_CS();		   
	}				    
	for(i=0;i<READ_TIMES-1; i++)//����
	{
		for(j=i+1;j<READ_TIMES;j++)
		{
			if(buf[i]>buf[j])//��������
			{
				temp=buf[i];
				buf[i]=buf[j];
				buf[j]=temp;
			}
		}
	}	  
	sum=0;
	for(i=LOST_VAL;i<READ_TIMES-LOST_VAL;i++)sum+=buf[i];
	temp=sum/(READ_TIMES-2*LOST_VAL);
	
	return temp;   
}
//--------------------------------------------------------------
#define ERR_RANGE 90 //��Χ 
uint16_t touchFliter(uint8_t channel)
{
	uint16_t temp1,temp2;
	temp1 = touchReadAdc(channel);
	if(temp1<ERR_RANGE)return(0);
	temp2 = touchReadAdc(channel);
	if(temp2<ERR_RANGE)return(0);
	
	if((temp2<=temp1&&temp1<temp2+ERR_RANGE)||(temp1<=temp2&&temp2<temp1+ERR_RANGE))
	return (temp1+temp2)>>1;
	
    return 0;
}
//-------------------------------------------------------------------
uint16_t touchReadAdc_X(void)
{
	return touchFliter(CHANNEL_X);	
}
//-------------------------------------------------------------------
uint16_t touchReadAdc_Y(void)
{	
	return touchFliter(CHANNEL_Y);
}
//-------------------------------------------------------------------

