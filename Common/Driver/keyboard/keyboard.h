#ifndef __KEYBOARD_H
#define __KEYBOARD_H
#include "sys.h"

/*********************************************************************************
**********************************************************************************
* �ļ�����: KEYBOARD.c                                                                
* �ļ�������4*4���������������                                                            
* �������ڣ�2017.8.06                                                           
* ��    ����V1.0                                                                 
* ��    �ߣ�liang                                                               
* ˵    ����ֻ�����ú�IO��ӳ��
						֧��STM32����˿�ӳ��
						֧�ֵ��ΰ��»�����ģʽ* 
**********************************************************************************
*********************************************************************************/


/*    ���̶˿ں궨��        */
#define keyBoard_Out1		PAout(0)	
#define keyBoard_Out2 	PAout(1)	
#define keyBoard_Out3 	PAout(2)	
#define keyBoard_Out4 	PAout(3)	

#define keyBoard_In1 		PAin(6)
#define keyBoard_In2 		PAin(7)	
#define keyBoard_In3 		PCin(4)	
#define keyBoard_In4 		PCin(5)	

#define keyBoard_InO1 	PAout(6)
#define keyBoard_InO2 	PAout(7)	
#define keyBoard_InO3 	PCout(4)	
#define keyBoard_InO4 	PCout(5)	

void Key_Init(void);
u8 Read_KeyValue(void);
u8 Scan_key(u8 Mode);
#endif

