
#ifndef __FILTER_H_
#define __FILTER_H_

#include <stdint.h>
#include <stdlib.h>

//--------------------------------------------------
typedef uint16_t value_t; //类型定义，可重写
//--------------------------------------------------

typedef struct
{
	value_t amplitude; //振幅
	value_t val_1;   	
	
}Limiter_t;  //限幅滤波

typedef struct
{
    value_t amplitude; //振幅
	value_t val_1; 
    value_t val_2;
    value_t val_3;		
	
}SpeedLimiter_t;  //限速滤波

typedef struct
{
	value_t val_1;   
	value_t val_2;
	value_t val_3;
}Inertia_t;  //惯性滤波




//-------------------------------------------------

value_t limiter(Limiter_t filter,value_t input); //限幅滤波
value_t speedLimiter(SpeedLimiter_t filter,value_t input); //限速滤波
value_t inertiaFilter(Inertia_t filter,value_t input);  //惯性滤波
//value_t averageFilter(

#endif

