#include "config.h"

//**************testmode****************************************//
#define TEST_TIMER  BIT(0)
#define TEST_UART   BIT(1)

//**************timer define****************************************//
#define TIMER0      BIT(0)
#define TIMER1      BIT(1)
#define TIMER2      BIT(2)

#define MODE_TIME   BIT(0)
#define MODE_CONT   BIT(1)
#define MODE_PWM    BIT(2)

#define TIME_1PSC_CNT     4
#define TIME_2PSC_CNT     8
#define TIME_4PSC_CNT     16
#define TIME_8PSC_CNT     32
#define TIME_16PSC_CNT    64
#define TIME_32PSC_CNT    125
#define TIME_64PSC_CNT    250
#define TIME_128PSC_CNT   500
//**************xxx define****************************************//

//#define ERROR             5
u8 startCapCounterFlag;
u16 externPulseCounter;
u16 gbPulseTemp;
u8 time40ms_cnt;

/************************************************************
@
************************************************************/
void printf_ccr()
{
  u16 ccr1;
  u16 ccr2;
  u16 ccr3;
  
  ccr1  = TIM2_CCR1H<<8;
  ccr1 |= TIM2_CCR1L;
  ccr2  = TIM2_CCR2H<<8;
  ccr2 |= TIM2_CCR2L;
  ccr3  = TIM2_CCR3H<<8;
  ccr3 |= TIM2_CCR3L;
  
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
void TTCounterRun()                   //放入计数模式的定时器中断中
{
  if(startCapCounterFlag == 1)
  {
    externPulseCounter++;
  }
}

u16 TTCounterCalculator()
{
  u16 ret = 0;
  
  if(startCapCounterFlag == 1)
  {
    time40ms_cnt++;
    if(time40ms_cnt >= 20)
    {
      time40ms_cnt = 0;
      gbPulseTemp = externPulseCounter;
//      deg_string("@");
//      printf_dec_u16(externPulseCounter);
      externPulseCounter = 0;
    }
  }
  
  return ret;
}


/************************************************************
@
************************************************************/
void TTPutCommand(u8 testmode,u8 timer_sel,u8 cmd,u8 psc)
{
  u8 i;
  u8 buf[10];  
  
  buf[0] = 0xFA;            //head
  buf[1] = 0x55;            //head
  buf[2] = testmode;       
  buf[3] = timer_sel;      //select timerX
  buf[4] = cmd;              //timer mode
  buf[5] = psc;             //prescale 1,2,4,8,16,32,64,128
  buf[6] = 0x00;
  buf[7] = 0x00;
  buf[8] = 0xdd;
  buf[9] = 0xcc;
  
  for(i=0;i<10;i++)
  {
    UART_sendbyte(buf[i]);
  }
  
}
/************************************************************
@
************************************************************/
u16 cal2npower(u8 n)
{
  u8 len;
  u16 s = 1;
  
  for(len=1;len<=n;len++)
  {
    s *=2;
  }
  
  return s;
}
/************************************************************
@
************************************************************/
void BJ501TimerTest()
{

  u8 timer_sel;
  u8 timer_mode;
  u16 timer_psc;
 // u8 delay_cnt;
  u16 pWith,pWithS;
  u8 msg;
  u8 animateCounter;
//  u16 tmp;
//  u16 tmp2;
//  u16 tmp3;
  
  deg_string("/*****BJ501 timer test******/\n");

  stm8_tim2_capture();
  Init_Timer1();
  
  startCapCounterFlag = 1;
  
  timer_sel = TIMER0;
  timer_mode = MODE_TIME;
  timer_psc = 0;
  
  
  TTPutCommand(TEST_TIMER,timer_sel,timer_mode,timer_psc);
  deg_string("\ntimer");
  printf_u8(timer_sel);
  deg_string("--");
  deg_string("mode:");
  printf_u8(timer_mode);
  deg_string("--");
  deg_string("psc:");
  printf_u8(timer_psc);  
  //gbPulseTemp 理论值 40000*8/（psc*250）/2
  SetTimerTick(50);
  animateCounter = 0;
  while(1)
  {
    msg = get_msg2();
    
    switch(msg)
    {
      case TIMER_TICK:
        animateCounter++;
        if((animateCounter % 10) == 0)
        {
            timer_psc++;
           if(timer_psc > 7)
           {
            timer_psc = 0;
            timer_sel <<=1;
            if(timer_sel == BIT(3))
            {
              timer_sel = TIMER0;
            }
           }
           TTPutCommand(TEST_TIMER,timer_sel,timer_mode,timer_psc);
           break;
        }
        pWith = Get_Timer2_pWith();
//        printf_dec_u16(pWith);
        pWithS = (cal2npower(timer_psc)*250/64);
        if((pWith >= (pWithS-3)) &&  (pWith <= (pWithS+3)))
        {
          deg_string("\nT");
          UART_sendbyte(timer_sel/2+'0');      
          deg_string("-psc:");
          UART_sendbyte(timer_psc+'0');
          deg_string(":y");
        }
        else
        {
          deg_string("\nT");
          UART_sendbyte(timer_sel/2+'0');    
          deg_string("-psc:");
          UART_sendbyte(timer_psc+'0');
          deg_string(":n");     
          printf_dec_u16(pWith);
        }
        break;
    
    } 
  }
}





