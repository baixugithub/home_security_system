#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"
#include "sys.h"


void USART3_Config(u32 bound);
//串口发送信息,通过查询方式发送一个字符
void USART3_SendByte(unsigned char dat);
// 从 USART3 读取一个字节
unsigned char USART3_ReceivByte(void);


#endif
