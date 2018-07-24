#ifndef __ADC_H__
#define __ADC_H__

void  adc_init(u8 ch);
void ADC_Test();
u16 getADCAvr();

extern u8 adcResH;
extern u8 adcResL;
extern u8 adcFinishFlag;

#endif