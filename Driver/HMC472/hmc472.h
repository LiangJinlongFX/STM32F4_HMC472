#ifndef __HMC472_H
#define __HMC472_H	 
#include "sys.h"

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

#define HMC472A_V1	PDout(5)	
#define HMC472A_V2 	PDout(4)	
#define HMC472A_V3 	PDout(3)	
#define HMC472A_V4 	PDout(2)	
#define HMC472A_V5 	PDout(1)
#define HMC472A_V6 	PDout(0)	

#define HMC472B_V1 	PDout(13)	
#define HMC472B_V2	PDout(12)
#define HMC472B_V3 	PDout(11)	
#define HMC472B_V4 	PDout(10)	 
#define HMC472B_V5 	PDout(9)
#define HMC472B_V6 	PDout(8)

void HMC472_Init(void);
u8 HMC472_Con(u16 Con_Num , u8 Attenuator_Num);    //   Con_Num：衰减量  Attenuator_Num  0:单片模式   1；双片模式
#endif

