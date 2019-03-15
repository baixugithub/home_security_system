#ifndef __FIGURE_H
#define __FIGURE_H 			   
#include "stm32f10x.h"
#include "stdio.h"
#include "led.h"
//#include "lcd.h"
#include "delay.h"
#include "usart3.h"
#include "key.h"
#include "exti.h"
#include "motor.h"
#include "beep.h"


extern u8 modeflag;
extern u8 clearallflag;
extern u8 changeflag;//默认为识别模式，如果为1为录入指纹模式,每录入一次SaveNumber++

//协议包头
//static unsigned char Pack_Head[6] = {0xEF,0x01,0xFF,0xFF,0xFF,0xFF};      
static unsigned char Get_Img[12] ={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
								 0x01,0x00,0x03,0x01,0x0,0x05};//回送12个
//Verify  Password   ：验证设备握手口令
static unsigned char VPWD[16]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
							   0x01,0x00,0x07,0x13,0x00,0x00,0x00,0x00,0x00,0x1b};//回送12个
//DEL templet      ;清空指纹库
static unsigned char DELE_all[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
								   0x01,0x00,0x03,0x0d,0x00,0x11};	//会送12个

//GetImage           ：探测手指并从传感器上读入图像(录指纹图像)
static unsigned char GIMG[14]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
							   0x01,0x0,0x03,0x01,0x00,0x05};	//回送12个
//Gen Templet1        ：根据原始图像生成指纹特征1
static unsigned char GENT1[13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
								0x01,0x00,0x04,0x02,0x01,0x00,0x08};	//回送12个

//Gen Templet2        ：根据原始图像生成指纹特征2
static unsigned char GENT2[13]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
								0x01,0x00,0x04,0x02,0x02,0x00,0x09}; //回送12个	

//Search Finger      ：以CharBufferA或CharBufferB中的特征文件搜索整个或部分指纹库(特征合成模板)
static unsigned char SEAT[17]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
							   0x01,0x00,0x08,0x04,0x01,0x00,0x00,0x00,0x65,0x00,0x73};	//回送16个

//Store Templet      ：将ModelBuffer中的文件储存到flash指纹库中
static unsigned char STOR[16]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
							   0x01,0x00,0x06,0x06,0x02,0x00,0x00,0x00,0x0f}; //回送12个
//Merge Templet      ;将CharBufferA与CharBufferB中的特征文件合并生成模板，结果存于ModelBuffer。
static unsigned char MERG[12]={0xEF,0x01,0xFF,0xFF,0xFF,0xFF,\
							   0x01,0x00,0x03,0x05,0x00,0x09};//回送12个	
////设置设备握手口令
//static unsigned char STWD[16]={16,0X01 ,0Xff,0xff,0xff,0xff, 0x01,0,7,0x12,0x00,0x00,0x00,0x00,0x00,0x1a};	 //回送12个
//
//	
//
//
//
////Read Note
//static unsigned char RDNT[14]={13,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,4,0x19,  0, 0x00,0x1e};
//
////Clear Note
//static unsigned char DENT[46]={45,0X01 ,0Xff,0xff,0xff,0xff, 0x01, 0,36,0x18,0,0,0,
//0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0x00,0x3d};
//
////DEL one templet
//static unsigned char DELE_one[16]={16, 0X01 ,0Xff,0xff,0xff,0xff, 0x01,   0,7,  0x0c,    0x00,0x00, 0,1, 0x00,0x15};
//
//
//////////////////////////////////////常用指令定义-------结束///////////////////////////////////////////////////////////////////////////////////////


//FINGERPRINT_获得指纹图像命令
void FINGERPRINT_Cmd_Get_Img(void);

//因此，我们在主函数中可以这样调用：
void Figure_Test(void);//主函数

#endif 
