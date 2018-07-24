#include "config.h"

#define ADCBUFSIZE  10

u8 adcResH;
u8 adcResL;
u16 adcRes;
u16 adcBuf[ADCBUFSIZE];

u8 adcFinishFlag;

/************************************************************
@
************************************************************/
static void delay(u16 cnt)
{
  for(;cnt>0;cnt--);
}

/************************************************************
@
************************************************************/
void  adc_init(u8 ch)
{
    ADC_CSR_CH = ch;        //ѡ��ADͨ����AIN6��
    ADC_CSR_EOCIE = 0;     //1.��ADC�ж�0.��ֹ�ж�
    ADC_CR1_SPSEL = 4;     //4��Ƶʱ��
    ADC_CR2_ALIGN = 1;    //�����Ҷ���,��ADC_DRL���8λ��ADC_DRH���2λ
    
    ADC_CR1_ADON = 1;      //��adc
}

/************************************************************
@
************************************************************/
u16 getADC()
{
    u16 res;
    
    ADC_CR1_ADON = 1;      //��adc
    adcFinishFlag = 0;

    while(!ADC_CSR_EOC);
//    while(!adcFinishFlag);
    ADC_CSR_EOC = 0;
    
    adcResH = ADC_DRH;
    adcResL = ADC_DRL;   
    
    res = (u16)((adcResH<<8)|(adcResL));
    
    return res;
}

/************************************************************
@
************************************************************/
void bubble_sort(u16 *a,u8 len)//nΪ����a��Ԫ�ظ���
{
    u16 i,j,temp;
   
    
    for(j=0;j<len-1;j++)
    {
        for(i=0;i<len-1-j;i++)
        {
            if(a[i]>a[i+1])//����Ԫ�ش�С����������
            {
                temp=a[i];
                a[i]=a[i+1];
                a[i+1]=temp;
            }
        }
    }
}

/************************************************************
@
************************************************************/
u16 getADCAvr()
{
  u8 i;
  u16 sum;
  
//  deg_string("\nadc org:");
  for(i=0;i<ADCBUFSIZE;i++)
  {
    adcBuf[i] = getADC();
    delay(100);
//    printf_u16(adcBuf[i]);
  }
  
  bubble_sort(adcBuf,ADCBUFSIZE);
  
//  deg_string("\nbubble:");
//  for(i=0;i<ADCBUFSIZE;i++)
//  {
//    printf_u16(adcBuf[i]);
//  }  
  
  sum = 0;
  for(i=2;i<8;i++)
  {
    sum += adcBuf[i]; 
  }
  
//  printf_u16(sum);
  return (sum/6);
  
}

/************************************************************
@
************************************************************/
void ADC_Test()
{
  deg_string("\nadc test!!!");
  PB_DDR = 0X00;
  PB_CR1 = 0X00;
  PB_CR2 = 0X00;
  adc_init(1);
  
  while(1)
  {
    DelayMs(100);
    ADC_CR1_ADON = 1;      //��adc
//    adcRes = getADCAvr();
//    printf_u16(adcRes);

  }
}


