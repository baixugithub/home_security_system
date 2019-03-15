#ifndef __ADC_H
#define __ADC_H 			   
#include "ADC.h"
#include "delay.h" 
#include "stm32f10x.h"
		   
//初始化ADC
//我们默认将开启通道0~3																	   
void  Adc_Init(void);				  
//获得ADC值
//ch:通道值 0~3
u16 Get_Adc(u8 ch);
u16 Get_Adc_Average(u8 ch,u8 times);	 

#endif











