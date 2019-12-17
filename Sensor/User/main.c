


#include "stm32f10x.h"
#include "bsp_adc.h"
#include "GUI.h"
#include "DIALOG.h"
#include "LCD_MD070SD.h" 
#include "main.h"
#include "string.h"
#include "stdlib.h"

 #define OFFLIGHTTIME  60000  


 uint16_t Times[TOP+1];

ones_t Ones[OnesTOP]={{OFFLIGHTTIME,0},{0,0}};






int main(void)
{	 
  GPIOx_Init();	
	ADCx_Init();		
	Tem_Init();	
  MainTask();
  
	while (1)
	{	    
		 GUI_PID_STATE State;
		 if(!Times[display]){
				Times[display] = 100;
				dispTemGraph();
				dispTemPanel();  
				if(GUI_TOUCH_GetState(&State)){
					if(!light) {
						lcdLight(16);
						GPIO_ResetBits(GPIOC,GPIO_Pin_10);
					}
					Ones[light].delay = OFFLIGHTTIME;			
				}	 
		 }
		 if(!Times[alarm]) onAlarm();
		 if(!Times[Sampler]) getEnv();		 
//		 if(!Ones[light].delay) {lcdLight(2);GPIO_SetBits(GPIOC,GPIO_Pin_10);}
		 if(Ones[light].msg) {Ones[light].msg =0; lcdLight(2);GPIO_SetBits(GPIOC,GPIO_Pin_10);}
       if(Ones[save].msg) {Ones[save].msg =0; CommIIC(&ParSave, sizeof(Save_t), 0, 0 );}
		
	}
}

//----------------------------------------------------------------------
void GPIOx_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|
	                    RCC_APB2Periph_GPIOC|RCC_APB2Periph_GPIOD,ENABLE );
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_CRC, ENABLE);	
	
	AFIO->MAPR &= (0x07<<24);
	AFIO->MAPR |= (0x02<<24);
	 NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
	SysTick_Config(SystemCoreClock/1000);	
	
	 /*Configure GPIO pins : PC13 PC14 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_14;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pins : PA5 PA7 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_7;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PA6 PA12 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6/*|GPIO_Pin_12*/;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : GPIO_Pin_All*/
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStruct);

  /*Configure GPIO pins : PC6 PC7 PC8 PC9 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PA8 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pin : PA11 PA12*/
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*Configure GPIO pins : PC10 PC11 */
  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10|GPIO_Pin_11;
  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
  GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
  GPIO_Init(GPIOC, &GPIO_InitStruct);

  /*Configure GPIO pin : PC12 */
//  GPIO_InitStruct.GPIO_Pin = GPIO_Pin_12;
//  GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
//  GPIO_Init(GPIOC, &GPIO_InitStruct);	
	
	GPIO_ResetBits(GPIOB,GPIO_Pin_All);
	GPIO_ResetBits(GPIOA, GPIO_Pin_5|GPIO_Pin_7);
	GPIO_ResetBits(GPIOC, GPIO_Pin_10|GPIO_Pin_13|GPIO_Pin_14);
	GPIO_SetBits(GPIOC, GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_11);
	GPIO_SetBits(GPIOA, GPIO_Pin_8|GPIO_Pin_11);
	
	
}
//----------------------------------------------------------------------
extern volatile GUI_TIMER_TIME OS_TimeMS;
void SysTickProc(void)
{
	int i;
	static uint8_t tim;
	for(i=0;i<TOP;i++)
	if(Times[i] >0) Times[i]--;		
	for(i=0;i<OnesTOP;i++){
		if(Ones[i].delay >0) {
		   Ones[i].delay--;
			if(Ones[i].delay ==0) Ones[i].msg =1;
		}
	}
	OS_TimeMS++;
	if(++tim ==10){	
        tim = 0;		
	    GUI_TOUCH_Exec();       
	}
	
}
//----------------------------------------------------------------------
void Dealyms(uint16_t ms)
{
	 Times[wait] = ms;
	 while(Times[wait]>0){};
}
//----------------------------------------------------------------------
void onAlarm(void) 
{
	static uint8_t bit;
	uint8_t Error;	
	Error = 0;	
    for(int i=0;i<8;i++){
		temperature[i].alarm = (temperature[i].PV10 > temperature[i].SV10) ? 1 : 0;
		if(temperature[i].alarm) Error = 1; 
	}
    if(Error) GPIOC->ODR ^= GPIO_Pin_10|GPIO_Pin_13;  
	if((bit)&&(!Error)) GPIO_ResetBits(GPIOC,GPIO_Pin_10|GPIO_Pin_13);
    bit = Error;		
	Times[alarm] = 400;//300ms
}

