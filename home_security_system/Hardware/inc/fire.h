#ifndef __FIRE_H
#define __FIRE_H 			   
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "led.h"
#include "key.h"		
#include "usart2.h" 
#include "ADC.h"

#define FIRE  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_7)//∂¡»°

extern u8 Flag_Fire; 

void FIRE_init(void);

#endif
