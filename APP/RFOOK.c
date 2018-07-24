#include "config.h"



//定义数据，数组，结构体
//union _RF_INFO_ RF_Info;

u16 PairKeyCounter;
u16 BeepCounter;
u16 RF_KeyUpCounter;

/************************************************************
@
************************************************************/
void STM8SEVALBoard_LED_Init()
{
  PB_DDR |= BIT(5);      //PB5输出
  PB_CR1 |= BIT(5);     //PB5推挽输出    
  PB_CR2 &=~BIT(5);     //PB4禁止中断 

}



void CT1_GPIOInit(void)
{
  
  PA_DDR &=~BIT(2);     //PA2为输入
  PA_CR1 &=~BIT(2);     //PA2浮空输入         
  PA_CR2 &=~BIT(2);     //PA2禁止中断  
  
  PA_DDR &=~BIT(1);     //PA1为输入
  PA_CR1 &=~BIT(1);     //PA1浮空输入         
  PA_CR2 &=~BIT(1);     //PA1禁止中断 
  
  PD_DDR |= (BIT(4)|BIT(2));      //PB5输出
  PD_CR1 |= (BIT(4)|BIT(2));     //PB5推挽输出    
  PD_CR2 &=~(BIT(4)|BIT(2));     //PB4禁止中断   
  
  PC_DDR |= (BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7));      
  PC_CR1 |= (BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7));        
  PC_CR2 &=~(BIT(3)|BIT(4)|BIT(5)|BIT(6)|BIT(7));        
 
}


/************************************************************
@
************************************************************/
void RF433_Main(void)
{
  u8 msg;
//  u8 optRes;
  
//  optRes = SystemSetOPTByte();
  
  Init_UART();
  
  KeyInit();
  
  Init_Timer4();
  
  CT1_GPIOInit();

  EE_ReadRFMask();
  
  TIM1_Init();
//  STM8SEVALBoard_LED_Init();
  
  //开全局中断
  EN_INTERRUPT;  
  
  DelayMs(150);
  
  PairKeyCounter = 0;
  
  deg_string("RF_Test..................\n");
  
//  while(1)
//  {
//    GetMsg();
//    if(KEY_TIME_INPUT) 
//    {
//        deg_string("TIME_\n");
//    }
//    if(KEY_MEM_INPUT) 
//    {
//        deg_string("MEM_\n");
//    }
//    if(KEY_PWR_INPUT) 
//    {
//        deg_string("PWR_\n");
//    }
//  }
  
  while(1)
  {
    
    msg = GetMsg();
    PT2262_RX();
    RFKeyHandle();
    
    switch(msg)
    {
      case PS_PWR:
          LED2_PORT = ~LED2_PORT;
          JK2_PORT = ~JK2_PORT;
          BeepCounter = TIMER_BEEP_CNT;
          break;
          
      case PS_TIME:
          LED3_PORT = ~LED3_PORT;
          JK3_PORT = ~JK3_PORT;   
          BeepCounter = TIMER_BEEP_CNT;
          break;
          
      case PS_MEM:
          LED1_PORT = ~LED1_PORT;
          JK1_PORT = ~JK1_PORT;     
          BeepCounter = TIMER_BEEP_CNT;
          break;
          
      case PL_PWR:
          KEY_Study(1);
          break;
          
      case PL_TIME:
          KEY_Study(2);
          break;
          
      case PL_MEM:
          KEY_Study(0);
          break;
          
          
//      case PU_PWR:
//          deg_string("PU_PWR\n");
//          break;
          
          
            
//      case UART_REV_ONE_FRAME:
//          deg_string(dataBuffer);
//          deg_string("\n");
//          deg_string("\n");
//          deg_string("\n");
//          if(dataBuffer[2] == '0')
//          {
//            if(dataBuffer[3] == '1')
//            {
//              LED1_PORT = 1;
//              JK1_PORT = 1;
//              BeepCounter = TIMER_BEEP_CNT;
//            }
//            else
//            {
//              LED1_PORT = 0;
//              JK1_PORT = 0;
//              BeepCounter = TIMER_BEEP_CNT;				
//            }
//          }
//          else if(dataBuffer[2] == '1')
//          {
//            if(dataBuffer[3] == '1')
//            {
//              LED2_PORT = 1;
//              JK2_PORT = 1;
//              BeepCounter = TIMER_BEEP_CNT;
//            }
//            else
//            {
//              LED2_PORT = 0;
//              JK2_PORT = 0;
//              BeepCounter = TIMER_BEEP_CNT;				
//            }						
//          }
//          else if(dataBuffer[2] == '2')
//          {
//            if(dataBuffer[3] == '1')
//            {
//              LED3_PORT = 1;
//              JK3_PORT = 1;
//              BeepCounter = TIMER_BEEP_CNT;
//            }
//            else
//            {
//              LED3_PORT = 0;
//              JK3_PORT = 0;
//              BeepCounter = TIMER_BEEP_CNT;				
//            }						
//          }
//          break;         

          
      default:
          break;          
    }
  }

}

void RF_KeyUpCounterRun(void)
{
  if(RF_KeyUpCounter < 50000) RF_KeyUpCounter++;
}

void BeepCounterRun(void)
{
  if(BeepCounter)
  {
    BeepCounter--;
    BEEP_PORT = ~BEEP_PORT;
  }
  else
  {
    BEEP_PORT = 0;
  }
}

void KeyCounterRun(void)
{
  if(PairKeyCounter < 50000) PairKeyCounter++;
}

