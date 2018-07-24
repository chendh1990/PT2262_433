#include "config.h"

/************************************************************
@
************************************************************/
 void stm8_tim2_capture(void)
{
    TIM2_PSCR  = 0x07;          //16M/128��Ƶ��8us ����һ��
    
    TIM2_ARRH = 0xff;
    TIM2_ARRL = 0xff;           //������ֵ 
    
    TIM2_CNTRH = 0x00;
    TIM2_CNTRL = 0x00;
          
    TIM2_CCMR1 = 0x02;         //CC1ͨ��������Ϊ���룬IC1ӳ����TI2FP1��
    TIM2_CCMR2 = 0x01;         //CC1ͨ��������Ϊ���룬IC2ӳ����TI2FP2��
//    TIM2_CCMR3 = 0x01;       //CC1ͨ��������Ϊ���룬IC3ӳ����TI3FP3��
    
    TIM2_CR1 = 0x01;          //����Tim2 ���ϼ���ģʽ    
    
    TIM2_CCER1 = 0x31;        //�½��أ������ز���ʹ�ܲ��� CC2P,CC2E,CC1P,CC1E
//    TIM2_CCER2 = 0x01;        //�����ز���ʹ�ܲ��� CC3P,CC3E
    
    TIM2_SR1_CC1IF = 0;       //�岶���־λ  
//    TIM2_SR1_CC2IF = 0;
//    TIM2_SR1_CC3IF = 0;
    
//    TIM2_IER = 0x45;
//    TIM2_EGR = 0x45;
}


/************************************************************
@
************************************************************/
u16 Get_Timer2_pWith()
{
  s32 tmp,tmp2;
  
//  if(TIM2_SR1_CC1IF == 0)
//  {
//    return 0;
//  }

  tmp2 = TIM2_CCR1H<<8;
  tmp2 |= TIM2_CCR1L;
  tmp = TIM2_CCR2H<<8;
  tmp |= TIM2_CCR2L;
  
  tmp2 -= tmp;
  if(tmp2 < 0)
  {
    tmp2 = 0-tmp2;
  }
  
  return tmp2;
      
}

/************************************************************
@
************************************************************/
extern u8 GenPulseCnt;
void Init_Timer2(void)
{
    TIM2_CR1 = 0x00;//ʹ�ܼ�����
  //TIM2_IER=0x00;
    TIM2_IER = 0x01;//�����ж�ʹ��
    TIM2_EGR = 0x01;
    TIM2_CNTRH = 0;//������ֵ
    TIM2_CNTRL = 0;
    TIM2_ARRH = 0;//�Զ���װ��ֵ
    TIM2_ARRL = 100;
    TIM2_PSCR = 0x03;//��Ƶֵ 16M/8 , T = 0.5us
    //����������
    TIM2_CR1 |= 0x01;
    GenPulseCnt = 100;
}

/************************************************************
@
************************************************************/
void Init_Timer2Counter(void)
{
    TIM2_CR1 = 0x00;//ʹ�ܼ�����

    TIM2_IER = 0x00;//�����ж�ʹ��
    TIM2_EGR = 0x00;
    TIM2_CNTRH = 0;//������ֵ
    TIM2_CNTRL = 0;
    TIM2_ARRH = 0XFF;//�Զ���װ��ֵ
    TIM2_ARRL = 0XFF;
    TIM2_PSCR = 0x04;//��Ƶֵ 16M/8 , T = 1us
    
    //����������
    TIM2_CR1 |= 0x01;

}



