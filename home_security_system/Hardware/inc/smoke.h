#ifndef __SMOKE_H
#define __SMOKE_H 			   
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "led.h"
#include "key.h"		
#include "usart2.h" 
#include "ADC.h"
#include "stdio.h"
#include "lcd.h"

extern u16 adcx;
extern float temp;

void smoke(void);

#endif			 
