#include "figure.h"
unsigned char dat[18];
unsigned char 	SaveNumber=0,searchnum=0;
unsigned int  	SearchNumber=0;		
unsigned char str[3]={0,'\0','\0'};
u8 modeflag=0,clearallflag=0,changeflag=0;//Ĭ��Ϊʶ��ģʽ�����Ϊ1Ϊ¼��ָ��ģʽ,ÿ¼��һ��SaveNumber++

// ˵��������������Ǽ���Ƿ���ָ���������Ϣ�������û��ֲᣬ��ȷ���뷵��ֵΪ0ʱ����ʾ�ɹ�¼�룬���ԣ����ǿ���������ĺ�����
////���ָ��ģ��¼��ָ�����������00��ʾ¼��ɹ���02����ָ��03¼��ʧ��

u8 Command(unsigned char *p,u8 MaxTime, u8 Receive) //�������,��ģ�鷢��һ������
{
  	u8 i;
	unsigned char temp; 
	for (i=0;i<MaxTime;i++) //�������� 0x1d
	{
 		temp = *p++;//ȡ�ڸ���1����Ԫ�ص����ݣ�Ȼ���� 
		USART3_SendByte(temp);	
	}
	for (i=0;i<Receive;i++)//����Ӧ����Ϣ
		dat[i] = USART3_ReceivByte();
	if (dat[9]==0)
	{
		return 1;
	}
	return 0;	   	
}
//FINGERPRINT_���ָ��ͼ������
//void FINGERPRINT_Cmd_Get_Img(void)
//{
//	Command(Get_Img, 12, 12);
//}   
//// 
//void VefPSW(void)//��֤�豸���ֿ���,�ɹ�����1     
//{
//	Command(VPWD, 16, 12);
//}
//
//void Clear_All(void) //���ָ�ƿ�   
//{				
//	Command(DELE_all, 12, 12);
//}
//
u8 ImgProcess(unsigned char BUFID)  //����ȡͼ�����������ļ�������BUFID��//�������Ϊ��������  
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
u8 Searchfinger(void)//����ָ��(������������Լ����ݷ���ֵȷ���Ƿ����)        
{		
   	if(Command(SEAT,17,16)) //������ָ�� 
    {
		SearchNumber=dat[10]*0x100+dat[11];//��������ҳ��
		//MatchScore=FIFO[12]*0x100+FIFO[13]   �����ڴ˼���÷֣��Ӷ����а�ȫ�����趨�����������
	   	return 1;
	}     
    else             
    {
       	return 0;
    }  
}
//
unsigned char search(void)//�����û� 
{
 	unsigned char SearchBuf=0,i=0;
  	while (i<20)
    {
     	if (ImgProcess(1)==1)//���ȶ���һ��ָ��  
       	{
       		SearchBuf=Searchfinger();//����ָ�Ʊȶԣ������������������������ָ�����
       		if(SearchBuf==1)
       		{
       			return SearchNumber; 
       		}
       		else 
			{
			   return 255;//��ʾ��������ָ�Ʋ���ȷ
			}     
       	}
		i++;	
    }
   return 0;
}
//
u8 savefingure(unsigned char ID)//����ָ��
{
	 unsigned char i=0;
	 //���ڿ�ʼ���д洢ָ��ģ��Ĳ���
     for (i=0;i<16;i++)	//����ָ����Ϣ
	{
		dat[i]=STOR[i];
	}  
	dat[12]=ID; //��ָ��ģ���ŵ�PAGE_IDҲ����FLASH��λ��
	dat[14]=dat[14]+ID;	//У���
	if (Command(dat,16,12)==1)//���ɹ�����0	//�˴����д��ָ��ģ�����
		return(1);
	else
		return(0); //���ɹ�����0
}//
u8 enroll(void) //�ɼ�����ָ�ƣ�����1�� ָ��ģ��		/////////////////���޸�=========================
{
 	unsigned char temp=0,count=0;
  	while(1)
  	{
  	 	temp = ImgProcess(1); //��������1    
   		if (temp==1)//���������ļ��ɹ�             
      	{  		      
        	//�ɼ���һ�������ɹ� 
		   	count=0;  
		  	buzzer=1;	//��������
			delay_ms(100);	//��������
			buzzer=0;		//��������
			break;
       	}
     	else                   
       	{
        	if (temp==0)//�ɼ�ָ��û�гɹ�
          	{ 
				count++;
            	if (count>=40)//����ɼ���40�Σ������ɹ���ֱ�Ӳɼ�ʧ�ܣ�ֱ���˳�enroll����������������0  
					return(0);
            }
        }
   	}

	//�ɼ���һ�������ɹ� 
   	count=0;  
  	buzzer=1;	  
	delay_ms(100); 
	buzzer=0;	   //close_buzzer
	delay_ms(2000);//��ʱ2S��ʼ�ɼ���һ������

	//��ʼ�ɼ��ڶ������� 
 	while(1)
  	{
   		temp=ImgProcess(2); //��������2    
   		if (temp==1)//���������ļ�2�ɹ�
      	{
        	if (Command(MERG,12,12)) //�ϲ��ɹ�����1
			{
			     buzzer=1;		 //��������
	             delay_ms(100);
	             buzzer=0;
				 delay_ms(100);
				 buzzer=1;
	             delay_ms(100);	//����������ʾ����һ��ģ��ɹ�
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
        	if (temp==0)//�ɼ�ָ��û�гɹ�
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
void Figure_Test(void)//������
{
	u8 i;
	mode();//����ǰ��ʲôģʽ
	
	for(i=0;i<6;i++)//��ʼ����6�Σ����û��һ�γɹ�����ʾģ��ͨ�Ų�������ֻҪ�ɹ���������ѭ��
	{
		if(Command(VPWD, 16, 12))//��ģ������ͨ�����̵����𡣽���ʶ��ģʽ
		{
			LED1 = 0; //��һ��
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
//		if(modeflag==1)//¼��һ��ָ��
//		{
//			if(enroll()==1)//�ɼ����Σ�����1��ָ��ģ��ɹ�
//		  	{
//			   if(savefingure(SaveNumber+1))//����Ҳ�ɹ�
//			   	{
//					SaveNumber++;//��һ��
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
		if(modeflag==0)//Ϊʶ��ģʽ
		{
			searchnum=search();
			if(searchnum>=1&&searchnum<=162)//�����162��ָ��
			{
				shownum(searchnum);
				if (searchnum==1)
  			    {
					forward();	//  ����			
				}
				if (searchnum==2)
				{
					backward();   //����
				}
//					while(1)		 //�޸�ʹ��ʵ�ֹ���^_^
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
			   //��������һ��
			   buzzer=1;
			   delay_ms(100);
			   buzzer=0;
			   for(i=0;i<20;i++)
			   {
					delay_ms(50);
			   }
			}
			if(searchnum==255)//����ȷ��ָ�� ������������
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
//			Command(DELE_all, 12, 12); //�������ָ��
//		    LED0=0;	     //��ɫ����
//		    LED1=1;
//			//����������һ�Σ���ʾ�������ָ�ƽ���
//			modeflag=1;//����¼��ָ��ģʽ
//			shownum(0);
//			buzzer=1;
//			delay_ms(300);
//			buzzer=0;
//			SaveNumber=0;
//		}
//		if(changeflag==1)
//		{
//			mode();//��ʾ��ǰģʽ	
//			changeflag=0;
//		}
	}
}
//
