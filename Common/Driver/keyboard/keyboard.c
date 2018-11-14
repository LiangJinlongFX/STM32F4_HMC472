#include "keyboard.h"
#include "delay.h"	
#include "usart.h"

/*********************************************************************************
**********************************************************************************
* �ļ�����: KEYBOARD.c                                                                
* �ļ�������4*4���������������                                                            
* �������ڣ�2017.8.06                                                           
* ��    ����V1.0                                                                 
* ��    �ߣ�liang                                                               
* ˵    ����ֻ�����ú�IO��ӳ��
						֧��STM32����˿�ӳ��
						֧�ֵ��ΰ��»�����ģʽ* 
**********************************************************************************
*********************************************************************************/


/**
	*����IO�ڳ�ʼ������
	*ʹ�ü���ǰһ��Ҫ�ǵõ��ô˺�����ʼ���˿�
**/
void Key_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//ʹ��ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//����
  GPIO_Init(GPIOA, &GPIO_InitStructure);						//��ʼ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);						//��ʼ��
	
	keyBoard_Out1=1;
	keyBoard_Out2=1;
	keyBoard_Out3=1;
	keyBoard_Out4=1;
	
	keyBoard_InO1=0;
	keyBoard_InO2=0;
	keyBoard_InO3=0;
	keyBoard_InO4=0;

}

/**
	*����ɨ�躯��
	*����ֵ�� 0���ް�������   ע�ⷵ��ֵ����ASCII��ֵ
**/
u8 Read_KeyValue(void) 
{
	u8 KeyValue=0;

	keyBoard_Out1=1;
	keyBoard_Out2=0;
	keyBoard_Out3=0;
	keyBoard_Out4=0;
	if(keyBoard_In1) KeyValue='1';
	else if(keyBoard_In2) KeyValue='2'; 
	else if(keyBoard_In3) KeyValue='3';
	else if(keyBoard_In4) KeyValue='A';    
	
	keyBoard_Out1=0;
	keyBoard_Out2=1;
	keyBoard_Out3=0;
	keyBoard_Out4=0;
	if(keyBoard_In1) KeyValue='4';
	else if(keyBoard_In2) KeyValue='5'; 
	else if(keyBoard_In3) KeyValue='6';
	else if(keyBoard_In4) KeyValue='B';  
	
	keyBoard_Out1=0;
	keyBoard_Out2=0;
	keyBoard_Out3=1;
	keyBoard_Out4=0;
	if(keyBoard_In1) KeyValue='7';
	else if(keyBoard_In2) KeyValue='8'; 
	else if(keyBoard_In3) KeyValue='9';
	else if(keyBoard_In4) KeyValue='C';  
	
	keyBoard_Out1=0;
	keyBoard_Out2=0;
	keyBoard_Out3=0;
	keyBoard_Out4=1;
	if(keyBoard_In1) KeyValue='.';
	else if(keyBoard_In2) KeyValue='0'; 
	else if(keyBoard_In3) KeyValue='E';
	else if(keyBoard_In4) KeyValue='D';  

	keyBoard_Out1=1;
	keyBoard_Out2=1;
	keyBoard_Out3=1;
	keyBoard_Out4=1;
	
	keyBoard_InO1=0;
	keyBoard_InO2=0;
	keyBoard_InO3=0;
	keyBoard_InO4=0;
	
	return KeyValue;
}


/**
	*���̼�ֵ������
	*֧��������0��  �򵥴δ���ģʽ  1
**/
u8 Scan_key(u8 Mode)
{
	u8 Key_Num;
	do{
		do{
			Key_Num=Read_KeyValue();
		}while(!Key_Num);
		delay_ms(20);
	}while(Read_KeyValue()!=Key_Num);
	if(Mode)
	{
		while(Read_KeyValue());
	}
	return Key_Num;
}


