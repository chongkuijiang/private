
#include "lookUp.h"


//----------------------------------------------------------------------------------
// 功能: 查下降趋势表,返回表的下标,常用于NTC测温。
// 参数: tab-每个对像要创建一个变量
// 输入：R-(整数)
// 输出: 输出float值
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
// 功能: 查上升趋势表,返回表的下标,常用于热电耦测温。
// 参数: tab-每个对像要创建一个变量
// 输入：volt-(整数)
// 输出: 输出float值
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
// 功能: 反向查上升趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
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
// 功能: 反向查下降趋势表,返回数值域。
// 参数: tab-不修改对象中的变量
// 输入：volt-(整数)
// 输出: 输出float值
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
// 功能: 初始化一个查表对象
// 参数: tab-对象指针，Tab-表指针... 
void init_LookUp(lookUp_param_t *tab,tablt_t *Tab,
	uint16_t step,int16_t min,uint16_t maxIndex) //创建查趋势表方法
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
int32_t inertiaFilter(Inertia_t* filter,int32_t input)  //惯性滤波
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

lookUp_param_t EnvTem;
uint16_t  HTofs[9];
thermocouple_t TemTab[8];
Inertia_t filter[9];
//---------------------------------------------------------
static void LoadData(void)
{
	int i;
	 CommIIC((uint8_t*)&ParSave, sizeof(Save_t), 0, 1 );
	 if(ParSave.EE!= 0xea){
		ParSave.EE = 0xea;
		ParSave.lock = 1;
		ParSave.HTofs[8] = 900;
		ParSave.Calib.top = 3839;
		ParSave.Calib.bottom = 455;
		ParSave.Calib.left = 208;
		ParSave.Calib.right = 3935;			 
		for(int i=0;i<8;i++){			
		   ParSave.Tem[i].sv = 2500;
			ParSave.Tem[i].sv01 = 100; 	
			ParSave.Tem[i].cf = 0;
			ParSave.Tem[i].jk = 1;
			ParSave.Tem[i].sw = 0;
         ParSave.HTofs[i] = 1000;				
		}
		CommIIC(&ParSave, sizeof(Save_t), 0, 0 );
	}  
}
//---------------------------------------------------------
void Tem_Init(void)
{	
	LoadData();
	HTofs[8] = ParSave.HTofs[8];
	locked = ParSave.lock;		
	init_LookUp(&EnvTem,NTC103_3435tab,10,-400,165); //*10	
	for(int i=0;i<8;i++){
		temperature[i].SV10 = ParSave.Tem[i].sv;
		temperature[i].SV01 = ParSave.Tem[i].sv01;
		temperature[i].jk = ParSave.Tem[i].jk;
		temperature[i].cf = ParSave.Tem[i].cf;
		temperature[i].on_off = ParSave.Tem[i].sw;
		HTofs[i] = ParSave.HTofs[i];
		if(ParSave.Tem[i].jk){
			init_LookUp(&TemTab[i].EnvTemOffset,JTtab,10,-2090,1409); 
			init_LookUp(&TemTab[i].Tem,JTtab,10,-2090,1409); //*10
		}else{
			init_LookUp(&TemTab[i].EnvTemOffset,KTtab,10,-590,1431); 
			init_LookUp(&TemTab[i].Tem,KTtab,10,-590,1431); //*10
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
			init_LookUp(&TemTab[index].EnvTemOffset,KTtab,10,-590,1431); 
			init_LookUp(&TemTab[index].Tem,KTtab,10,-590,1431); //*10
		}
		Ones[save].delay = 3000;
	}
}
//-----------------------------------------------------------
void OFSchang(void)
{
	for(int i=0;i<9;i++){
	   ParSave.HTofs[i] = HTofs[i];
	}
	Ones[save].delay = 3000;
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
void SV01chang(uint8_t index,uint16_t sv)
{
	uint16_t last;
	last = temperature[index].SV01;
	temperature[index].SV01 = sv;
	ParSave.Tem[index].sv01 = sv;
	if(last != temperature[index].SV01) 
	Ones[save].delay = 3000;
}
//----------------------------------------------------------
void SWchang(uint8_t index,uint16_t sv)
{
	uint16_t last;
	last = temperature[index].on_off;
	temperature[index].on_off = sv;
	ParSave.Tem[index].sw = sv;
	if(last != temperature[index].on_off) 
	Ones[save].delay = 3000;
}
//----------------------------------------------------------
uint16_t Env;
void getEnv(void)
{
	int32_t adj,R,R2,env,encOffset[8],i;	
	adj = ADC_SumValue[8]/ADC_Count[8];
	ADC_SumValue[8] = 0;
	ADC_Count[8] = 0;	
	//adj*SYS.DataSet[ET_Z]*10/(4095*25/33-adj);
	 R = HTofs[8]*10*adj/(4095*25/33-adj); //R
	
	Env = env = downtrendTab(&EnvTem,inertiaFilter(&filter[8],R));
	for(i=0;i<8;i++)
	{
		adj = ADC_SumValue[i]/ADC_Count[i];
		ADC_SumValue[i] = 0;
		ADC_Count[i] = 0;
		encOffset[i] = Re_uptrendTab(&TemTab[i].EnvTemOffset,env);	
		R = adj*33*HTofs[i]/4095;// /101.2004008; 
		R2 = inertiaFilter(&filter[i],R) + encOffset[i];
		temperature[i].PV10 =uptrendTab(&TemTab[i].Tem,R2);		
	} 
	Times[Sampler] = 150;
	dispTemPanel();
}


