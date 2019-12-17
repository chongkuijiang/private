
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
	uint16_t i,j;
	float result;
	i = (volt-tab->min)/tab->pace;
	result = tab->Tab[i];
	j = (volt-tab->min)%tab->pace;
	if(j != 0)
		result += (float)j*(tab->Tab[i+1]-tab->Tab[i]) / tab->pace;
	return result;
}
//------------------------------------------------------------------------------------
// ����: ������½����Ʊ�,������ֵ��
// ����: tab-���޸Ķ����еı���
// ���룺volt-(����)
// ���: ���floatֵ
float Re_downtrendTab(lookUp_param_t *tab,int32_t volt) 
{
	uint16_t i,j;
	float result;
	i = (volt-tab->min)/tab->pace;
	result = tab->Tab[i];
	j = (volt-tab->min)%tab->pace;
	if(j != 0)
		result -= (float)j*(tab->Tab[i]-tab->Tab[i+1]) / tab->pace;
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
#include "stm32f10x.h"
#include "DIALOG.h"
#include "bsp_adc.h"
#include "main.h"
//-------------------------------------------------------------
int32_t inertiaFilter(Inertia_t* filter,int32_t input)  //�����˲�
{
	int32_t val;
	if(filter->times <3)
	{
		filter->val[filter->times++] = input;
		val = input;
	}
	else
	{		
		val = filter->val[2]*0.35 + filter->val[1]*0.40 + input*0.25;	
		filter->val[2] = filter->val[1];
		filter->val[1] = filter->val[0];
		filter->val[0] = val;
	}
	return val;
}
typedef struct 
{	
	lookUp_param_t EnvTemOffset;
	lookUp_param_t Tem;
}thermocouple_t;
static lookUp_param_t EnvTem;
static thermocouple_t TemTab[8];
static Inertia_t filter[9];
static uint16_t Envofs;
//---------------------------------------------------------
static void LoadData(void)
{
	int i;
	 CommIIC((uint8_t*)&ParSave, sizeof(Save_t), 0, 1 );
	 if(ParSave.EE!= 0xee){
			ParSave.EE = 0xee;
			ParSave.Envofs = 1000;
			for(int i=0;i<8;i++){			
		   ParSave.Tem[i].sv = 2000;
			ParSave.Tem[i].cf = 0;
			ParSave.Tem[i].jk = 1;
			ParSave.Calib.top = 3839;
			ParSave.Calib.bottom = 455;
         ParSave.Calib.left = 208;
         ParSave.Calib.right = 3935;				
		}
		CommIIC(&ParSave, sizeof(Save_t), 0, 0 );
	}  
}
//---------------------------------------------------------
void Tem_Init(void)
{	
	LoadData();
	Envofs = ParSave.Envofs;
	init_LookUp(&EnvTem,NTC103_3435tab,10,-400,165); //*10	
	for(int i=0;i<8;i++){
		temperature[i].SV10 = ParSave.Tem[i].sv;
		temperature[i].jk = ParSave.Tem[i].jk;
		temperature[i].cf = ParSave.Tem[i].cf;
		if(ParSave.Tem[i].jk){
			init_LookUp(&TemTab[i].EnvTemOffset,JTtab,10,-2090,1409); 
			init_LookUp(&TemTab[i].Tem,JTtab,10,-2090,1409); //*10
		}else{
			init_LookUp(&TemTab[i].EnvTemOffset,JTtab,10,-2090,1409); 
			init_LookUp(&TemTab[i].Tem,JTtab,10,-2090,1409); //*10
		}
	}	
}
//----------------------------------------------------------
void JKchang(uint8_t index,uint8_t jk)
{
	uint8_t last;
	last = temperature[index].jk;
	temperature[index].jk = jk;
	ParSave.Tem[index].jk = jk;
	if(last != temperature[index].jk) {
		if(jk){
			init_LookUp(&TemTab[index].EnvTemOffset,JTtab,10,-2090,1409); 
			init_LookUp(&TemTab[index].Tem,JTtab,10,-2090,1409); //*10
		}else{
			init_LookUp(&TemTab[index].EnvTemOffset,JTtab,10,-2090,1409); 
			init_LookUp(&TemTab[index].Tem,JTtab,10,-2090,1409); //*10
		}
		Ones[save].delay = 3000;
	}
}
//----------------------------------------------------------
void SVchang(uint8_t index,uint16_t sv)
{
	uint16_t last;
	last = temperature[index].SV10;
	temperature[index].SV10 = sv;
	ParSave.Tem[index].sv = sv;
	if(last != temperature[index].SV10) 
	Ones[save].delay = 3000;
}
//----------------------------------------------------------
int32_t RT;
void getEnv(void)
{
	int32_t adj,R,env,encOffset[8],i;	
	adj = ADC_SumValue[8]/ADC_Count[8];
	ADC_SumValue[8] = 0;
	ADC_Count[8] = 0;	
	RT = R = 1000*10*adj/(4057-adj);//+Envofs; //R
	env = downtrendTab(&EnvTem,inertiaFilter(&filter[8],R));
	for(i=0;i<8;i++)
	{
		adj = ADC_SumValue[i]/ADC_Count[i];
		ADC_SumValue[i] = 0;
		ADC_Count[i] = 0;
		encOffset[i] = Re_uptrendTab(&TemTab[i].EnvTemOffset,env);	
		R = (adj*3270*1000/4095)/101.2004008; 
		R = inertiaFilter(&filter[i],R) + encOffset[i];
		temperature[i].PV10 =uptrendTab(&TemTab[i].Tem,R);
	}
	/*temperature[7].SV10=*/Env = env;
	if(Envofs>0) Envofs--;
	Times[Sampler] = 80;
}


