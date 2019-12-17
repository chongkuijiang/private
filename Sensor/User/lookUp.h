
#ifndef __LOOK_UP_H_
#define __LOOK_UP_H_

#include <stdint.h>

//---------------------------------------------------
typedef const int32_t tablt_t;  //���Ͷ��壬����д
//---------------------------------------------------
typedef struct 
{
    tablt_t   *Tab; //���(�����Ʊ�ȡ���ֵ��,�������Ʊ�ȡ��Сֵ)	
	uint16_t  index;  //��һ�α������
	uint16_t  pace; //���ֵ����
	int16_t   min;   //���ֵ��Сֵ(�ɸ�ֵ)	
	uint16_t  maxIndex; //�����������ֵ
	
}lookUp_param_t;

#endif
