#include "config.h"

/*************	本地变量声明	**************/
#define		P_IR_RX  	RF_INPUT		//定义红外接收输入端口


bool B_IR_Press;
bool F0;
bool P_IR_RX_temp;			//Last sample
bool B_IR_Sync;				//已收到同步标志
u8 IR_BitCnt;				//编码位数

u16 IR_RxActiveCnt;

u16 IR_TimeBuf[48];
u8 IR_TimeIndex;


struct __EE_INFO_ EE_Info;
union _RF_INFO_ RF_Info;
struct __EE_RF_IDX_ EE_RF_Idx;
union RF_DataForm RF_data;

void EE_ReadRFMask(void)
{
  u8 EE_ID;
  u16 i;

  
  EEPROM_ReadByte(EE_USER_ID_ADDR,&EE_ID,1);
  if(EE_ID != 0XA5)
  {
    deg_string("Init EE\n");
    EE_ID = 0xA5;
    
    EEPROM_Unlock();
    
    EEPROM_WriteByte(EE_USER_ID_ADDR,&EE_ID,1);
    
    memset(RF_Info.ee_buf,0,EE_RF_SIZE);
    EEPROM_WriteByte(0,RF_Info.ee_buf,EE_RF_SIZE);
    
    memset((u8 *)&EE_RF_Idx,0,EE_RF_IDX_SIZE);
    EEPROM_WriteByte(0,(u8 *)&EE_RF_Idx,EE_RF_IDX_SIZE);
    
    EEPROM_Lock();
  }
  EEPROM_ReadByte(0,(u8 *)&EE_RF_Idx,EE_RF_IDX_SIZE);
  EEPROM_ReadByte(0,RF_Info.ee_buf,EE_RF_SIZE);
  deg_string("RF Read mask:");
  for(i=0;i<EE_RF_SIZE;i++)
  {
    if(i%(RF_KEY_MAX*4) == 0)
    {
      deg_string("\n");
    }
    printf_u8(RF_Info.ee_buf[i]);

  }
  deg_string("\n");
}


u8 EEPROM_ReadKeyIdx(u8 key,u8 state)
{
  u16 idx_addr;
  u8 dat;
  
  idx_addr = EE_IDX_ADDR+key*3+state;
  
  EEPROM_ReadByte(idx_addr,&dat,1);
  
  return dat;
  
}

void EEPROM_WriteKeyIdx(u8 key,u8 state,u8 dat)
{
  u16 idx_addr;
  u8 buf;
  
  buf = dat;
  
  idx_addr = EE_IDX_ADDR+key*3+state;
  EEPROM_Unlock();
  EEPROM_WriteByte(idx_addr,&buf,1);  
  EEPROM_Lock();
}


void RFKeyHandle(void)
{
  u8 i;
  bool k0_toggle = 0;
  bool k1_toggle = 0;
  bool k2_toggle = 0;
  static u32 Last_RF_Key;
  
  if(!B_IR_Press || RF_data.rf_data == 0)
  {
    B_IR_Press = 0;
    RF_data.rf_data = 0;
    return;
  }
  if(Last_RF_Key == RF_data.rf_data)            //短时间收到相同的码的处理
  {
    if(RF_KeyUpCounter < RF_UP_CNT)             //相同码间隔时间太短，不动作
    {
      Last_RF_Key = RF_data.rf_data;
      RF_KeyUpCounter = 0;
      B_IR_Press = 0;
      return;
    }
  }
  Last_RF_Key = RF_data.rf_data;
  RF_KeyUpCounter = 0;
  
  B_IR_Press = 0;
  for(i=0;i<RF_KEY_MAX;i++)
  {
    //*********************      KEY0   *********************************************
    if(RF_data.rf_data == RF_Info.stru.k0_tg_cmp[i])
    {
      if(!k0_toggle)
      {
        k0_toggle = 1;
        //k0 toggle
        deg_string("k0 toggle\n");
        LED1_PORT = ~LED1_PORT;
        JK1_PORT = ~JK1_PORT;     
        BeepCounter = TIMER_BEEP_CNT;
      }
    }
    if(RF_data.rf_data == RF_Info.stru.k0_on_cmp[i])
    {
      //k0 on
      deg_string("k0 on\n");
      LED1_PORT = 1;
      JK1_PORT = 1;     
      BeepCounter = TIMER_BEEP_CNT;
    }
    if(RF_data.rf_data == RF_Info.stru.k0_off_cmp[i])
    {
      //k0 off
      deg_string("k0 off\n");
      LED1_PORT = 0;
      JK1_PORT = 0;     
      BeepCounter = TIMER_BEEP_CNT;
    }
    
    //*********************      KEY1   *********************************************
    if(RF_data.rf_data == RF_Info.stru.k1_tg_cmp[i])
    {
      if(!k1_toggle)
      {
        k1_toggle = 1;
        //k1toggle
        deg_string("k1 toggle\n");
        LED2_PORT = ~LED2_PORT;
        JK2_PORT = ~JK2_PORT;     
        BeepCounter = TIMER_BEEP_CNT;
      }
    }
    if(RF_data.rf_data == RF_Info.stru.k1_on_cmp[i])
    {
      //k1 on
      deg_string("k1 on\n");
        LED2_PORT = 1;
        JK2_PORT = 1;     
        BeepCounter = TIMER_BEEP_CNT;
    }
    if(RF_data.rf_data == RF_Info.stru.k1_off_cmp[i])
    {
      //k1 off
      deg_string("k1 off\n");
      LED2_PORT = 0;
      JK2_PORT = 0;     
      BeepCounter = TIMER_BEEP_CNT;
    }
    
    //*********************      KEY2   *********************************************
    if(RF_data.rf_data == RF_Info.stru.k2_tg_cmp[i])
    {
      if(!k2_toggle)
      {
        k2_toggle = 1;
        //k0 toggle
        deg_string("k2 toggle\n");
        LED3_PORT = ~LED3_PORT;
        JK3_PORT = ~JK3_PORT;     
        BeepCounter = TIMER_BEEP_CNT;
        
      }
    }
    if(RF_data.rf_data == RF_Info.stru.k2_on_cmp[i])
    {
      //k2 on
      deg_string("k2 on\n");
        LED3_PORT = 1;
        JK3_PORT = 1;     
        BeepCounter = TIMER_BEEP_CNT;
    }
    if(RF_data.rf_data == RF_Info.stru.k2_off_cmp[i])
    {
      //k2 off
      deg_string("k2 off\n");
      LED3_PORT = 0;
      JK3_PORT = 0;     
      BeepCounter = TIMER_BEEP_CNT;
    }
  }
}


void RF_K0_Erase(void)
{
  u8 i;
  
  for(i=0;i<RF_KEY_MAX;i++)
  {
    RF_Info.stru.k0_tg_cmp[i] =  0|0X80000000;
    RF_Info.stru.k0_on_cmp[i] =  0|0X80000000;
    RF_Info.stru.k0_off_cmp[i] = 0|0X80000000;
  }
}
void RF_K1_Erase(void)
{
  u8 i;
  
  for(i=0;i<RF_KEY_MAX;i++)
  {
    RF_Info.stru.k1_tg_cmp[i] =  0|0X80000000;
    RF_Info.stru.k1_on_cmp[i] =  0|0X80000000;
    RF_Info.stru.k1_off_cmp[i] = 0|0X80000000;
  }
}
void RF_K2_Erase(void)
{
  u8 i;
  
  for(i=0;i<RF_KEY_MAX;i++)
  {
    RF_Info.stru.k2_tg_cmp[i] =  0|0X80000000;
    RF_Info.stru.k2_on_cmp[i] =  0|0X80000000;
    RF_Info.stru.k2_off_cmp[i] = 0|0X80000000;
  }
}

void EE_RF_Update(void)
{
  u16 i;
  
  EEPROM_Unlock();
  
  deg_string("need_update:\n");
  for(i=0;i<EE_RF_SIZE;i++)
  {
     if(i%(RF_KEY_MAX*4) == 0)
    {
      deg_string("\n");
    }   
    printf_u8(RF_Info.ee_buf[i]);
  }
  deg_string("\n");
  
  for(i=0;i<EE_RF_SIZE;i++)
  {
    if((i%4) == 0)
    {
      if(RF_Info.ee_buf[i]&0X80)
      {
        RF_Info.ee_buf[i] &= ~0X80;
          
        EEPROM_WriteByte(i,RF_Info.ee_buf+i,4); 
      }
    }
  }
  
  EEPROM_Lock();
}

void EE_WriteRFRecData(u8 key,u8 mode,u8 idx,u32 recData)
{
  if(key == 0)
  {
    if(mode == 0)
    {
      RF_Info.stru.k0_tg_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 1)
    {
      RF_Info.stru.k0_on_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 2)
    {
      RF_Info.stru.k0_off_cmp[idx] = recData|0X80000000;
    }
  }
  else if(key == 1)
  {
    if(mode == 0)
    {
      RF_Info.stru.k1_tg_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 1)
    {
      RF_Info.stru.k1_on_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 2)
    {
      RF_Info.stru.k1_off_cmp[idx] = recData|0X80000000;
    }
  }
  else if(key == 2)
  {
    if(mode == 0)
    {
      RF_Info.stru.k2_tg_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 1)
    {
      RF_Info.stru.k2_on_cmp[idx] = recData|0X80000000;
    }
    else if(mode == 2)
    {
      RF_Info.stru.k2_off_cmp[idx] = recData|0X80000000;
    }
  }
  EE_RF_Update();
}

void KEY_Study(u8 key)
{
  u8 msg;
  u8 done;
  u8 pairMode = 0;
  u8 k_idx;
  u16 pairModeCounter = 0;
   
  done = 0;
  PairKeyCounter = 0;
  while(!done)
  {
    msg = GetMsg();
    if(msg == PU_PWR || msg == PU_TIME || msg == PU_MEM)
    {
        done = 1;
    }
    
    pairModeCounter++;
    if(pairModeCounter == 1)            //0s
    {
        BeepCounter = TIMER_BEEP_CNT;
        pairMode = 0;  
    }
    if(pairModeCounter >= 10 && pairModeCounter <= 20)          //1s~2s
    {
      if(pairModeCounter == 10)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 12)   BeepCounter = TIMER_BEEP_CNT;
      pairMode = 1;  
    }
    if(pairModeCounter >= 22 && pairModeCounter <= 28)          //3s~4s
    {
      if(pairModeCounter == 22)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 24)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 26)   BeepCounter = TIMER_BEEP_CNT;
      pairMode = 2;  
    }
    if(pairModeCounter >= 35 && pairModeCounter <= 45)          //5s~6s
    {
      if(pairModeCounter == 35)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 37)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 39)   BeepCounter = TIMER_BEEP_CNT;
      if(pairModeCounter == 41)   BeepCounter = TIMER_BEEP_CNT;
      pairMode = 3;  
    }
//    if(pairModeCounter > 60)
//    {
//      
//    }
    if(pairModeCounter >= 200) pairModeCounter = 200;
    _delay_ms_timer(100);
  }
  
  
  if(pairMode == 3)
  {
    deg_string("erase key:\n");
    printf_u8(key);
    deg_string("\n");
    if(key == 0)
    {
      RF_K0_Erase();
    }
    else if(key == 1)
    {
      RF_K1_Erase();
    }
    else if(key == 2)
    {
      RF_K2_Erase();
    }
    EE_RF_Update();
    EE_ReadRFMask();
    BeepCounter = TIMER_BEEP_CNT;
    while(BeepCounter);   
    return;
  }
  
  pairModeCounter = 0;
  done = 0;
  SetTimerTick(50);
  while(!done)
  {
    PT2262_RX();
    msg = GetMsg();
    if(msg == TIMER_TICK) pairModeCounter++;
    if(B_IR_Press)
    {
        B_IR_Press = 0;
        
        EEPROM_ReadByte(0,(u8 *)&EE_RF_Idx,EE_RF_IDX_SIZE);
        
        k_idx = key*3+pairMode;
        EE_RF_Idx.idx[k_idx] = EEPROM_ReadKeyIdx(key,pairMode);
        if(EE_RF_Idx.idx[k_idx] < RF_KEY_MAX-1)
        {
          EE_RF_Idx.idx[k_idx]++;
        }
        else
        {
          EE_RF_Idx.idx[k_idx] = 0;
        }
        
        EEPROM_WriteKeyIdx(key,pairMode,EE_RF_Idx.idx[k_idx]);
        
        EE_WriteRFRecData(key,pairMode,EE_RF_Idx.idx[k_idx],RF_data.rf_data);
        done = 1;
        deg_string("dat:");
        printf_u8(RF_data.buf[0]);
        printf_u8(RF_data.buf[1]);
        printf_u8(RF_data.buf[2]);
        printf_u8(RF_data.buf[3]);
        deg_string("\n");
        
    }
    
    if(pairModeCounter >= RF_PAIR_TIMEOUT)     //500ms*20 = 10 000ms = 10s超时
    {
      done = 1;
    }

  }
  KillTimerTick();
  EE_ReadRFMask();
  B_IR_Press = 1;
  while(BeepCounter);
}



//*******************************************************************************************
//**************************** IR RECEIVE MODULE ********************************************
void PT2262_RX(void)
{
  u16 SampleTime;
  u16 divData;
  u16 buf[4];
  u8 i;
  u8 dataConfirm = 1;
  
  if(IR_RxActiveCnt)
  {
    IR_RxActiveCnt--;
    return;	
  }
//  while(!P_IR_RX);
//  {
//  }
//  SampleTime = TIM_GetCounter(TIM1);			//get the sample time
//  printf_dec_u16(SampleTime);
//  TIM_SetCounter(TIM1, 0);					//Clear the sample counter
//  
//  while(P_IR_RX);
//  {
//  }
//  SampleTime = TIM_GetCounter(TIM1);			//get the sample time
//  printf_dec_u16(SampleTime);
//  TIM_SetCounter(TIM1, 0);					//Clear the sample counter
  

  F0 = P_IR_RX_temp;						//Save Last sample status
  P_IR_RX_temp = P_IR_RX;					//Read current status
  
  if(!B_IR_Sync)
  {
    if(F0 != P_IR_RX_temp)
    {
      SampleTime = TIM_GetCounter(TIM1);			//get the sample time
      TIM_SetCounter(TIM1, 0);					//Clear the sample counter
      if(P_IR_RX_temp)
      {
        
        //if(SampleTime >= 10000 && SampleTime <= 12000)
       if(SampleTime >= 8500 && SampleTime <= 12000)
        {
//          printf_dec_u16(SampleTime);
          B_IR_Sync = 1;
          IR_BitCnt = D_IR_BIT_NUMBER;	//Load bit number        
          IR_TimeIndex = 0;         
        }
      }
    }
  }
  else
  {
    if(IR_BitCnt)
    {
      if(IR_BitCnt&1)
      {
        if(P_IR_RX_temp == 1)
        {
          SampleTime = TIM_GetCounter(TIM1);
          IR_TimeBuf[IR_TimeIndex++] = SampleTime;
          if((SampleTime > D_IR_DATA_MAX) || (SampleTime < D_IR_DATA_MIN))      //前处理
          {
            //deg_string("x1:");
            //printf_dec_u16(SampleTime);
            //deg_string("\n");
            IR_RxActiveCnt = 0;
            B_IR_Sync = 0;      		
          }          
          TIM_SetCounter(TIM1, 0);
          IR_BitCnt--;
        }       
      }
      else
      {
        if(P_IR_RX_temp == 0)
        {
          SampleTime = TIM_GetCounter(TIM1);
          IR_TimeBuf[IR_TimeIndex++] = SampleTime;
          if((SampleTime > D_IR_DATA_MAX) || (SampleTime < D_IR_DATA_MIN))      //前处理
          {
            //deg_string("x2:");
            //printf_dec_u16(SampleTime);
            //deg_string("\n");
            IR_RxActiveCnt = 0;
            B_IR_Sync = 0;      		
          }
          TIM_SetCounter(TIM1, 0);
          IR_BitCnt--;
        }
      }
    }
    else
    {
      IR_RxActiveCnt = 200;
      B_IR_Sync = 0;  
      
//      deg_string("\n***********************************************************\n");
//      for(IR_TimeIndex=0;IR_TimeIndex<48;IR_TimeIndex++)
//      {
//        printf_dec_u16(IR_TimeBuf[IR_TimeIndex]);
//      }

      dataConfirm = 1;
      //时间不符 后处理
      for(i=0;i<24;i++)
      {
        divData = IR_TimeBuf[i*2+0]+IR_TimeBuf[i*2+1];
        if((divData > D_IR_SUM_MAX) || (divData < D_IR_SUM_MIN))
        {
//          deg_string("x3:");
//          printf_dec_u16(divData);
//          deg_string("\n");
          dataConfirm = 0;
          break;
        }
      }
      RF_data.rf_data = 0;
      if(dataConfirm)
      {
        //解析数据
        for(i=0;i<12;i++)
        {
          buf[0] = IR_TimeBuf[i*4+0];
          buf[1] = IR_TimeBuf[i*4+1];
          buf[2] = IR_TimeBuf[i*4+2];
          buf[3] = IR_TimeBuf[i*4+3];
          
          RF_data.rf_data <<= 1;
          if((buf[0] > buf[1]) && (buf[2] > buf[3]))
          {
             RF_data.rf_data++;
             RF_data.rf_data <<= 1;
             deg_string("1");
          }
          else if((buf[0] < buf[1]) && (buf[2] > buf[3]))
          {
            RF_data.rf_data++;
            RF_data.rf_data <<= 1;
            RF_data.rf_data++;
            deg_string("f");
          }
          else
          {
            RF_data.rf_data <<= 1;
            deg_string("0");
          }
        }
        
        if(RF_data.rf_data)
        {
          B_IR_Press = 1;
//          RF_data.rf_data = 0X00AA5522;
          deg_string("\n");
          deg_string("RF_data.rf_data:");
          printf_u8(RF_data.buf[1]);
          printf_u8(RF_data.buf[2]);
          printf_u8(RF_data.buf[3]);
          deg_string("\n");
        }
      }
      
//      deg_string("\n");
//      for(i=0;i<48;i++)
//      {
//        printf_dec_u16(IR_TimeBuf[i]);
//      }
      
      
/* 
002 006 005 002 
002 005 005 002 
002 005 006 001
002 006 005 002 
002 005 005 002 
002 005 006 001 
002 005 006 002 
001 006 005 002 
      
005 002 005 002 
002 005 002 005 
002 006 001 006 
002 005 002 005 
      
      
引导码10ms  短400us  长1ms      
可见PT2622软件滤除干扰比较难
*/
      

    }
  }

}
