#ifndef __HMC472_H
#define __HMC472_H	 
#include "sys.h"

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

#define HMC472A_V1	PCout(0)	
#define HMC472A_V2 	PCout(1)	
#define HMC472A_V3 	PCout(2)	
#define HMC472A_V4 	PCout(3)	
#define HMC472A_V5 	PCout(14)
#define HMC472A_V6 	PCout(15)	

#define HMC472B_V1 	PDout(11)	
#define HMC472B_V2	PDout(10)
#define HMC472B_V3 	PDout(9)	
#define HMC472B_V4 	PDout(8)	 
#define HMC472B_V5 	PDout(7)
#define HMC472B_V6 	PDout(6)

void HMC472_Init(void);
u8 HMC472_Con(double Con_Num , u8 Attenuator_Num);    //   Con_Num��˥����  Attenuator_Num  0:��Ƭģʽ   1��˫Ƭģʽ
#endif

