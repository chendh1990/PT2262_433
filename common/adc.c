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
    ADC_CSR_CH = ch;        //选择AD通道：AIN6脚
    ADC_CSR_EOCIE = 0;     //1.打开ADC中断0.禁止中断
    ADC_CR1_SPSEL = 4;     //4分频时钟
    ADC_CR2_ALIGN = 1;    //数据右对齐,即ADC_DRL存低8位，ADC_DRH存高2位
    
    ADC_CR1_ADON = 1;      //打开adc
}

/************************************************************
@
************************************************************/
u16 getADC()
{
    u16 res;
    
    ADC_CR1_ADON = 1;      //打开adc
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
void bubble_sort(u16 *a,u8 len)//n为数组a的元素个数
{
    u16 i,j,temp;
   
    
    for(j=0;j<len-1;j++)
    {
        for(i=0;i<len-1-j;i++)
        {
            if(a[i]>a[i+1])//数组元素大小按升序排列
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
    ADC_CR1_ADON = 1;      //打开adc
//    adcRes = getADCAvr();
//    printf_u16(adcRes);

  }
}


