#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"

//sbit k2=P3^4; //¼��һ��ָ��
//sbit k1=P3^3; //ģʽʶ��ת��
//sbit k3=P3^2; //�������ָ�ƣ�10��ָ�������


#define k1 PCin(5)   //PC5 //ʶ��
#define k2 PAin(15)	  //PA15 //¼��
#define k3 PAin(0)	  //PA0  WK_UP //�������ָ�ƣ�10��ָ�������
	 
void KEY_Init(void);//IO��ʼ��
//u8   KEY_Scan(void);  //����ɨ�躯��					    
#endif
