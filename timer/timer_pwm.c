#include "config.h"

u8 PWM_SW;
u8 PWM_R;
u8 PWM_D;
u8 PWM_CNT;
u8 PWM_INV;

/************************************************************
@
************************************************************/
void PWM_Run()
{
  if(PWM_SW == 1)
  {
    if((PWM_CNT > PWM_R)&&(PWM_CNT <= PWM_D))
    {
      if(PWM_INV == 0)
      {
        PWM_OUT_PIN = 1;
      }
      else
      {
        PWM_OUT_PIN = 0;   
      }
    }
    else
    {
    
       if(PWM_INV == 0)
      {
        PWM_OUT_PIN = 0;
      }
      else
      {
        PWM_OUT_PIN = 1;   
      }   
    }
    
    PWM_CNT++;
    if(PWM_CNT == 0)
    {
      PWM_CNT = PWM_R;
    }
  
  }

}

/************************************************************
@
************************************************************/
void PWM_Set(u8 TR,u8 TD,u8 INV)
{
  PWM_R = TR;
  PWM_D = TD;
  PWM_INV = INV;
  PWM_CNT = PWM_R;
  PWM_SW = 1;
}

/************************************************************
@
************************************************************/
void PWM_Test()
{
  Init_Timer2();
  PWM_Init();
  PWM_Set(6,255,0);
  
  while(1);
}