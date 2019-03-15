#include "usart3.h"


 /**
  * @˵��     USART3 ���GPIO�͹���ģʽ����
  * @����     None 
  * @����ֵ   None
  */
void USART3_Config(u32 bound)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    //����USART2 TX���Ź���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //����USART2 RX���Ź���ģʽ
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //����2����ģʽ����
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

	USART_ClearFlag(USART3, USART_FLAG_TC);//���־
}
//
//���ڷ�����Ϣ,ͨ����ѯ��ʽ����һ���ַ�
void USART3_SendByte(unsigned char dat)
{
	USART_SendData(USART3, dat);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}
//
// �� USART3 ��ȡһ���ֽ�
unsigned char USART3_ReceivByte()
{
	unsigned char recev;
	while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
	recev = USART_ReceiveData(USART3);
	return recev;
}

