#include "usart3.h"


 /**
  * @说明     USART3 相关GPIO和工作模式配置
  * @参数     None 
  * @返回值   None
  */
void USART3_Config(u32 bound)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

    //配置USART2 TX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //配置USART2 RX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //串口2工作模式配置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART3, &USART_InitStructure);
    USART_Cmd(USART3, ENABLE);

	USART_ClearFlag(USART3, USART_FLAG_TC);//清标志
}
//
//串口发送信息,通过查询方式发送一个字符
void USART3_SendByte(unsigned char dat)
{
	USART_SendData(USART3, dat);
	while(USART_GetFlagStatus(USART3, USART_FLAG_TXE) == RESET);
}
//
// 从 USART3 读取一个字节
unsigned char USART3_ReceivByte()
{
	unsigned char recev;
	while(USART_GetFlagStatus(USART3, USART_FLAG_RXNE) == RESET);
	recev = USART_ReceiveData(USART3);
	return recev;
}

