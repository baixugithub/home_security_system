#ifndef _BEEP_H_
#define _BEEP_H_			   
#include "stm32f10x.h"
#include "delay.h"
#include "sys.h"

#define buzzer PCout(12)	// buzzer,·äÃùÆ÷½Ó¿Ú		   

void BEEP_Init(void);	
void beep(void);


#endif 
