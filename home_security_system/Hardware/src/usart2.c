#include "delay.h"
#include "usart2.h"

void USART_Config(u32 bound)
{
    GPIO_InitTypeDef  GPIO_InitStructure;
    USART_InitTypeDef USART_InitStructure;
//	NVIC_InitTypeDef NVIC_InitStructure;

    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

    //配置USART2 TX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //配置USART2 RX引脚工作模式
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

   //Usart2 NVIC 配置
//	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
//	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;
//	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//
//
//	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
//	NVIC_Init(&NVIC_InitStructure);	//根据NVIC_InitStruct中指定的参数初始化外设NVIC寄存器USART1
  
    //串口2工作模式配置
    USART_InitStructure.USART_BaudRate = bound;
    USART_InitStructure.USART_WordLength = USART_WordLength_8b;
    USART_InitStructure.USART_StopBits = USART_StopBits_1;
    USART_InitStructure.USART_Parity = USART_Parity_No ;
    USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
    USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
    USART_Init(USART2, &USART_InitStructure);
    USART_Cmd(USART2, ENABLE);

//	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断

	USART_ClearFlag(USART2, USART_FLAG_TC);//清标志
}
//
//串口发送信息,通过查询方式发送一个字符
void USART2_SendByte(unsigned char dat)
{
	USART_SendData(USART2, dat);
	while(USART_GetFlagStatus(USART2, USART_FLAG_TXE) == RESET); //等待发送结束
}
//
void USART2_String(uint8_t *str)
{
    while (0 != *str)    
    {    
        USART2_SendByte(*str);    
        str++;    
    }    
} 
//
/***************************************END OF FILE*************************/
