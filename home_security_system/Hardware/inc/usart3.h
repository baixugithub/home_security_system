#ifndef __USART3_H
#define __USART3_H
#include "stdio.h"
#include "sys.h"


void USART3_Config(u32 bound);
//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
void USART3_SendByte(unsigned char dat);
// �� USART3 ��ȡһ���ֽ�
unsigned char USART3_ReceivByte(void);


#endif
