#ifndef __SIM900A_H__
#define __SIM900A_H__	 
#include "sys.h"
#include "delay.h"	
#include "led.h"
#include "key.h"		
#include "usart2.h" 
#include "ADC.h"
#include "stdio.h"
#include "lcd.h"
#include "smoke.h"

#include "sim900a.h"

//SIM900A发短信测试 【红外】
void sim900a_sms_red(void);
//
//SIM900A发短信测试 【火灾】
void sim900a_sms_fire(void);
//
//SIM900A发短信测试 【烟雾】
void sim900a_sms_smoke(void);


#endif





