#ifndef __ADC_H
#define	__ADC_H


#include "stm32f10x.h"

// ת��ͨ������
#define    macNOFCHANEL											9

extern __IO uint16_t ADC_ConvertedValue[macNOFCHANEL];
extern __IO uint16_t ADC_Count[macNOFCHANEL];
extern __IO uint32_t ADC_SumValue[macNOFCHANEL];

/**************************��������********************************/
void ADCx_Init(void);
void AdcProc(void);

#endif 

