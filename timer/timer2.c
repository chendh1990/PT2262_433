#include "config.h"

/************************************************************
@
************************************************************/
 void stm8_tim2_capture(void)
{
    TIM2_PSCR  = 0x07;          //16M/128分频：8us 计数一次
    
    TIM2_ARRH = 0xff;
    TIM2_ARRL = 0xff;           //最大计数值 
    
    TIM2_CNTRH = 0x00;
    TIM2_CNTRL = 0x00;
          
    TIM2_CCMR1 = 0x02;         //CC1通道被配置为输入，IC1映射在TI2FP1上
    TIM2_CCMR2 = 0x01;         //CC1通道被配置为输入，IC2映射在TI2FP2上
//    TIM2_CCMR3 = 0x01;       //CC1通道被配置为输入，IC3映射在TI3FP3上
    
    TIM2_CR1 = 0x01;          //启动Tim2 向上计数模式    
    
    TIM2_CCER1 = 0x31;        //下降沿，上升沿捕获、使能捕获 CC2P,CC2E,CC1P,CC1E
//    TIM2_CCER2 = 0x01;        //上升沿捕获、使能捕获 CC3P,CC3E
    
    TIM2_SR1_CC1IF = 0;       //清捕获标志位  
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
    TIM2_CR1 = 0x00;//使能计数器
  //TIM2_IER=0x00;
    TIM2_IER = 0x01;//更新中断使能
    TIM2_EGR = 0x01;
    TIM2_CNTRH = 0;//计数器值
    TIM2_CNTRL = 0;
    TIM2_ARRH = 0;//自动重装的值
    TIM2_ARRL = 100;
    TIM2_PSCR = 0x03;//分频值 16M/8 , T = 0.5us
    //启动计数器
    TIM2_CR1 |= 0x01;
    GenPulseCnt = 100;
}

/************************************************************
@
************************************************************/
void Init_Timer2Counter(void)
{
    TIM2_CR1 = 0x00;//使能计数器

    TIM2_IER = 0x00;//更新中断使能
    TIM2_EGR = 0x00;
    TIM2_CNTRH = 0;//计数器值
    TIM2_CNTRL = 0;
    TIM2_ARRH = 0XFF;//自动重装的值
    TIM2_ARRL = 0XFF;
    TIM2_PSCR = 0x04;//分频值 16M/8 , T = 1us
    
    //启动计数器
    TIM2_CR1 |= 0x01;

}



