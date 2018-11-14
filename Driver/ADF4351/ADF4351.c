/**
  ******************************************************************************
  * @file    ADF4351.c 
  * @author  Liang
  * @version V1.0.0
  * @date    2017-7-29
  * @brief   PLLоƬ ADF4351��������
  ******************************************************************************
  * @attention
	* ������ͨIO��ģ�⴮��ʱ��ʽ
	*	����ʵ�����������ص�io��
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "ADF4351.h"
#include "delay.h"

#define SET_LE()		GPIO_SetBits(GPIOB, GPIO_Pin_4)		//LE
#define CLR_LE()		GPIO_ResetBits(GPIOB, GPIO_Pin_4)

#define	SET_SCL()		GPIO_SetBits(GPIOB, GPIO_Pin_6)		//CLK
#define	CLR_SCL()		GPIO_ResetBits(GPIOB, GPIO_Pin_6)

#define SET_DATA()		GPIO_SetBits(GPIOB, GPIO_Pin_5)	//DAT
#define CLR_DATA()		GPIO_ResetBits(GPIOB, GPIO_Pin_5)

#define SET_CE()		GPIO_SetBits(GPIOB, GPIO_Pin_3)		//CE
#define CLR_CE()		GPIO_ResetBits(GPIOB, GPIO_Pin_3)
	
u8 buf[4];


//д��32���ֽ�
void ADF4351_Write(u32 adf_dat)
{
	u8 i;

	CLR_LE();//����LE,׼��д������
	/* ��λд��32λ���ݣ� MSBģʽ */
	for (i = 0; i < 32; i++)
	{
		if ((adf_dat & 0x80000000) == 0x80000000)
			SET_DATA();
		else
			CLR_DATA();
		/* ģ��ʱ������ */
		CLR_SCL();
		SET_SCL();
		CLR_SCL();
		/* �Ƶ���һλ׼������ */
		adf_dat <<= 1;
	}
	/* LE���� ���ݷ������ */
	SET_LE();
	delay_us(1);
	CLR_LE();
}

void ADF4351_Init(void)
{
		GPIO_InitTypeDef  GPIO_InitStructure;
		
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE); ;
		
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 |GPIO_Pin_7;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;//��ͨ���ģʽ
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;//�������
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;//100MHz
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;//����
		GPIO_Init(GPIOB, &GPIO_InitStructure);//��ʼ��
		
		GPIO_ResetBits(GPIOB, GPIO_Pin_7);
	  SET_CE();
	

}


//---------------------------------
//void WriteToADF4350(unsigned char count,unsigned char *buf);
//---------------------------------
//Function that writes to the ADF4350 via the SPI port. 
//--------------------------------------------------------------------------------

/* �Զ���8λ����д�� �Ӹ�λ����λ */
void WriteToADF4350(unsigned char count, unsigned char *buf)
{
	unsigned	char	ValueToWrite = 0;
  unsigned	char	i = 0;
	unsigned	char	j = 0;
	
	delay_ms(1);
	CLR_SCL();
	CLR_LE();
	delay_ms(1);

	for(i=count;i>0;i--)
 	{
	 	ValueToWrite = *(buf + i - 1);
		for(j=0; j<8; j++)
		{
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_DATA();	  //Send one to SDO pin
			}
			else
			{
				CLR_DATA();	  //Send zero to SDO pin
			}
			delay_us(1);
			SET_SCL();
			delay_us(1);
			ValueToWrite <<= 1;	//Rotate data
			CLR_SCL();
		}
	}
	CLR_DATA();
	delay_us(1);
	SET_LE();
	delay_us(1);
	CLR_LE();
}


void SetFreq_Res(void)
{
	u32 R0=0xa00000;
	u32 R1=0x8008011;
	u32 R2=0x70004fc2;
	u32 R3=0x20044b3;
	u32 R4=0xe50034;
	u32 R5=0x180005;
	ADF4351_Write(R5);
	ADF4351_Write(R4);
	ADF4351_Write(R3);
	ADF4351_Write(R2);
	ADF4351_Write(R1);
	ADF4351_Write(R0);
}

void Frequency_35MHz(void)
{

	buf[3] = 0x00;
	buf[2] = 0x58;
	buf[1] = 0x00;				//write communication register 0x00580005 to control the progress 
 	buf[0] = 0x05;				//to write Register 5 to set digital lock detector
	WriteToADF4350(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0xD0;	//EC			//(DB23=1)The signal is taken from the VCO directly;(DB22-20:6H)the RF divider is 64;(DB19-12:50H)R is 80
	buf[1] = 0xa0;				//(DB11=0)VCO powerd up;
 	buf[0] = 0x3C;				//(DB5=1)RF output is enabled;(DB4-3=3H)Output power level is 5
	WriteToADF4350(4,buf);		

	buf[3] = 0x00;
	buf[2] = 0x84;
	buf[1] = 0x80;				//(DB14-3:96H)clock divider value is 150.
 	buf[0] = 0x13;
	WriteToADF4350(4,buf);	

	buf[3] = 0x61;
	buf[2] = 0x00;				//(DB6=1)set PD polarity is positive;(DB7=1)LDP is 6nS;
	buf[1] = 0x40;				//(DB8=0)enable fractional-N digital lock detect;
 	buf[0] = 0x42;				//(DB12-9:7H)set Icp 2.50 mA;
	WriteToADF4350(4,buf);		//(DB23-14:1H)R counter is 1

	buf[3] = 0x00;
	buf[2] = 0x00;
	buf[1] = 0x03;			   //(DB14-3:6H)MOD counter is 6;
 	buf[0] = 0x21;			   //(DB26-15:6H)PHASE word is 1,neither the phase resync 
	WriteToADF4350(4,buf);	   //nor the spurious optimization functions are being used
							   //(DB27=1)prescaler value is 8/9

	buf[3] = 0x01;
	buf[2] = 0x39;
	buf[1] = 0x80;
 	buf[0] = 0xa0;				//(DB14-3:0H)FRAC value is 0;
	WriteToADF4350(4,buf);		//(DB30-15:140H)INT value is 320;

}




	/*-------------------------------------200MHz---------------------------------------------
	Reference frequency: 20MHz;Output frequency: 200MHz;VCO frequency: 3200MHz;Prescaler: 8/9;
	RF divider: 16;VCO channel spacing frequency: 200KHz;PFD frequency: 10MHz;
	INT: 320;FRAC: 0;MOD: 100;R: 1;Lock Clk Div: 6; bank clk div: 200; Phase: 1  
	----------------------------------------------------------------------------------------*/
	/*RFout = [INT + (FRAC/MOD)] * (Fpfd/RF Divider)*/
	/*Fpfd = REFIN * [(1 + D)/(R * (1 + T))]*/
	/*Fvco = RF divider * Output frequency   2.2G-4.4G*/

void ADF_SetFre(void)
{

	u32 adf_data;
 
	/**********************R5****************************************/
	u8 LD_Pin_Mode=3;  			//���������ⷽʽ  0: low 1: digital lock detect 2:low 3:high
	/**********************R4****************************************/
	u8 Feedback_Select=1;   //����ѡ��  0:�źŴӷ�Ƶ�����  1:�ź�ֱ�Ӵ�VCO���
	u8 VCO_PowerDown=0;     //VCO�ضϣ� 0: VCO�ϵ�  1: VCO�ض�
	u8 MTLD=0;							//��������⵽����  1:��Ч
	u8 AUX_Output=1;        //�������ѡ�� 0:�������ΪRF��Ƶ�����  1:ֱ��Ϊ��Ƶ���
	u8 AUX_EN=1;						//�������ʹ��  0:����  1:ʹ��
	u8 AUX_Power=1;         //�����������ѡ��
	u8 RF_Output_EN=1;			//�����ʹ��  0;����  1;ʹ��
	u8 RF_Output_Power=2;		//���������
	/**********************R3****************************************/
	u8 Band_Clock_Mode=1;		//Ƶ��ʱ��ѡ��ģʽ  0:LOW 1:HIGH
	u8 APB=1;								//������������  0:6ns 1:3ns
	u8 Charge_Cancel=1;			//������� 0��Disable 1:Enable
	u8 CSR=1;								//CSR  0:Disable 1:Enable
	u8 Clk_Div_Mode=1;			//ʱ�ӷ�Ƶ��ģʽ   0:CLOCK CIVDER OFF  1:FAST LOCK ENABLE 2:RESYNC ENABLE; 3:RESERVED
	u16 adf_Locktime=160;	//ʱ�ӷ�Ƶֵ
	/**********************R2****************************************/
	u8 Low_Noise_Spur_Mode=3;//�������͵���ɢģʽ  0: LOW NOISE MODE  1: RESERVED 2: RESERVED 3: LOW SPUR MODE
	u8 Muxout=1;						//��·�������   0: THREE_STATE OUTPUT 1:DVDD 2:DGND 3:R COUNT OUTPUT 4: N DIV 5:ANALOG LOCK DETECT 6: DIGTAL LOCK DETRCT 7:RESERVED
	u16 adf_R=1;					//RF�ο���Ƶϵ��
  u8 adf_D=0;						//RF REFin��Ƶ��λ(0 or 1)
  u8 adf_T=0;						//�ο�����Ƶλ,����ռ�ձ�50%,��������
	u8 Double_Buf=0;				//˫������ 0��DISABLE 1:ENABLE
	u8 Charge_Pump=8;				//��ɱõ�������
	u8 LDP=3;								//������⾫��   0: ����С����Ƶ  3:����������Ƶ
	u8 PD_Polarity=1;				//����������  0: NEGATIVE  1:POSITIVE
	u8 Power_Down=0;				//0: disable  1:enable
	/**********************R1****************************************/
	u16 adf_MOD=2;			
	u16 adf_PHASE=1;
	/**********************R0****************************************/
	u16 adf_INT=300;
  u16 adf_FARC=0;
	
	/* ��ʼ���������� */
	CLR_SCL();
	CLR_LE();
	
	
	//���üĴ���5
	adf_data = 0x00580000;		//��������   LD���ŵĹ�����ʽΪ��������   D23 D22=01
	adf_data =adf_data | ADF_R5;	
	adf_data = adf_data | (LD_Pin_Mode << 22);
	ADF4351_Write(adf_data);
	
	
	//���üĴ���4
	adf_data = 0x00800038;
	/*(DB23=1)The signal is taken from the VCO directly,�ź�ֱ�Ӵ�VCO���
	���޸�RF divider, R��ֵ(DB22-20)the RF divider is 16;
	(DB11=0)VCO powerd up;	����RF�������; Ƶ��ѡ��ʱ��,��Ƶ��125k, ��Ƶֵ160*/
	adf_data = adf_data | (Feedback_Select << 23);
	adf_data = adf_data | (RF_div64 << 20);		//RF divider is 16
	adf_data = adf_data | (160 << 12);		//Ƶ��ѡ��ʱ��
	adf_data = adf_data | (VCO_PowerDown << 11);
	adf_data = adf_data | (MTLD << 10);
	adf_data = adf_data | (AUX_Output << 9);
	adf_data = adf_data | (AUX_EN << 8);
	adf_data = adf_data | (AUX_Power << 6);
	adf_data = adf_data | (RF_Output_EN << 5);
	adf_data = adf_data | (RF_Output_Power << 3);
	adf_data = adf_data | ADF_R4;	
	ADF4351_Write(adf_data);
	
	
	//���üĴ���3
	adf_data = 0x00848000;	
	/*ѡ���Ƶ�Σ�D23=1��, APB6ns(D22=0,=����С����Ƶʹ��),,(D21=0,С����Ƶʹ��) ʹ��CSR(D18=1),(D16 D15=01)��������
	���޸�clock divider value��ֵ*/
	adf_data = adf_data | (Band_Clock_Mode << 23);
	adf_data = adf_data | (APB << 22);
	adf_data = adf_data | (Charge_Cancel << 21);
	adf_data = adf_data | (CSR << 18);
	adf_data = adf_data | (Clk_Div_Mode << 15);
	adf_data = adf_data | (adf_Locktime << 3);
	adf_data = adf_data | ADF_R3;	
	ADF4351_Write(adf_data);
	
	//���üĴ���2
	adf_data = 0x61002040;
	//����ɢ���, ���òο���Ƶ, ����Ƶ������ʹ��(������������)
	//ʹ��˫������, ���õ�ɰ�����0.31, С��N��Ƶ(40), ����R��Ƶ����ֵΪ1
	//���ü������ļ���, (DB6)ͬ���˲���1,�����˲���0,������ͬ���˲���
	adf_data = adf_data | (Low_Noise_Spur_Mode << 29);
	adf_data = adf_data | (Muxout << 26);
	adf_data = adf_data | (adf_T << 24);
	adf_data = adf_data | (adf_R << 14);
	adf_data = adf_data | (Double_Buf << 13);
	adf_data = adf_data | (Charge_Pump << 9);
	adf_data = adf_data | (LDP << 7);
	adf_data = adf_data | (PD_Polarity << 6);	
	adf_data = adf_data | (Power_Down << 5);	
	adf_data = adf_data | ADF_R2;	
	ADF4351_Write(adf_data);
	
	//���üĴ���1
	adf_data = 0x01008000;
	//������λ����,Ԥ��Ƶ����ֵΪ8/9
  //��λ��Ϊ1
	adf_data = adf_data | (adf_PHASE << 15);
	adf_data = adf_data | (adf_MOD << 3);
	adf_data = adf_data | ADF_R1;	
	ADF4351_Write(adf_data);
	
	//���üĴ���0
	adf_data = 0x00000000;
	adf_data = adf_data | (adf_INT << 15);
	adf_data = adf_data | (adf_FARC << 3);
	adf_data= adf_data | ADF_R0;	
	ADF4351_Write(adf_data);	
	
}


/* 
	���������ֹƵ�ʣ�����Ƶ�� ����� N 
	Ĭ��FARC=0,D=T=0,R=1	
*/
u8 ADF_SetInit(u16 Start_Freq, u16 Stop_Freq)
{
	u8 Frequency;
	if((Start_Freq*64)>2200&&(Stop_Freq*64)<4400) ;
	else if((Start_Freq*32)>2200&&(Stop_Freq*32)<4400);
	else if((Start_Freq*16)>2200&&(Stop_Freq*16)<4400);
	else if((Start_Freq*8)>2200&&(Stop_Freq*8)<4400);
	else if((Start_Freq*4)>2200&&(Stop_Freq*4)<4400);
	else if((Start_Freq*2)>2200&&(Stop_Freq*2)<4400);
	else  return 0;
	
}

/* ��������ȡƵ�� */
u8 ADF_Set_AllFre(u16 Freq,u16 Fresout)
{
	u8 RF_Div;
	u16 Fpfd;
	u32 adf_data;
	u16 adf_R;				//RF�ο���Ƶϵ��
  u8 adf_D=0;					//RF REFin��Ƶ��λ(0 or 1)
  u8 adf_T=0;					//�ο�����Ƶλ,����ռ�ձ�50%,��������
  u16 adf_Locktime=160;
  u16 adf_MOD=1;
  u16 adf_INT=256;
  u16 adf_FARC=0;
  u16 adf_PHASE=1;
  u8 pinduan;
	if((Freq*2)>2200&&(Freq*2)<4400) RF_Div=2; 
	else if((Freq*4)>2200&&(Freq*4)<4400) RF_Div=4;
	else if((Freq*8)>2200&&(Freq*8)<4400) RF_Div=8;
	else if((Freq*16)>2200&&(Freq*16)<4400) RF_Div=16;
	else if((Freq*32)>2200&&(Freq*32)<4400) RF_Div=32;
	else if((Freq*64)>2200&&(Freq*64)<4400) RF_Div=64;
	else return 0;
	Fpfd=Fresout*RF_Div;
	adf_R=10000/Fpfd;
	adf_INT=Freq*1000*RF_Div/Fpfd;	
	
	/* ��ʼ���������� */
	CLR_SCL();
	CLR_LE();
	
	
	//���üĴ���5
	adf_data = 0x00580000;		//��������   LD���ŵĹ�����ʽΪ��������   D23 D22=01
	adf_data =adf_data | ADF_R5;	
	ADF4351_Write(adf_data);
	
	
	//���üĴ���4
	adf_data = 0x00800038;
	/*(DB23=1)The signal is taken from the VCO directly,�ź�ֱ�Ӵ�VCO���
	���޸�RF divider, R��ֵ(DB22-20)the RF divider is 16;
	(DB11=0)VCO powerd up;	����RF�������; Ƶ��ѡ��ʱ��,��Ƶ��125k, ��Ƶֵ160*/
	adf_data = adf_data | (RF_div32 << 20);		//RF divider is 16
	adf_data = adf_data | (160 << 12);		//Ƶ��ѡ��ʱ��
	adf_data = adf_data | ADF_R4;	//(DB5=1)RF output is enabled;(DB4-3=3H)Output power level is 5dBm 
	ADF4351_Write(adf_data);
	
	
	//���üĴ���3
	adf_data = 0x00848000;	
	/*ѡ���Ƶ�Σ�D23=1��, APB6ns(D22=0,=����С����Ƶʹ��),,(D21=0,С����Ƶʹ��) ʹ��CSR(D18=1),(D16 D15=01)��������
	���޸�clock divider value��ֵ*/
	adf_data = adf_data | (adf_Locktime << 3);
	adf_data = adf_data | ADF_R3;	
	ADF4351_Write(adf_data);
	
	//���üĴ���2
	adf_data = 0x61002040;
	//����ɢ���, ���òο���Ƶ, ����Ƶ������ʹ��(������������)
	//ʹ��˫������, ���õ�ɰ�����0.31, С��N��Ƶ(40), ����R��Ƶ����ֵΪ1
	//���ü������ļ���, (DB6)ͬ���˲���1,�����˲���0,������ͬ���˲���
	adf_data = adf_data | (adf_D << 25);
	adf_data = adf_data | (adf_T << 24);
	adf_data = adf_data | (adf_R << 14);	
	adf_data = adf_data | ADF_R2;	
	ADF4351_Write(adf_data);
	
	//���üĴ���1
	adf_data = 0x01008000;
	//������λ����,Ԥ��Ƶ����ֵΪ8/9
  //��λ��Ϊ1
	adf_data = adf_data | (adf_PHASE << 15);
	adf_data = adf_data | (adf_MOD << 3);
	adf_data = adf_data | ADF_R1;	
	ADF4351_Write(adf_data);
	
	//���üĴ���0
	adf_data = 0x00000000;
	adf_data = adf_data | (adf_INT << 15);
	adf_data = adf_data | (adf_FARC << 3);
	adf_data= adf_data | ADF_R0;	
	ADF4351_Write(adf_data);	
	
	return 1;
}

