#include "beep.h"

void BEEP_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	 //ʹ��GPIOB�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;				 //BEEP-->PB.8 �˿�����
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	 //�ٶ�Ϊ50MHz
	GPIO_Init(GPIOC, &GPIO_InitStructure);	 //���ݲ�����ʼ��GPIOB.8
	
	GPIO_ResetBits(GPIOC,GPIO_Pin_12);//���0���رշ��������
}
//	
void beep(void)
{
	GPIO_SetBits(GPIOC,GPIO_Pin_12);
	delay_ms(500);		 
	GPIO_ResetBits(GPIOC,GPIO_Pin_12);//���0���رշ��������
	delay_ms(500);	
}
//
