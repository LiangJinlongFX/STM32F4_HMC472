#include "Display.h"
#include "delay.h"
#include "lcd.h"
#include "keyboard.h"


DDS_TypeDef DDS_Structest;


/**
	*本函数为参数录入界面函数
	*具有录入参数超范围值错误提示  根据实际情况更改
	*当设置模式为单一频率输出时，只能设置开始频率  终止频率自动跟随开始频率
**/
void Display1(void)
{
	u8 key_num,flag=0;
	u16 temp1=0,temp2=0;
	u8 Display_State=0;
	char Display_State_Temp=0;
	
	//设置扫描默认参数
	u8 Mode_Num_Temp;
	u16 Start_Freq_Temp=10;
	u16 Stop_Freq_Temp=1500;
	u16 RF_Voltage_Temp=900;
	u16 Step_Freq_Temp=100;
	u16 Sweep_Time_Temp=1;
	
	/*参数选择界面*/
	LCD_ShowString(20,24,132,24,24, "      Mode:");
	LCD_ShowString(20,48,252,24,24, "Start Freq:    .  MHz");
	LCD_ShowString(20,72,252,24,24, "Stop  Freq:    .  MHz");	
	LCD_ShowString(20,96,240,24,24, "    RF Out:       mV");
	LCD_ShowString(20,120,252,24,24," Step Freq:       kHz");
	LCD_ShowString(20,144,228,24,24,"Sweep Time:       s");
	
	LCD_ShowString(90,168,132,24,24,"---State---");
	
	//更改画笔为红色
	POINT_COLOR=RED;
	
	//显示初始功能状态
	LCD_ShowString(78,192,192,24,24,"Mode     ");

	//显示初始参数
	LCD_ShowString(164,24,132,24,24, "Auto ");
	LCD_ShowxNum(164,48,Start_Freq_Temp/10,3,24,0);
	LCD_ShowxNum(212,48,Start_Freq_Temp%10,1,24,0);
	LCD_ShowxNum(164,72,Stop_Freq_Temp/10,3,24,0);
	LCD_ShowxNum(212,72,Stop_Freq_Temp%10,1,24,0);
	LCD_ShowxNum(176,96,RF_Voltage_Temp,4,24,0);
	LCD_ShowxNum(176,120,Step_Freq_Temp,4,24,0);
	LCD_ShowxNum(212,144,Sweep_Time_Temp,1,24,0);
	
	
	//参数录入循环
	do
	{				
		//等待按键动作
		key_num=Scan_key(1);
		
		//键值处理
		switch(key_num)
		{
			case 0:{temp1=temp1+0;if(Display_State==0) temp1=0;}break;
			case 1:{temp1=temp1+1;if(Display_State==0) temp1=1;}break;
			case 2:{temp1=temp1+2;if(Display_State==0) temp1=2;}break;
			case 3:temp1=temp1+3;break;
			case 4:temp1=temp1+4;break;
			case 5:temp1=temp1+5;break;
			case 6:temp1=temp1+6;break;
			case 7:temp1=temp1+7;break;
			case 8:temp1=temp1+8;break;
			case 9:temp1=temp1+9;break;
			case 'A':
			{	
				temp2=1;//切换功能后，录入数据缓存无效
				Display_State_Temp+=1;
				//当模式设置为单一频率时，自动跳跃终止频率设置
				if(Mode_Num_Temp==2&&Display_State_Temp==2) Display_State_Temp+=1;
				if(Display_State_Temp>5) Display_State_Temp=0;
			}break;
			case 'B':
			{
				temp2=1;//切换功能后，录入数据缓存无效
				Display_State_Temp-=1; 
				//当模式设置为单一频率时，自动跳跃终止频率设置
				if(Mode_Num_Temp==2&&Display_State_Temp==2) Display_State_Temp-=1;
				if(Display_State_Temp<0) Display_State_Temp=5;
			}break;
			case 'E':flag=1;break;
			case '.':temp1=0;break;
			default:break;
		 }
		 //切换功能 数据缓冲变量清零
		 if(Display_State_Temp!=Display_State)
		 {
			 temp1=0;
			 Display_State=Display_State_Temp;
		 }
		 //未按下确认键之前，参数还处于更改状态
		 if(!flag)
		 {
		 //根据功能状态改变显示数据
		 switch(Display_State)
		 {
			case 0:
			{
				if(!temp2) Mode_Num_Temp=temp1;
				switch(Mode_Num_Temp)
				{
					case 0: LCD_ShowString(164,24,132,24,24, "Auto    ");break;
					case 1: LCD_ShowString(164,24,132,24,24, "Manually");break;
					case 2: LCD_ShowString(164,24,132,24,24, "Single  ");break;
					default:break;
				}
				LCD_ShowString(78,192,192,24,24,"Mode            ");
			}break;
			case 1:
			{
				if(!temp2) Start_Freq_Temp=temp1;
				LCD_ShowString(78,192,192,24,24,"Start_Freq      ");
				LCD_ShowxNum(164,48,Start_Freq_Temp/10,3,24,0);
				LCD_ShowxNum(212,48,Start_Freq_Temp%10,1,24,0);
				if(Mode_Num_Temp==2) 
				{
					Stop_Freq_Temp=Start_Freq_Temp;
					LCD_ShowxNum(164,72,Stop_Freq_Temp/10,3,24,0);
					LCD_ShowxNum(212,72,Stop_Freq_Temp%10,1,24,0);
				}
			}break;
			case 2:
			{
				if(!temp2) Stop_Freq_Temp=temp1;
				LCD_ShowString(78,192,192,24,24,"Stop_Freq       ");
				LCD_ShowxNum(164,72,Stop_Freq_Temp/10,3,24,0);
				LCD_ShowxNum(212,72,Stop_Freq_Temp%10,1,24,0);
			}break;
			case 3:
			{
				if(!temp2) RF_Voltage_Temp=temp1;
				LCD_ShowString(78,192,192,24,24,"RF_Voltage      ");
				LCD_ShowxNum(176,96,RF_Voltage_Temp,4,24,0);
			}break;
			case 4:
			{
				if(!temp2) Step_Freq_Temp=temp1;
				LCD_ShowString(78,192,192,24,24,"Step_Freq       ");
				LCD_ShowxNum(176,120,Step_Freq_Temp,4,24,0);
			}break;
			case 5:
			{
				if(!temp2) Sweep_Time_Temp=temp1;
				LCD_ShowString(78,192,192,24,24,"Sweep_Time      ");
				LCD_ShowxNum(200,144,Sweep_Time_Temp,2,24,0);
			}break;
			default:break;
		}
		
		//放置录入的数据大于变量最大值
		if(temp1>10000) temp1=9999;
		//数据缓存标志位清除
		temp2=0;
		//变量进位
		temp1*=10;
		
		}
		
		//按下确认键，判断录入的参数是否正确
		if(flag)
		{
			//出现错误，做出提示
			if(Start_Freq_Temp<10||Start_Freq_Temp>Stop_Freq_Temp)
			{
				flag=0;//数据录入标志位清除
				temp1=0;//数据缓存清零
				LCD_ShowString(78,192,192,24,24,"Start_Freq ERROR");//提示错误
			}
			else if(Stop_Freq_Temp<Start_Freq_Temp||Stop_Freq_Temp>1600)
			{
				flag=0;
				temp1=0;
				LCD_ShowString(78,192,192,24,24,"Stop_Freq ERROR ");
			}
			else if(RF_Voltage_Temp<10||RF_Voltage_Temp>1000)
			{
				flag=0;
				temp1=0;
				LCD_ShowString(78,192,192,24,24,"RF_Voltage ERROR");
			}
			else if(Step_Freq_Temp<100||Step_Freq_Temp>1000)
			{
				flag=0;
				temp1=0;
				LCD_ShowString(78,192,192,24,24,"Step_Freq ERROR ");
			}				
			else if(Sweep_Time_Temp<1||Sweep_Time_Temp>5)
			{
				flag=0;
				temp1=0;
				LCD_ShowString(78,192,192,24,24,"Sweep_Time ERROR");
			}					
		}
	}while(!flag);
	
	//显示设置成功
	LCD_ShowString(78,192,192,24,24,"Set Successfully");
	//延时
	delay_ms(500);
	//真正开始赋值
	DDS_Structest.Mode_Num=Mode_Num_Temp;
	DDS_Structest.Start_Freq=Start_Freq_Temp;
	DDS_Structest.Stop_Freq=Stop_Freq_Temp;
	DDS_Structest.RF_Voltage=RF_Voltage_Temp;
	DDS_Structest.Step_Freq=Step_Freq_Temp;
	DDS_Structest.Sweep_Time=Sweep_Time_Temp;
	
	LCD_ShowString(78,192,192,24,24,"Start Sweep!    ");
	delay_ms(500);
	LCD_Clear(WHITE);
}

void Display2(void)
{
	//切换回黑色字
	POINT_COLOR=BLACK;
	
	LCD_ShowString(10,12,120,12,12,"Start Freq:    . MHz");
	LCD_ShowString(10,24,120,12,12," Stop Freq:    . MHz");
	LCD_ShowString(10,36,120,12,12," Step Freq:      kHz");
	LCD_ShowString(10,48,120,12,12,"Sweep Time:      s");

	LCD_ShowString(180,36,120,12,12,"   Mode:");	
	LCD_ShowString(180,12,120,12,12,"Maximum:    . MHz");
	LCD_ShowString(180,24,120,12,12,"Minimum:    . MHz");
	LCD_ShowString(180,36,120,12,12,"Display:");
	
	//切换回红色画笔
	POINT_COLOR=RED;
	
	//显示开始频率
	LCD_ShowxNum(82,12,DDS_Structest.Start_Freq/10,3,12,0);	
	LCD_ShowxNum(102,12,DDS_Structest.Start_Freq%10,1,12,0);
	
	//显示终止频率
	LCD_ShowxNum(82,24,DDS_Structest.Stop_Freq/10,3,12,0);	
	LCD_ShowxNum(102,24,DDS_Structest.Stop_Freq%10,1,12,0);
	
	//显示步进频率
	LCD_ShowxNum(88,36,DDS_Structest.Step_Freq,3,12,0);	
	
	//显示扫描时间
	LCD_ShowxNum(88,48,DDS_Structest.Sweep_Time,3,12,0);	
}

void Display_Spectrum()
{
	float temp;
	u16 Maximum,Minimum;
	u16 Point_Num;
	u16 

	//计算出总采样点数
	Point_Num=(DDS_Structest.Stop_Freq-DDS_Structest.Start_Freq)/(DDS_Structest.Step_Freq/100);
	
	arm_min_f32();
	arm_max_f32();
}
