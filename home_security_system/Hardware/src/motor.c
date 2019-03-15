#include "motor.h"

void motor_init(void)
{			   
	GPIO_InitTypeDef GPIO_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
//	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_All;	//  
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Mode =	GPIO_Mode_Out_PP;
	GPIO_Init(GPIOB, &GPIO_InitStruct); //GPIOB
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);

}
//
void forward(void)
{
//	u16 i=512;//��תһ��ʱ��
	u16 i=128;//��ת1/4��ʱ��
	while(i--)  //����
	{		
		GPIO_Write(GPIOB,0x11);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x22);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x44);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x88);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
	}
}
//
void backward(void)
{
//	u16 i=512;//��תһ��ʱ��
	u16 i=128;//��ת1/4��ʱ��
	while(i--)//����
	{
		GPIO_Write(GPIOB,0x88);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x44);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x22);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
		GPIO_Write(GPIOB,0x11);
		delay_ms(3);//�ı���Ӧ��ʱ�䣬���Ըı��ٶ�
	}
}

/***************************************END OF FILE*************************/
