#include "hmc472.h"
#include "usart.h"

/*********************************************************************************
**********************************************************************************
* 文件名称: hmc472a.c                                                                
* 文件简述：HMC472可控衰减器电平控制程序                                                            
* 创建日期：2017.8.06                                                           
* 版    本：V1.0                                                                 
* 作    者：liang                                                               
* 说    明：需配置好IO口映射
						!!!使用引脚之前一定要注意初始化IO口
						本程序支持一块HMC472也支持两块HMC472连续控制
						
**********************************************************************************
*********************************************************************************/
void HMC472_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//使能GPIOD时钟

  //初始化设置
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5 |GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//普通输出模式
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//推挽输出
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//上拉
  GPIO_Init(GPIOD, &GPIO_InitStructure);						//初始化
	
	//初始化为高，无衰减
	GPIO_SetBits(GPIOD,GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5 |GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13);

}

/**
	*HMC472控制函数
	*参数：衰减量{单机模式：0-31.5  双机模式：0-63 }   衰减器数量：0： 1    1：2   
	*返回值：0：控制成功  1：衰减量超出极限   2：在单机模式下衰减量超出极限
**/
u8 HMC472_Con(u16 Con_Num , u8 Attenuator_Num)
{
	u8 Con_Voltage;
	u8 Con_Voltage_A,Con_Voltage_B;
//	Con_Num=Con_Num*2;
	Con_Voltage=(u8)Con_Num;
	if(Con_Num>126)   return 1;
	Con_Voltage_A=Con_Voltage;
	
	if(Con_Num>63)
	{
		if(Attenuator_Num!=1) return 2;
		Con_Voltage_A=63;
		Con_Voltage_B=Con_Num-63;
	}
	Con_Voltage_A=~Con_Voltage_A;
	Con_Voltage_B=~Con_Voltage_B;
	if(Con_Voltage_A&0x01)
	HMC472A_V6=1;
	else HMC472A_V6=0;
	Con_Voltage_A>>=1;

	if(Con_Voltage_A&0x01)
	HMC472A_V5=1;
	else HMC472A_V5=0;
	Con_Voltage_A>>=1;

	if(Con_Voltage_A&0x01)
	HMC472A_V4=1;
	else HMC472A_V4=0;
	Con_Voltage_A>>=1;

	if(Con_Voltage_A&0x01)
	HMC472A_V3=1;
	else HMC472A_V3=0;
	Con_Voltage_A>>=1;

	if(Con_Voltage_A&0x01)
	HMC472A_V2=1;
	else HMC472A_V2=0;
	Con_Voltage_A>>=1;

	if(Con_Voltage_A&0x01)
	HMC472A_V1=1;
	else HMC472A_V1=0;

	if(Attenuator_Num)
	{
		if(Con_Voltage_B&0x01)
		HMC472B_V6=1;
		else HMC472B_V6=0;
		Con_Voltage_B>>=1;
		if(Con_Voltage_B&0x01)
		HMC472B_V5=1;
		else HMC472B_V5=0;
		Con_Voltage_B>>=1;
		if(Con_Voltage_B&0x01)
		HMC472B_V4=1;
		else HMC472B_V4=0;
		Con_Voltage_B>>=1;
		if(Con_Voltage_B&0x01)
		HMC472B_V3=1;
		else HMC472B_V3=0;
		Con_Voltage_B>>=1;
		if(Con_Voltage_B&0x01)
		HMC472B_V2=1;
		else HMC472B_V2=0;
		Con_Voltage_B>>=1;
		if(Con_Voltage_B&0x01)
		HMC472B_V1=1;
		else HMC472B_V1=0;	
	}
	return 0;
}

