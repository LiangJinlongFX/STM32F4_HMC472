#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "led.h"
#include "lcd.h"
#include "keyboard.h" 
#include "hmc472.h"
#include "dac.h"



int main(void)
{
	u8 num,Dis_num,State=0;
	int DAC_Num=0;
	double Attenuation_Num=0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init(168);      //初始化延时函数
	uart_init(115200);		//初始化串口波特率为115200
	Dac1_Init();
	
	Key_Init();
	HMC472_Init();
	LCD_Init();
	POINT_COLOR=BLACK;
	LCD_Clear(WHITE);

	LCD_ShowString(10,40,204,24,24,"Attenuation State");		
	LCD_ShowString(50,64,84,24,24,"-    dB");	
	
	LCD_ShowString(40,112,144,24,24,"VCA821 State");		
	LCD_ShowString(120,136,12,24,24,"V");	
	
	
	LCD_ShowString(50,184,132,24,24,"---State---");
	LCD_ShowString(70,208,84,24,24,"HMC472A");
	
	LCD_ShowxNum(62,64,Attenuation_Num*10,3,24,0);
	LCD_ShowxNum(70,136,DAC_Num,4,24,0);
	while(1)
	{
		num=Scan_key(1);
		if(num=='E')
		{
			State=~State;
			if(State==0) LCD_ShowString(70,208,84,24,24,"HMC472A");
			else LCD_ShowString(70,208,72,24,24,"VCA821");
		}
		else if(num=='A')
		{
			if(State==0)
			{
				Attenuation_Num+=0.5;
				if(Attenuation_Num>31.5) Attenuation_Num=31.5;
				HMC472_Con(Attenuation_Num,0);
				LCD_ShowxNum(62,64,Attenuation_Num*10,3,24,0);
			}
			else
			{
				DAC_Num+=100;
				if(DAC_Num>2000) DAC_Num=2000;
				Dac1_Set_Vol(DAC_Num);
				LCD_ShowxNum(70,136,DAC_Num,4,24,0);
			}
		}
		else if(num=='B')
		{
			if(State==0)
			{
				Attenuation_Num-=0.5;
				if(Attenuation_Num<0) Attenuation_Num=0;
				HMC472_Con(Attenuation_Num,0);
				LCD_ShowxNum(62,64,Attenuation_Num*10,3,24,0);
			}
			else
			{
				DAC_Num-=100;
				if(DAC_Num<0) DAC_Num=0;
				Dac1_Set_Vol(DAC_Num);
				LCD_ShowxNum(70,136,DAC_Num,4,24,0);
			}
		}

	}
}
