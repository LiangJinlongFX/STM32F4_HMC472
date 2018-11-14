#ifndef __ADF4351_H
#define __ADF4351_H

#include "sys.h"


#define ADF_R0 0
#define ADF_R1 1
#define ADF_R2 2
#define ADF_R3 3
#define ADF_R4 4
#define ADF_R5 5
#define RF_div1 0
#define RF_div2 1
#define RF_div4 2
#define RF_div8 3
#define RF_div16 4
#define RF_div32 5
#define RF_div64 6

void ADF4351_Init(void);
void WriteToADF4350(unsigned char count, unsigned char *buf);
void Frequency_35MHz(void);
void ADF_SetFre(void);
void SetFreq_Res(void);
u8 ADF_Set_AllFre(u16 Freq,u16 Fresout);
#endif
