/**
  ******************************************************************************
  * @file    STM32F407/IO.c 
  * @author  Liang
  * @version V1.0.0
  * @date    2017-7-23
  * @brief   ����IO�������ƻ������߿���
  ******************************************************************************
  * @attention
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "IO.h"

/* ����ʵ�������ʼ��Ӧ��IO���� */
void IO_Init(void)
{    	 
  GPIO_InitTypeDef  GPIO_InitStructure;

  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF, ENABLE);//ʹ��GPIOFʱ��

  //GPIOF9,F10��ʼ������
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;					//��ͨ���ģʽ
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;				//�������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;		//100MHz
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;					//����
  GPIO_Init(GPIOF, &GPIO_InitStructure);								//��ʼ��
	
	GPIO_SetBits(GPIOF,GPIO_Pin_9 | GPIO_Pin_10);//GPIOF9,F10���øߣ�����

}


/**
	* ��    ��: void GPIO_group_OUT(_gpio_group *group,u16 outdata)
	* ��    �ܣ�ʹ������16��IO�����һ��16λ���������
	* ��ڲ�����*group�� ����16��IO��ΪԪ�صĽṹ��ָ��
							outdata: 16λ�����ֵ
	* ���ز�������
	* ˵    ����outdata�Ӹ�λ��ʼ��ֵ
	**/
void GPIO_group_OUT(_gpio_group *group,u16 outdata)
{
  u8 t;
	for(t=0;t<16;t++)
    {               
        if((outdata&0x8000)>>15)  
				{
						switch(t)
						{
								case 0:	   group->data15=1; break;
								case 1:	   group->data14=1; break;
								case 2:	   group->data13=1; break;
								case 3:	   group->data12=1; break;
								case 4:	   group->data11=1; break;
								case 5:	   group->data10=1; break;
								case 6:	   group->data9=1;  break;
								case 7:	   group->data8=1;  break;
								case 8:	   group->data7=1;  break;
								case 9:	   group->data6=1;  break;
								case 10:	 group->data5=1;  break;
								case 11:	 group->data4=1;  break;
								case 12:	 group->data3=1;  break;
								case 13:	 group->data2=1;  break;
								case 14:	 group->data1=1;  break;
								case 15:	 group->data0=1;  break;
						}
				}
				else
				{
				  switch(t)
						{
								case 0:	   group->data15=0; break;
								case 1:	   group->data14=0; break;
								case 2:	   group->data13=0; break;
								case 3:	   group->data12=0; break;
								case 4:	   group->data11=0; break;
								case 5:	   group->data10=0; break;
								case 6:	   group->data9=0;  break;
								case 7:	   group->data8=0;  break;
								case 8:	   group->data7=0;  break;
								case 9:	   group->data6=0;  break;
								case 10:	 group->data5=0;  break;
								case 11:	 group->data4=0;  break;
								case 12:	 group->data3=0;  break;
								case 13:	 group->data2=0;  break;
								case 14:	 group->data1=0;  break;
								case 15:	 group->data0=0;  break;
						}
				}
     outdata<<=1; 	
	  }
}
/**
	* ��    ��: void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
	* ��    �ܣ�λ�β���ʵ�֣�ͬһIO�ڵļ�λ�����������
	* ��ڲ�����* GPIOx��  ��Ӧ��IO��
	*           start_bit: �����������ʼλ
	*           bit_size:  Ҫ���������λ��
	* ���ز�������
	* ˵    ����start_bit: 0~14
							bit_size:  1~16 
							bit_size<=16-start_bit
	**/
void GPIO_bits_OUT(GPIO_TypeDef* GPIOx, u8 start_bit, u8 bit_size,u16 outdata)
{
  u8 i=0;
	u16 bu1=0;u16 middata=1;

	if( bit_size>(16-start_bit) ) 
     bit_size=16-start_bit;
	
	i=start_bit;
	if(i>0)
		 {
			 while(i--)
         { bu1+=middata; middata*=2;}
		 }
	
   assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
   
	 GPIOx->ODR&=(  ( (0xffff<<bit_size) <<start_bit ) |bu1   ); 
	 GPIOx->ODR|=(outdata<<start_bit);		 
}

