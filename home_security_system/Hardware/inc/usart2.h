#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

void USART_Config(u32 bound);
//串口发送信息,通过查询方式发送一个字符
void USART2_SendByte(unsigned char dat);
// 从 USART2 读取一个字节
void USART2_String(uint8_t *str);

#endif













