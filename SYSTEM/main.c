#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "keyboard.h" 
#include "hmc472.h"
#include "adc.h"


int main(void)
{
	
	u16 adcx;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init(168);      //��ʼ����ʱ����
	uart_init(115200);		//��ʼ�����ڲ�����Ϊ115200
	Adc_Init();
	HMC472_Init();

	while(1)
	{
		adcx=Get_Adc_Average(ADC_Channel_5,20);
		HMC472_Con(adcx/33,1);
		printf("%d\n",adcx/33);
	}
}

