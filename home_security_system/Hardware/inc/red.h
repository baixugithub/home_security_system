#ifndef __RED_H
#define __RED_H 			   
#include "stm32f10x.h"
#include "sys.h"
#include "delay.h"	
#include "led.h"
#include "key.h"		
#include "usart2.h" 
#include "ADC.h"

#define red  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//¶ÁÈ¡°´¼ü0
extern u8 Flag_Red; 

void Red_init(void);
#endif
