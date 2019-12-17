
#ifndef __LOOK_UP_H_
#define __LOOK_UP_H_

#include <stdint.h>

//---------------------------------------------------
typedef const int32_t tablt_t;  //类型定义，可重写
//---------------------------------------------------
typedef struct 
{
    tablt_t   *Tab; //表格(降趋势表取最大值表,上升趋势表取最小值)	
	uint16_t  index;  //上一次表格素引
	uint16_t  pace; //输出值步距
	int16_t   min;   //输出值最小值(可负值)	
	uint16_t  maxIndex; //表格的最大素引值
	
}lookUp_param_t;

#endif
