#include "config.h"

/************************************************************
@
************************************************************/
void Init_Timer4(void)
{
    TIM4_CR1=0x01;//ʹ�ܼ�����
  //TIM4_IER=0x00;
    TIM4_IER=0x01;//�����ж�ʹ��
    TIM4_EGR=0x01;
    
    TIM4_CNTR=TIMER_INT_US/8;//������ֵ
    TIM4_ARR=TIMER_INT_US/8;//�Զ���װ��ֵ
    
    TIM4_PSCR=0x07;//��Ƶֵ 16M/128  T = 8us
}


