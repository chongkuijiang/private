
#ifndef __FILTER_H_
#define __FILTER_H_

#include <stdint.h>
#include <stdlib.h>

//--------------------------------------------------
typedef uint16_t value_t; //���Ͷ��壬����д
//--------------------------------------------------

typedef struct
{
	value_t amplitude; //���
	value_t val_1;   	
	
}Limiter_t;  //�޷��˲�

typedef struct
{
    value_t amplitude; //���
	value_t val_1; 
    value_t val_2;
    value_t val_3;		
	
}SpeedLimiter_t;  //�����˲�

typedef struct
{
	value_t val_1;   
	value_t val_2;
	value_t val_3;
}Inertia_t;  //�����˲�




//-------------------------------------------------

value_t limiter(Limiter_t filter,value_t input); //�޷��˲�
value_t speedLimiter(SpeedLimiter_t filter,value_t input); //�����˲�
value_t inertiaFilter(Inertia_t filter,value_t input);  //�����˲�
//value_t averageFilter(

#endif

