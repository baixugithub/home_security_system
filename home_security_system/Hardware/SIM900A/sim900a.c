#include "sim900a.h"

//SIM900A�����Ų��� �����⡿
void sim900a_sms_red(void)
{ 
	USART2_String("AT+CSCS=\"UCS2\"\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CSMP=17,167,2,25\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGF=1\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGS=\"00310033003600330039003300310033003200310036\"\r\n");//���ͽ�����
	//13639313216
	delay_ms(100);
	USART2_String("67094EBA975E6CD595EF5165FF0C8BF77ACB537367E5660E60C551B5FF01");// ���Զ���
	delay_ms(100);
	USART2_SendByte(0X1A);//���ͽ�����

} 
//
//SIM900A�����Ų��� �����֡�
void sim900a_sms_fire(void)
{ 
	USART2_String("AT+CSCS=\"UCS2\"\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CSMP=17,167,2,25\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGF=1\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGS=\"00310033003600330039003300310033003200310036\"\r\n");//���ͽ�����
	//13639313216
	delay_ms(100);
	USART2_String("706B707E98848B66FF018BF753CA65F6590474063002");// ���Զ���
	delay_ms(100);
	USART2_SendByte(0X1A);//���ͽ�����

} 
//
//SIM900A�����Ų��� ������
void sim900a_sms_smoke(void)
{ 
	USART2_String("AT+CSCS=\"UCS2\"\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CSMP=17,167,2,25\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGF=1\r\n");//���ͽ�����
	delay_ms(100);
	USART2_String("AT+CMGS=\"00310033003600330039003300310033003200310036\"\r\n");//���ͽ�����
	//13639313216
	delay_ms(100);
	USART2_String("661371C36C144F536B63572885135EF6FF0C8BF77ACB537363929664966960C5FF01");// ���Զ���
	delay_ms(100);
	USART2_SendByte(0X1A);//���ͽ�����

} 
//sim900a�����Գ���
//void sim900a_test(void)
//{
//
//	while(1)
//	{
//		smoke();
//		if(KEY1 == 0)
//		{
//			delay_ms(30);
//			sim900a_sms_send_test();		//���Ų���
//		}
//		LED0=!LED0;
//		delay_ms(250);	
//
//	}
//}
/***************************************END OF FILE*************************/
