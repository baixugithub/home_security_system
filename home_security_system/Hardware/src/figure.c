#include "figure.h"
unsigned char dat[18];
unsigned char 	SaveNumber=0,searchnum=0;
unsigned int  	SearchNumber=0;		
unsigned char str[3]={0,'\0','\0'};
u8 modeflag=0,clearallflag=0,changeflag=0;//默认为识别模式，如果为1为录入指纹模式,每录入一次SaveNumber++

// 说明：这个函数就是检测是否有指纹输入的信息，根据用户手册，当确认码返回值为0时，表示成功录入，所以，我们可以有下面的函数：
////检测指纹模块录入指纹情况，返回00表示录入成功；02无手指；03录入失败

u8 Command(unsigned char *p,u8 MaxTime, u8 Receive) //命令解析,给模块发送一个命令
{
  	u8 i;
	unsigned char temp; 
	for (i=0;i<MaxTime;i++) //发送命令 0x1d
	{
 		temp = *p++;//取第个“1”个元素的内容，然后发送 
		USART3_SendByte(temp);	
	}
	for (i=0;i<Receive;i++)//读回应答信息
		dat[i] = USART3_ReceivByte();
	if (dat[9]==0)
	{
		return 1;
	}
	return 0;	   	
}
//FINGERPRINT_获得指纹图像命令
//void FINGERPRINT_Cmd_Get_Img(void)
//{
//	Command(Get_Img, 12, 12);
//}   
//// 
//void VefPSW(void)//验证设备握手口令,成功返回1     
//{
//	Command(VPWD, 16, 12);
//}
//
//void Clear_All(void) //清空指纹库   
//{				
//	Command(DELE_all, 12, 12);
//}
//
u8 ImgProcess(unsigned char BUFID)  //发获取图像并生成特征文件，存入BUFID中//输入参数为缓冲区号  
{						   
    if(Command(GIMG,12,12))  
    {
		if(BUFID==1)      
		{	   			
      		if(Command(GENT1,13,12))  
        	{							
				return 1;
			}  
        	else
        	{
  				return 0;
         	}
		 }
		else if(BUFID==2)
		{
      		if(Command(GENT2,13,12))  
        	{				
				return 1;
			}  
        	else
        	{
  				return 0;
         	}			
		}
    }
    else
    {
      return 0;       
    }
	return 0;             
}
//
u8 Searchfinger(void)//搜索指纹(发送搜索命令、以及根据返回值确定是否存在)        
{		
   	if(Command(SEAT,17,16)) //搜索到指纹 
    {
		SearchNumber=dat[10]*0x100+dat[11];//搜索到的页码
		//MatchScore=FIFO[12]*0x100+FIFO[13]   可以在此计算得分，从而进行安全级别设定，本程序忽略
	   	return 1;
	}     
    else             
    {
       	return 0;
    }  
}
//
unsigned char search(void)//搜索用户 
{
 	unsigned char SearchBuf=0,i=0;
  	while (i<20)
    {
     	if (ImgProcess(1)==1)//首先读入一次指纹  
       	{
       		SearchBuf=Searchfinger();//进行指纹比对，如果搜索到，返回搜索到的指纹序号
       		if(SearchBuf==1)
       		{
       			return SearchNumber; 
       		}
       		else 
			{
			   return 255;//表示搜索到的指纹不正确
			}     
       	}
		i++;	
    }
   return 0;
}
//
u8 savefingure(unsigned char ID)//保存指纹
{
	 unsigned char i=0;
	 //现在开始进行存储指纹模板的操作
     for (i=0;i<16;i++)	//保存指纹信息
	{
		dat[i]=STOR[i];
	}  
	dat[12]=ID; //把指纹模板存放的PAGE_ID也就是FLASH的位置
	dat[14]=dat[14]+ID;	//校验和
	if (Command(dat,16,12)==1)//不成功返回0	//此处进行存放指纹模板的命
		return(1);
	else
		return(0); //不成功返回0
}//
u8 enroll(void) //采集两次指纹，生成1个 指纹模板		/////////////////我修改=========================
{
 	unsigned char temp=0,count=0;
  	while(1)
  	{
  	 	temp = ImgProcess(1); //生成特征1    
   		if (temp==1)//生成特征文件成功             
      	{  		      
        	//采集第一个特征成功 
		   	count=0;  
		  	buzzer=1;	//焊蜂鸣器
			delay_ms(100);	//焊蜂鸣器
			buzzer=0;		//焊蜂鸣器
			break;
       	}
     	else                   
       	{
        	if (temp==0)//采集指纹没有成功
          	{ 
				count++;
            	if (count>=40)//如果采集了40次，还不成功，直接采集失败，直接退出enroll函数－－－－返回0  
					return(0);
            }
        }
   	}

	//采集第一个特征成功 
   	count=0;  
  	buzzer=1;	  
	delay_ms(100); 
	buzzer=0;	   //close_buzzer
	delay_ms(2000);//延时2S开始采集下一个特征

	//开始采集第二个特征 
 	while(1)
  	{
   		temp=ImgProcess(2); //生成特征2    
   		if (temp==1)//生成特征文件2成功
      	{
        	if (Command(MERG,12,12)) //合并成功返回1
			{
			     buzzer=1;		 //开蜂鸣器
	             delay_ms(100);
	             buzzer=0;
				 delay_ms(100);
				 buzzer=1;
	             delay_ms(100);	//响两声，表示生成一个模板成功
	             buzzer=0; 
				 return(1);
			}
			else
			{
			   return(0);
			}		
        }
      	else      
       	{	
        	if (temp==0)//采集指纹没有成功
        	{
				count++;				
				if (count>=25) 				
				return(0);
       		}
     	}
   	}
}
//
void shownum(unsigned char dat)
{
	unsigned char numdat=0;
	numdat=dat;
	str[0]=0x30+numdat/10;
	str[1]=0x30+numdat%10;
}
//
void mode(void)
{
	 if(modeflag==0)
	 {
		LED1=0;
		LED0=1;
	 }
	 else
	 {

		LED0=0;
		LED1=1;
	 }
	 shownum(0);
}
void Figure_Test(void)//主函数
{
	u8 i;
	mode();//看当前是什么模式
	
	for(i=0;i<6;i++)//开始握手6次，如果没有一次成功，表示模块通信不正常。只要成功就跳出此循环
	{
		if(Command(VPWD, 16, 12))//与模块握手通过，绿灯亮起。进入识别模式
		{
			LED1 = 0; //读一次
			delay_ms(30);
			buzzer = 1;
			shownum(0);
			delay_ms(300);
			buzzer = 0;
			break;	
		}
	    else
		 {
			LED0=1; 
			LED1=1;
			break;

		 }
	}

	while(1)
	{
//		if(modeflag==1)//录入一个指纹
//		{
//			if(enroll()==1)//采集两次，生成1个指纹模板成功
//		  	{
//			   if(savefingure(SaveNumber+1))//保存也成功
//			   	{
//					SaveNumber++;//加一次
//					shownum(SaveNumber);
//				}		
//			}
//			else
//			{
//				buzzer=0; 
//				for(i=0;i<5;i++)
//				{
//				  delay_ms(10);
//				  LED0=~LED0;
//				}
//				LED0=0;
//				buzzer=1;									
//			}  						
//		}
		if(modeflag==0)//为识别模式
		{
			searchnum=search();
			if(searchnum>=1&&searchnum<=162)//最多是162个指纹
			{
				shownum(searchnum);
				if (searchnum==1)
  			    {
					forward();	//  开门			
				}
				if (searchnum==2)
				{
					backward();   //关门
				}
//					while(1)		 //修改使其实现功能^_^
//					{
//					  	red = 0;
//						green = 0;
//						delay_ms(50);
//					  	red = 1;
//						green = 1;
//						delay_ms(50);
//					
//					}
			    }
			   //蜂鸣器响一声
			   buzzer=1;
			   delay_ms(100);
			   buzzer=0;
			   for(i=0;i<20;i++)
			   {
					delay_ms(50);
			   }
			}
			if(searchnum==255)//不正确的指纹 蜂鸣器响三声
			{
			   shownum(0);
			   buzzer=1;delay_ms(100); buzzer=0;delay_ms(100);
			   buzzer=1;delay_ms(100); buzzer=0;delay_ms(100);
			   buzzer=1;delay_ms(100); buzzer=0;delay_ms(100); 
			}
			if (clearallflag==1)
			{
				delay_ms(10);
				if (clearallflag==1)
				{
					break;
				}
			}
		

//		if(clearallflag==1)
//		{
//			clearallflag=0;
//			Command(DELE_all, 12, 12); //清除所有指纹
//		    LED0=0;	     //红色灯亮
//		    LED1=1;
//			//蜂鸣器长响一次，表示清除所有指纹结束
//			modeflag=1;//进入录入指纹模式
//			shownum(0);
//			buzzer=1;
//			delay_ms(300);
//			buzzer=0;
//			SaveNumber=0;
//		}
//		if(changeflag==1)
//		{
//			mode();//显示当前模式	
//			changeflag=0;
//		}
	}
}
//
