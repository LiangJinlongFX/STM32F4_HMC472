#include "hmc472.h"
#include "usart.h"

/*********************************************************************************
**********************************************************************************
* �ļ�����: hmc472a.c                                                                
* �ļ�������HMC472�ɿ�˥������ƽ���Ƴ���                                                            
* �������ڣ�2017.8.06                                                           
* ��    ����V1.0                                                                 
* ��    �ߣ�liang                                                               
* ˵    ���������ú�IO��ӳ��
						!!!ʹ������֮ǰһ��Ҫע���ʼ��IO��
						������֧��һ��HMC472Ҳ֧������HMC472��������
						
**********************************************************************************
*********************************************************************************/
void HMC472_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);	//ʹ��GPIODʱ��

  //��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5 |GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;			//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;			//����
  GPIO_Init(GPIOD, &GPIO_InitStructure);						//��ʼ��
	
	//��ʼ��Ϊ�ߣ���˥��
	GPIO_SetBits(GPIOD,GPIO_Pin_0 | GPIO_Pin_1| GPIO_Pin_2| GPIO_Pin_3| GPIO_Pin_4| GPIO_Pin_5 |GPIO_Pin_8 | GPIO_Pin_9| GPIO_Pin_10| GPIO_Pin_11| GPIO_Pin_12| GPIO_Pin_13);

}

/**
	*HMC472���ƺ���
	*������˥����{����ģʽ��0-31.5  ˫��ģʽ��0-63 }   ˥����������0�� 1    1��2   
	*����ֵ��0�����Ƴɹ�  1��˥������������   2���ڵ���ģʽ��˥������������
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

