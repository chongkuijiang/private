
#include "lookUp.h"


//----------------------------------------------------------------------------------
// ����: ���½����Ʊ�,���ر���±�,������NTC���¡�
// ����: tab-ÿ������Ҫ����һ������
// ���룺R-(����)
// ���: ���floatֵ
float downtrendTab(lookUp_param_t *tab,int32_t R) 
{
	float result;
	uint16_t decimal;
	decimal = 0;
	while(1)
    {
		if(R < tab->Tab[tab->index])
		{
			tab->index++;
			if(R > tab->Tab[tab->index]){
			   tab->index--;
				decimal = 1;break;
			}
		}
		else if(R > tab->Tab[tab->index]) 
		{
			tab->index--;
			if(R < tab->Tab[tab->index]){
				decimal = 1;break;				
			}
		}
		else break;		
		if(tab->index > tab->maxIndex){
			tab->index = tab->maxIndex;break;			
		}	
	}
    result = tab->index * tab->pace + tab->min;
	if(decimal == 1){
		result += (float)(tab->Tab[tab->index]-R)*tab->pace / (tab->Tab[tab->index]-tab->Tab[tab->index+1]);
	}
	return result;
}
//----------------------------------------------------------------------------------
// ����: ���������Ʊ�,���ر���±�,�������ȵ�����¡�
// ����: tab-ÿ������Ҫ����һ������
// ���룺volt-(����)
// ���: ���floatֵ
float uptrendTab(lookUp_param_t *tab,int32_t volt) 
{
	float result;
	uint16_t decimal;
	decimal = 0;
	while(1)
    {
		if(volt > tab->Tab[tab->index])
		{
			tab->index++;
			if(volt < tab->Tab[tab->index]){
			   tab->index--;
				decimal = 1;break;
			}
		}
		else if(volt < tab->Tab[tab->index]) 
		{
			tab->index--;
			if(volt > tab->Tab[tab->index]){
				decimal = 1;break;				
			}
		}
		else break;
        if(tab->index > tab->maxIndex){
			tab->index = tab->maxIndex;break;			
		}			
	}
    result = tab->index * tab->pace + tab->min;
	if(decimal == 1){
		result += (float)(volt-tab->Tab[tab->index])*tab->pace / (tab->Tab[tab->index+1]-tab->Tab[tab->index]);
	}
	return result;
}
//------------------------------------------------------------------------------------
// ����: ������������Ʊ�,������ֵ��
// ����: tab-���޸Ķ����еı���
// ���룺volt-(����)
// ���: ���floatֵ
float Re_uptrendTab(lookUp_param_t *tab,int32_t volt) 
{
	uint16_t i;
	float result;
	i = volt/tab->pace;
	result = tab->Tab[i];
	if(volt%tab->pace != 0)
		result += (float)(volt-tab->Tab[i])*tab->pace/(tab->Tab[i+1]-tab->Tab[i]);
	return result;
}
//------------------------------------------------------------------------------------
// ����: ������½����Ʊ�,������ֵ��
// ����: tab-���޸Ķ����еı���
// ���룺volt-(����)
// ���: ���floatֵ
float Re_downtrendTab(lookUp_param_t *tab,int32_t volt) 
{
	uint16_t i;
	float result;
	i = volt/tab->pace;
	result = tab->Tab[i];
	if(volt%tab->pace != 0)
		result += (float)(tab->Tab[i]-volt)*tab->pace/(tab->Tab[i]-tab->Tab[i+1]);
	return result;
}
//------------------------------------------------------------------------------------
// ����: ��ʼ��һ��������
// ����: tab-����ָ�룬Tab-��ָ��... 
void init_LookUp(lookUp_param_t *tab,tablt_t *Tab,
	uint16_t step,int16_t min,uint16_t maxIndex) //���������Ʊ���
{	
	tab->Tab = Tab;
	tab->index = 0;
	tab->pace = step;
	tab->min = min;
	tab->maxIndex = maxIndex;    
}
//-------------------------------------------------------------------
#include "tempTab.h"
#include "stm32f1xx_hal.h"
#include "DIALOG.h"
extern ADC_HandleTypeDef hadc1;
extern DMA_HandleTypeDef hdma_adc1;
typedef struct 
{	
	lookUp_param_t EnvTemOffce;
	lookUp_param_t Tem;
}thermocouple_t;
static lookUp_param_t EnvTem;
static thermocouple_t TemTab[8];
  uint32_t adcVal[9],adcNum[9],adcBuf[9];

//---------------------------------------------------------
void Tem_Init(void)
{	
	init_LookUp(&EnvTem,NTtab,100,-20000,1300); //*100
	for(int i=0;i<8;i++){
		init_LookUp(&TemTab[i].EnvTemOffce,JTtab,100,-20900,1409);
		init_LookUp(&TemTab[i].Tem,JTtab,100,-20900,1409);
	}		
	 HAL_ADC_Start_DMA(&hadc1, adcBuf, 9); 
}
//----------------------------------------------------------
void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
	for(int i=0;i<8;i++){		
	 //   temperature[i].PV10 = adcBuf[i];
		//adcBuf[i] = 0;
		//adcNum[i]++;
	}
}
