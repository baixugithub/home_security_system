#ifndef __USART2_H
#define __USART2_H	 
#include "sys.h"  

void USART_Config(u32 bound);
//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
void USART2_SendByte(unsigned char dat);
// �� USART2 ��ȡһ���ֽ�
void USART2_String(uint8_t *str);

#endif













