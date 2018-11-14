#include "keyboard.h"
#include "delay.h"	
#include "usart.h"

/*********************************************************************************
**********************************************************************************
* 文件名称: KEYBOARD.c                                                                
* 文件简述：4*4矩阵键盘驱动程序                                                            
* 创建日期：2017.8.06                                                           
* 版    本：V1.0                                                                 
* 作    者：liang                                                               
* 说    明：只需配置好IO口映射
						支持STM32任意端口映射
						支持单次按下或连按模式* 
**********************************************************************************
*********************************************************************************/


/**
	*键盘IO口初始化函数
	*使用键盘前一定要记得调用此函数初始化端口
**/
void Key_Init()
{
	GPIO_InitTypeDef  GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOC, ENABLE);//使能时钟
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;			//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;			//上拉
  GPIO_Init(GPIOA, &GPIO_InitStructure);						//初始化
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4| GPIO_Pin_5;
	GPIO_Init(GPIOC, &GPIO_InitStructure);						//初始化
	
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
	*键盘扫描函数
	*返回值： 0：无按键按下   注意返回值都是ASCII码值
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
	*键盘键值处理函数
	*支持连按（0）  或单次触发模式  1
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


