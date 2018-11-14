#ifndef ADC_H
#define ADC_H
#include "sys.h"

typedef struct
{
	vu8 Mode_Num;
	vu16 Start_Freq;
	vu16 Stop_Freq;
	vu16 RF_Voltage;
	vu16 Step_Freq;
	vu16 Sweep_Time;
} DDS_TypeDef;

extern DDS_TypeDef DDS_Structest;


void Display1(void);
void Display2(void);




#endif

