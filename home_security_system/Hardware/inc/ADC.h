#ifndef __ADC_H
#define __ADC_H 			   
#include "ADC.h"
#include "delay.h" 
#include "stm32f10x.h"
		   
//��ʼ��ADC
//����Ĭ�Ͻ�����ͨ��0~3																	   
void  Adc_Init(void);				  
//���ADCֵ
//ch:ͨ��ֵ 0~3
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);	 

#endif











