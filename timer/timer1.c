#include "config.h"



/************************************************************
@
************************************************************/
void TIM1_Init(void)//延时函数，延时时间=单位时间*初值us
{
  TIM1_PSCRH = 0;  
  TIM1_PSCRL = 15;//时钟分频，每个单位为10us
  TIM1_ARRH=0XFF;//自动重装载
  TIM1_ARRL=0XFF;
  TIM1_IER=0X00;
  TIM1_CNTRH=0;//赋予初值
  TIM1_CNTRL=0;
  TIM1_CR1 |=0x01;//开计数器
	
}

/************************************************************
@
************************************************************/
void TIM1_Disable(void)
{
  TIM1_CR1 &=~0x01;//关计数器
}

/************************************************************
@
************************************************************/
void TIM_SetCounter(u8 TIMx,u16 cnt)
{
    
  TIM1_CNTRH = (u8)(cnt>>8);             //计数器值
  TIM1_CNTRL = (u8)(cnt); 

}

/************************************************************
@
************************************************************/
u16 TIM_GetCounter(u8 TIMx)
{
   u16 tmpcntr = 0;
   
   tmpcntr = (u16)(TIM1_CNTRH<<8);

  return (u16)(tmpcntr|(u16)(TIM1_CNTRL));
}

/************************************************************
@
************************************************************/
void _delay_us_timer(u16 t)
{
  TIM_SetCounter(TIM1, 0);
  while(TIM_GetCounter(TIM1) < t);
}

/************************************************************
@
************************************************************/
void _delay_ms_timer(u16 t)
{
  while(t--)
  {
    TIM_SetCounter(TIM1, 0);
    while(TIM_GetCounter(TIM1) < 1000);
  }
}

/************************************************************
@
************************************************************/
void Init_Timer1(void)
{
    TIM1_CR1 = 0x01;            //使能计数器
  //TIM1_IER=0x00;
    TIM1_IER = 0x01;            //更新中断使能
    TIM1_EGR = 0x01;
    TIM1_CNTRH = 0;             //计数器值
    TIM1_CNTRL = 0;
    TIM1_ARRH = 0;              //自动重装的值
    TIM1_ARRL = 200;
    TIM1_PSCRH = 0x00;
    TIM1_PSCRL = 0x07;          //分频值 16M/(PSCR[15:0]+1) = 2M  T = 0.5us
}


/************************************************************
@
************************************************************/
void Init_Timer1_CounterNoIntterupt()
{
    TIM1_CR1 = 0x00;                                    //禁止计数器
    
    TIM1_PSCRH  = 0;
    TIM1_PSCRL  = 15;                                   //分频值 16M/(PSCR[15:0]+1) = 1M  T = 1us    
    TIM1_IER    = 0x00;                                 //禁止更新中断
    TIM1_EGR    = 0x00;                                 //使能更新
    TIM1_CNTRH  = 0;                                    //计数器值
    TIM1_CNTRL  = 0;
    TIM1_ARRH   = (65535>>8)&0X00FF;                    //自动重装的值
    TIM1_ARRL   = (65535>>0)&0X00FF; 

    TIM1_CR1 = 0x01;                                    //使能计数器

}

/************************************************************
@
************************************************************/
 void stm8_tim1_capture(void)
{
    TIM1_PSCRH  = 0x00;          //16M/128分频：8us 计数一次
    TIM1_PSCRL  = 0x07;          //16M/128分频：8us 计数一次
    
    TIM1_ARRH = 0xff;
    TIM1_ARRL = 0xff;           //最大计数值 
    
    TIM1_CNTRH = 0x00;
    TIM1_CNTRL = 0x00;
    
    TIM1_CCMR1 = 0x01;         //配置通道1为输入
    TIM1_CCMR2 = 0x02;         
    
//    TIM2_CCMR1 = 0x02;         //配置通道1为输入
//    TIM2_CCMR2 = 0x01;         //配置通道2为输入
//    TIM2_CCMR3 = 0x01;         //配置通道CC3为输入
    
    TIM1_CR1 = 0x01;          //启动Tim2 向上计数模式    
    
    TIM1_CCER1 = 0x31;        //下降沿，上升沿捕获、使能捕获 CC2P,CC2E,CC1P,CC1E
//    TIM2_CCER2 = 0x01;        //上升沿捕获、使能捕获 CC3P,CC3E
    
    TIM1_SR1_CC1IF = 0;       //清捕获标志位  
//    TIM2_SR1_CC2IF = 0;
//    TIM2_SR1_CC3IF = 0;
    
//    TIM2_IER = 0x45;
//    TIM2_EGR = 0x45;
}

/************************************************************
@
************************************************************/
u16 Get_Timer1_PulseWith()
{
  s32 tmp,tmp2;
  
//  if(TIM2_SR1_CC1IF == 0)
//  {
//    return 0;
//  }

  tmp2 = TIM1_CCR1H<<8;
  tmp2 |= TIM1_CCR1L;
  tmp = TIM1_CCR2H<<8;
  tmp |= TIM1_CCR2L;
  
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
void printf_timer1_ccr()
{
  u16 ccr1;
  u16 ccr2;
  u16 ccr3;
  
  ccr1  = TIM1_CCR1H<<8;
  ccr1 |= TIM1_CCR1L;
  ccr2  = TIM1_CCR2H<<8;
  ccr2 |= TIM1_CCR2L;
  ccr3  = TIM1_CCR3H<<8;
  ccr3 |= TIM1_CCR3L;
  
  deg_string("\nCCR1:");
  printf_dec_u16(ccr1);
  deg_string("\nCCR2:");
  printf_dec_u16(ccr2);
  deg_string("\nCCR3:");
  printf_dec_u16(ccr3);
}


/************************************************************
@
************************************************************/
void Init_Timer1_PWM_ch1()
{
//   CLK_PCKENR1 |= 0x80;        //使能TIM1与fMASTER连接
//   //初始化捕获/比较模式寄存器1
//   TIM1_CCMR1 = 0x60;         //TIM1_CCMR1[6:4]=110,设置PWM模式1
//
//   //初始化捕获/比较使能寄存器1 
//   TIM1_CCER1 = 0x05;         //b0 CC1E=1,开启OC1信号输出到相应引脚
//                              //b1 CC1P=0,OC1高电平有效
//                              //b2 CC1NE=1,开启OC1N信号输出到相应引脚
//                              //b3 CC1NP=0,OC1高电平有效
//   //初始化刹车寄存器中MOE（主输出使能位）
//   TIM1_BKR |= 0x80;           //b7 MOE=1 使能OC和OCN引脚输出
//                              //b7 MOE=0 
//   
//   //设置自动重装寄存器（须先写高8位再写低8位）,决定PWM的频率
//   //  PWM频率：f=650KHZ, T=1.54us
//   //  时钟周期：t=1/(fmaster)=1/4MHZ = 0.25us
//   //  TIM1_ARR = T/t = 1.54us/0.25us = 6
//   TIM1_ARRH = 0x03;      
//   TIM1_ARRL = 0xff;
//   
//   //初始化比较寄存器，决定PWM的占空比 
//   TIM1_CCR1H = 0;
//   TIM1_CCR1L = 5;
//   
//   //初始化预分频器，fmaster不分频，（须先写高8位再写低8位）
//   TIM1_PSCRH = 0x00;        
//   TIM1_PSCRL = 0x08;
//   
//   TIM1_CR1 = 0x01;      //CEN=1,则允许计数  
 

}

/************************************************************
@
************************************************************/
void TestTimer1_main()
{
  u8 msg;
  
  Init_Timer1_PWM_ch1();
  SetTimerTick(50);
  while(1)
  {
    msg = get_msg2();
    switch(msg)
    {
      case TIMER_TICK:
          deg_string("\ntick");
          break;
    }
  }

}




