#include "Display.h"
#include "delay.h"
#include "lcd.h"
#include "keyboard.h"


DDS_TypeDef DDS_Structest;


/**
	*������Ϊ����¼����溯��
	*����¼���������Χֵ������ʾ  ����ʵ���������
	*������ģʽΪ��һƵ�����ʱ��ֻ�����ÿ�ʼƵ��  ��ֹƵ���Զ����濪ʼƵ��
**/
void Display1(void)
{
	u8 key_num,flag=0;
	u16 temp1=0,temp2=0;
	u8 Display_State=0;
	char Display_State_Temp=0;
	
	//����ɨ��Ĭ�ϲ���
	u8 Mode_Num_Temp;
	u16 Start_Freq_Temp=10;
	u16 Stop_Freq_Temp=1500;
	u16 RF_Voltage_Temp=900;
	u16 Step_Freq_Temp=100;
	u16 Sweep_Time_Temp=1;
	
	/*����ѡ�����*/
	LCD_ShowString(20,24,132,24,24, "      Mode:");
	LCD_ShowString(20,48,252,24,24, "Start Freq:    .  MHz");
	LCD_ShowString(20,72,252,24,24, "Stop  Freq:    .  MHz");	
	LCD_ShowString(20,96,240,24,24, "    RF Out:       mV");
	LCD_ShowString(20,120,252,24,24," Step Freq:       kHz");
	LCD_ShowString(20,144,228,24,24,"Sweep Time:       s");
	
	LCD_ShowString(90,168,132,24,24,"---State---");
	
	//���Ļ���Ϊ��ɫ
	POINT_COLOR=RED;
	
	//��ʾ��ʼ����״̬
	LCD_ShowString(78,192,192,24,24,"Mode     ");

	//��ʾ��ʼ����
	LCD_ShowString(164,24,132,24,24, "Auto ");
	LCD_ShowxNum(164,48,Start_Freq_Temp/10,3,24,0);
	LCD_ShowxNum(212,48,Start_Freq_Temp%10,1,24,0);
	LCD_ShowxNum(164,72,Stop_Freq_Temp/10,3,24,0);
	LCD_ShowxNum(212,72,Stop_Freq_Temp%10,1,24,0);
	LCD_ShowxNum(176,96,RF_Voltage_Temp,4,24,0);
	LCD_ShowxNum(176,120,Step_Freq_Temp,4,24,0);
	LCD_ShowxNum(212,144,Sweep_Time_Temp,1,24,0);
	
	
	//����¼��ѭ��
	do
	{				
		//�ȴ���������
		key_num=Scan_key(1);
		
		//��ֵ����
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
				temp2=1;//�л����ܺ�¼�����ݻ�����Ч
				Display_State_Temp+=1;
				//��ģʽ����Ϊ��һƵ��ʱ���Զ���Ծ��ֹƵ������
				if(Mode_Num_Temp==2&&Display_State_Temp==2) Display_State_Temp+=1;
				if(Display_State_Temp>5) Display_State_Temp=0;
			}break;
			case 'B':
			{
				temp2=1;//�л����ܺ�¼�����ݻ�����Ч
				Display_State_Temp-=1; 
				//��ģʽ����Ϊ��һƵ��ʱ���Զ���Ծ��ֹƵ������
				if(Mode_Num_Temp==2&&Display_State_Temp==2) Display_State_Temp-=1;
				if(Display_State_Temp<0) Display_State_Temp=5;
			}break;
			case 'E':flag=1;break;
			case '.':temp1=0;break;
			default:break;
		 }
		 //�л����� ���ݻ����������
		 if(Display_State_Temp!=Display_State)
		 {
			 temp1=0;
			 Display_State=Display_State_Temp;
		 }
		 //δ����ȷ�ϼ�֮ǰ�����������ڸ���״̬
		 if(!flag)
		 {
		 //���ݹ���״̬�ı���ʾ����
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
		
		//����¼������ݴ��ڱ������ֵ
		if(temp1>10000) temp1=9999;
		//���ݻ����־λ���
		temp2=0;
		//������λ
		temp1*=10;
		
		}
		
		//����ȷ�ϼ����ж�¼��Ĳ����Ƿ���ȷ
		if(flag)
		{
			//���ִ���������ʾ
			if(Start_Freq_Temp<10||Start_Freq_Temp>Stop_Freq_Temp)
			{
				flag=0;//����¼���־λ���
				temp1=0;//���ݻ�������
				LCD_ShowString(78,192,192,24,24,"Start_Freq ERROR");//��ʾ����
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
	
	//��ʾ���óɹ�
	LCD_ShowString(78,192,192,24,24,"Set Successfully");
	//��ʱ
	delay_ms(500);
	//������ʼ��ֵ
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
	//�л��غ�ɫ��
	POINT_COLOR=BLACK;
	
	LCD_ShowString(10,12,120,12,12,"Start Freq:    . MHz");
	LCD_ShowString(10,24,120,12,12," Stop Freq:    . MHz");
	LCD_ShowString(10,36,120,12,12," Step Freq:      kHz");
	LCD_ShowString(10,48,120,12,12,"Sweep Time:      s");

	LCD_ShowString(180,36,120,12,12,"   Mode:");	
	LCD_ShowString(180,12,120,12,12,"Maximum:    . MHz");
	LCD_ShowString(180,24,120,12,12,"Minimum:    . MHz");
	LCD_ShowString(180,36,120,12,12,"Display:");
	
	//�л��غ�ɫ����
	POINT_COLOR=RED;
	
	//��ʾ��ʼƵ��
	LCD_ShowxNum(82,12,DDS_Structest.Start_Freq/10,3,12,0);	
	LCD_ShowxNum(102,12,DDS_Structest.Start_Freq%10,1,12,0);
	
	//��ʾ��ֹƵ��
	LCD_ShowxNum(82,24,DDS_Structest.Stop_Freq/10,3,12,0);	
	LCD_ShowxNum(102,24,DDS_Structest.Stop_Freq%10,1,12,0);
	
	//��ʾ����Ƶ��
	LCD_ShowxNum(88,36,DDS_Structest.Step_Freq,3,12,0);	
	
	//��ʾɨ��ʱ��
	LCD_ShowxNum(88,48,DDS_Structest.Sweep_Time,3,12,0);	
}

void Display_Spectrum()
{
	float temp;
	u16 Maximum,Minimum;
	u16 Point_Num;
	u16 

	//������ܲ�������
	Point_Num=(DDS_Structest.Stop_Freq-DDS_Structest.Start_Freq)/(DDS_Structest.Step_Freq/100);
	
	arm_min_f32();
	arm_max_f32();
}
