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
//	u16 i=512;//旋转一周时间
	u16 i=128;//旋转1/4周时间
	while(i--)  //正向
	{		
		GPIO_Write(GPIOB,0x11);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x22);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x44);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x88);
		delay_ms(3);//改变相应的时间，可以改变速度
	}
}
//
void backward(void)
{
//	u16 i=512;//旋转一周时间
	u16 i=128;//旋转1/4周时间
	while(i--)//反向
	{
		GPIO_Write(GPIOB,0x88);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x44);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x22);
		delay_ms(3);//改变相应的时间，可以改变速度
		GPIO_Write(GPIOB,0x11);
		delay_ms(3);//改变相应的时间，可以改变速度
	}
}

/***************************************END OF FILE*************************/
