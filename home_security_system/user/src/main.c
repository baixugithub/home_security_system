#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "key.h"
#include "sim900a.h"	
#include "usart2.h"	
#include "usart3.h"
#include "red.h"
#include "ADC.h"
//#include "lcd.h"
#include "smoke.h"
#include "fire.h"
#include "dht11.h"
#include "motor.h"
#include "figure.h"
#include "exti.h"
#include "beep.h"

int main(void)
{
	u8 t=0;			    
	u8 temperature;  	    
	u8 humidity;    	   
	u16 adcx;
/*************************************/
	int T_shi;	 //�¶�
	int T_ge;
	int T_point;

	int H_shi;	//ʪ��
	int H_ge;
	int H_point;

	int S_shi;  //����
	int S_ge;
	int S_point;

/*************************************/ 
	delay_init();	    	 //��ʱ������ʼ��	  
	LED_Init();
	NVIC_Configuration();	 
	uart_init(9600);
	USART_Config(115200);
	USART3_Config(9600);
	Adc_Init();
	BEEP_Init();
	EXTIX_Init();
	KEY_Init();
	motor_init();
	    
// 	while(DHT11_Init())	//DHT11��ʼ��	
//	{
//		delay_ms(200);
// 		delay_ms(200);
//	}								   
	delay_ms(5000);				   
	delay_ms(5000);				   
	while(1)
	{

		if(t%10==0)//ÿ100ms��ȡһ��
		{									  
			DHT11_Read_Data(&temperature,&humidity);		//��ȡ��ʪ��ֵ					    
		}
		{//����1�����¶�
			delay_ms(5);
			T_shi = temperature/10 + 0x30;
			Uart1_PutChar(T_shi);
			delay_ms(5);
			T_ge = temperature%10 + 0x30;
			Uart1_PutChar(T_ge);
			delay_ms(5);
			T_point = temperature/100 + 0x30;
			Uart1_PutChar(T_point);
			delay_ms(5);
			T_point = temperature/100 + 0x30;
			Uart1_PutChar(T_point);
			delay_ms(5);
		}
		{//����1����ʪ��
			delay_ms(5);
			H_shi = humidity/10 + 0x30;
			Uart1_PutChar(H_shi);
			delay_ms(5);
			H_ge = humidity%10 + 0x30;
			Uart1_PutChar(H_ge);
			delay_ms(5);
			H_point = humidity/100 + 0x30;
			Uart1_PutChar(H_point);
			delay_ms(5);
			H_point = humidity/100 + 0x30;
			Uart1_PutChar(H_point);
			delay_ms(5);

		}		   
		   
//		smoke();//�����������ص�ֵ
		adcx=Get_Adc_Average(ADC_Channel_4,10);	 //ͨ��4 _PA.4����������

		{//����1��������ֵ
			if(adcx < 100)
			{
				delay_ms(5);
				S_point = adcx/100 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
				S_point = adcx/100 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
				S_shi = adcx/10 + 0x30;
				Uart1_PutChar(S_shi);
				delay_ms(5);
				S_ge = adcx%10 + 0x30;
				Uart1_PutChar(S_ge);
				delay_ms(5);
			
			}
			if(adcx >= 100 & adcx < 1000)
			{
				delay_ms(5);
				S_point = adcx/10000 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
				S_shi = adcx/100 + 0x30;
				Uart1_PutChar(S_shi);
				delay_ms(5);
				S_ge = adcx%100/10 + 0x30;
				Uart1_PutChar(S_ge);
				delay_ms(5);
				S_point = adcx%100%10 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
			}
			if(adcx >= 1000 & adcx < 5000)
			{
				delay_ms(5);
				S_shi = adcx/1000 + 0x30;
				Uart1_PutChar(S_shi);
				delay_ms(5);
				S_ge = adcx%1000/100 + 0x30;
				Uart1_PutChar(S_ge);
				delay_ms(5);
				S_point = adcx%1000%100/10 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
				S_point = adcx%1000%100%10 + 0x30;
				Uart1_PutChar(S_point);
				delay_ms(5);
			}

		}
		if (adcx>1500)	  
		{
			delay_ms(10);
			sim900a_sms_smoke();		//���Ų���
		}
		Red_init();
		if (1==Flag_Red)	  
		{
			delay_ms(10);
			sim900a_sms_red();		//���Ų���
			Flag_Red = 0;
		}
		FIRE_init();
		if (1==Flag_Fire)	  
		{
			delay_ms(10);
			sim900a_sms_fire();		//���Ų���
			Flag_Fire = 0;

		}
		//		motor_decive();//���Բ�������Ƕ�
		if (k1 == 0)
		{
			delay_ms(10);
			if (k1 == 0)
			{
				Figure_Test();//ָ��ʶ���			
			}
		}s
		LED0=!LED0;
		delay_ms(10);	

	}


}
