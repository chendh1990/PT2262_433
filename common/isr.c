#include "config.h"

extern unsigned long delay_counter;
/*****************************************************************************
@��ʱ��4�жϺ���
@
******************************************************************************/
#pragma vector = TIM4_OVR_UIF_vector//0x19
__interrupt void TIM4_OVR_UIF_IRQHandler(void)//��ӦIAP���жϵ�ַ��0x8060
{ //250*8us = 2ms

    static u8 cnt;
    static u8 keyScanCnt;
    
    cnt++;
    TIM4_SR=0x00;
    
    KeyCounterRun();
    BeepCounterRun();
    RF_KeyUpCounterRun();

    if(++keyScanCnt >= 2000/TIMER_INT_US)    
    {
      keyScanCnt = 0;
       KeyScan_jxh();
      if(delay_counter)
      {
        delay_counter--;
      }           
    }
//    KeyScan_jxh();
//    if(delay_counter)
//    {
//      delay_counter--;
//    }      

    if(cnt == 10000/TIMER_INT_US)   
    {
      cnt = 0;
      if(TimerTick && (iTimerTick++ >= TimerTick))
      {
         iTimerTick = 0;
         PutMsg(TIMER_TICK);
      }
    }
}

/*****************************************************************************
@ADC�жϺ���
@
******************************************************************************/
#pragma   vector = 0x18
__interrupt  void  ADC_EOC(void)
{
  ADC_CSR_EOC = 0;
  adcFinishFlag = 1;
  deg_string("\nadc int");

  adcResH = ADC_DRH;
  adcResL = ADC_DRL;
  printf_u16((u16)((adcResH<<8)|(adcResL)));
}


/*****************************************************************************
@��ʱ��1�����жϺ���
@
******************************************************************************/
#pragma vector = TIM1_CAPCOM_CC1IF_vector
__interrupt void TIM1_CAPCOM_CC1IF_IRQHandler(void)//��ӦIAP���жϵ�ַ��
{
  TIM1_SR1 = 0;    
  asm("nop");
  asm("nop");
  asm("nop");
}

/*****************************************************************************
@��ʱ��1����жϺ���
@
******************************************************************************/
#pragma vector = TIM1_OVR_UIF_vector
__interrupt void TIM1_OVR_UIF_IRQHandler(void)//��ӦIAP���жϵ�ַ��
{
  static u16 counter = 0;
  TIM1_SR1 = 0;    
  asm("nop");
  asm("nop");
  asm("nop");
  
  if(counter++ >= 1000)
  {
    counter = 0;
    PE_ODR_ODR5 =~PE_ODR_ODR5;  
  }
}



/*****************************************************************************
@��ʱ��2����жϺ���
@
******************************************************************************/
#pragma vector = TIM2_CAPCOM_CC1IF_vector
__interrupt void TIM2_CAPCOM_CC1IF_IRQHandler(void)//��ӦIAP���жϵ�ַ��
{
  TIM2_SR1_CC1IF = 0;  
  TIM2_SR1_CC2IF = 0;  
  TIM2_SR1_CC3IF = 0;  

}


/*****************************************************************************
@��ʱ��2����жϺ���
@
******************************************************************************/
#pragma vector = TIM2_OVR_UIF_vector
__interrupt void TIM2_OVR_UIF_IRQHandler(void)//��ӦIAP���жϵ�ַ��
{
  TIM2_SR1 = 0;    
  PWM_Run();
//  PC_ODR_ODR3 = ~PC_ODR_ODR3;
//  if(GenPulseCnt)
//  {
//    GenPulseCnt--;
//  }
//  else
//  {
//    TIM2_CR1 &=~0x01;
//  }
}


/*****************************************************************************
@UART2�жϺ���
@
******************************************************************************/
//���յ��������ٷ��ͳ�ȥ
#ifdef UART2_R_OR_vector

#pragma vector = UART2_R_OR_vector//0x14
__interrupt void UART2_R_OR_IRQHandler(void)
{
    char recdat;
    
    recdat = UART2_DR;   
//    OXYInfoReceive(recdat);
    if(recdat);

    return;
}

#else

#pragma vector = UART1_R_OR_vector//0x14
__interrupt void UART1_R_OR_IRQHandler(void)
{
    char recdat;
    
    recdat = UART1_DR;   
    UartInfoReceive(recdat);
    if(recdat);

    return;
}

#endif


//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************
//*****************************************************************************

#if 1
/*****************************************************************************
@EXTI0�жϺ���
@PA
******************************************************************************/
#pragma vector = EXTI0_vector
__interrupt void EXTI0_IRQHandler(void)
{
  return;
}

/*****************************************************************************
@EXTI1�жϺ���
@PB
******************************************************************************/
#pragma vector = EXTI1_vector
__interrupt void EXTI1_IRQHandler(void)
{
  return;
}


/*****************************************************************************
@EXTI2�жϺ���
@PC
******************************************************************************/
#pragma vector = EXTI2_vector
__interrupt void EXTI2_IRQHandler(void)
{
  return;
}

/*****************************************************************************
@EXTI3�жϺ���
@
******************************************************************************/
#pragma vector = EXTI3_vector
__interrupt void EXTI3_IRQHandler(void)
{
    
  return;
}


/*****************************************************************************
@EXTI4�жϺ���
@
******************************************************************************/
#pragma vector = EXTI4_vector
__interrupt void EXTI4_IRQHandler(void)
{
    
  return;
}

#endif
