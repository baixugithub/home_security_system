#include "exti.h" 

//�ⲿ�жϷ������
//��ʼ��PA0,PA13,PA15Ϊ�ж�����.
void EXTIX_Init(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;


//  	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable , ENABLE);	//�ر�jtag

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO,ENABLE);

  //��ʼ�� KEY0-->GPIOA.13,KEY1-->GPIOA.15  ��������
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_13|GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);
 // ��ʼ�� WK_UP-->GPIOA.0	  ��������
  	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_0;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD; 
  	GPIO_Init(GPIOA, &GPIO_InitStructure);

  //GPIOA.13 �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource13);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line13;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	 	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

 //GPIOA.15	  �ж����Լ��жϳ�ʼ������
  	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource15);

  	EXTI_InitStructure.EXTI_Line=EXTI_Line15;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);	  	//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���

    //GPIOA.0	  �ж����Լ��жϳ�ʼ������
 	GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0);

 	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
  	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
  	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;
  	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;					//�����ȼ�1
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure); 
  
  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ������ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x02;					//�����ȼ�2 
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  	  //����NVIC_InitStruct��ָ���Ĳ�����ʼ������NVIC�Ĵ���
}

 
void EXTI0_IRQHandler(void)
{
	if (EXTI_GetITStatus(EXTI_Line0) != RESET)	  //���ָ����EXTI0��·�������������
	{	  
		if (k3==1)
		{
			delay_ms(5);
			if (k3==1)
			{
				modeflag = 0;
				changeflag=1;			
			}		
		}
	}
	EXTI_ClearITPendingBit(EXTI_Line0);  //���EXTI0��·����λ
}
 
void EXTI15_10_IRQHandler(void)
{ 
    if (EXTI_GetITStatus(EXTI_Line13) != RESET) //ʶ��ָ��
	{
		modeflag = 0;
		changeflag = 1;//ģʽ������ת��			
	}
	else if (EXTI_GetITStatus(EXTI_Line15) != RESET)//ģʽת��
	{
//		modeflag = 0;

		clearallflag = 1;
//		changeflag = 1;
	}
	EXTI_ClearITPendingBit(EXTI_Line13);  //���EXTI13��·����λ
	EXTI_ClearITPendingBit(EXTI_Line15);  //���EXTI15��·����λ
}
