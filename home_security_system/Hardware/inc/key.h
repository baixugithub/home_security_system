#ifndef __KEY_H
#define __KEY_H	 
#include "stm32f10x.h"
#include "sys.h" 
#include "delay.h"

//sbit k2=P3^4; //录入一次指纹
//sbit k1=P3^3; //模式识别转换
//sbit k3=P3^2; //清除所有指纹（10个指纹清除）


#define k1 PCin(5)   //PC5 //识别
#define k2 PAin(15)	  //PA15 //录入
#define k3 PAin(0)	  //PA0  WK_UP //清除所有指纹（10个指纹清除）
	 
void KEY_Init(void);//IO初始化
//u8   KEY_Scan(void);  //按键扫描函数					    
#endif
