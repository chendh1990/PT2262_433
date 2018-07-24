/******************************************************************
*key.c
*
*      
*******************************************************************/
#include "config.h"



#define K_EFFECT_V      0
//volatile u8 delay_counter;
u8 keyCounter ;		//按键扫描计数

/************************************************************
@
************************************************************/
void KeyInit()
{
  PB_DDR &=~(BIT(4)|BIT(5));          
  PB_CR1 &=~(BIT(4)|BIT(5));                  
  PB_CR2 = 0X00;//BIT(3);              //PC3带中断
  
  PA_DDR &=~(BIT(3));             
  PA_CR1 &=~(BIT(3));             
  PA_CR2 = 0X00;   
}

/************************************************************
@
************************************************************/
void CheckADKey(u8 *flag)
{
    if(KEY_PWR_INPUT == K_EFFECT_V)
    {
      *flag |= KEY_PWR;
    }
    
    if(KEY_TIME_INPUT == K_EFFECT_V)
    {
      *flag |= KEY_TIME;
    }

    if(KEY_MEM_INPUT == K_EFFECT_V)
    {
      *flag |= KEY_MEM;
    }    

}


/************************************************************
@
************************************************************/
u8 KeyDetect(u8 cnt )
{
  static u8 keyTmp = 0;

  if (cnt == 0)
  {	
  }
  else if (cnt == 1)
  {   
    keyTmp = 0;
    CheckADKey(&keyTmp);     
  }
  else if (cnt == 4)
  {	
  }

  if((keyTmp == 0)&&(cnt == 4))
    keyTmp = NO_KEY;

  return keyTmp;
}



/*----------------------------------------------------------------------------*/
/**@brief 按键检测，每10ms进行一次
@return 无
*/
/*----------------------------------------------------------------------------*/
void KeyScan_jxh(void)
{
    static u8 keyValue = 0;
    static u8 cnt = 0;	
	
    u8 keyTmp = NO_KEY;
    u8 key_return = NO_KEY;

    keyTmp = KeyDetect(cnt);
    if(cnt == 4)
    {
      if (keyTmp == NO_KEY )
      {
          if (keyCounter >= KEY_LONG_TIMES)  //长按抬键
          {
              key_return = keyValue | KEY_LONG_UP;
          }
          else if (keyCounter >= KEY_SCAN_TIMES)   //短按抬键
          {
              key_return = keyValue | KEY_SHORT_UP;
          }
      
          keyValue = keyTmp;
          keyCounter = 0;
      }
      else if(keyTmp != keyValue)
      {
        keyValue = keyTmp;
        keyCounter = 0;
        //PutMsg(KEY_CHANGE);
      }	
      else
      {
          keyCounter++;
          if (keyCounter == KEY_SCAN_TIMES)			//去抖
          {
              key_return = keyValue;
          }
          else if (keyCounter == KEY_LONG_TIMES)				//长按
          {
              key_return = keyValue | KEY_LONG;
          }
          else if (keyCounter == (KEY_LONG_TIMES + KEY_HOLD_TIMES) )			//连按
          {
              key_return = keyValue | KEY_HOLD;
              keyCounter = KEY_LONG_TIMES;
          }

       }
        if (key_return != NO_KEY)
        {
            PutMsg(key_return);
        }
      }
      else if(cnt ==  0)
      {
              //PowerScan(keyTmp);

      }
	cnt = (cnt==4)?0:(cnt+1);

}


/*----------------------------------------------------------------------------*/
/**@brief 
   @param 无
   @return 无
   @note
*/
/*----------------------------------------------------------------------------*/
void SetTimerTick(u8 iTick)
{
    TimerTick = iTick;
	
}

/*----------------------------------------------------------------------------*/
/**@brief 
   @param 无
   @return 无
   @note
*/
/*----------------------------------------------------------------------------*/
void KillTimerTick()
{
    TimerTick = 0;
    iTimerTick = 0;
}


/************************************************************
@
************************************************************/
void DelayMs(u8 cnt)
{
   delay_counter = cnt*5;
   while(delay_counter)
   {
      GetMsg();
   }
}



/************************************************************
@
************************************************************/
void test_key_fun(u8 msg)
{
    switch(msg)
    {
      case PR_PWR:
        deg_string("\nPR_PWR");
        break;
      case PS_PWR:
        deg_string("\nPS_PWR");
        break;
      case PL_PWR:
        deg_string("\nL_PWR");
        break;
      case PU_PWR:
        deg_string("\nPU_PWR");
        break;
      case PH_PWR:
        deg_string("\nPH_PWR");
        break;
    }

}


