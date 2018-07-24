#include "config.h"

/************************************************************
@
************************************************************/
void Init_Timer4(void)
{
    TIM4_CR1=0x01;//使能计数器
  //TIM4_IER=0x00;
    TIM4_IER=0x01;//更新中断使能
    TIM4_EGR=0x01;
    
    TIM4_CNTR=TIMER_INT_US/8;//计数器值
    TIM4_ARR=TIMER_INT_US/8;//自动重装的值
    
    TIM4_PSCR=0x07;//分频值 16M/128  T = 8us
}



