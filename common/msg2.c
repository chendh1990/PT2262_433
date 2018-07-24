/******************************************************************
*msg2.c
*
*       
*******************************************************************/
#include "config.h"

#define MSG2_POOL_SIZE (16)

u8 MsgIndex;
u8 MessageBuff[MSG2_POOL_SIZE+2];


/************************************************************
@清空消息池
************************************************************/
void flush_msg2()
{
  u8 i;
  MsgIndex = 0;

  for(i=0;i<MSG2_POOL_SIZE;i++)
  {
    MessageBuff[i] = 0;
  }
 
}


/************************************************************
@//后进先出
************************************************************/
void put_msg_fifo(u8 msg)
{ 
  u8 i;
  u8 tmp;
  if(MsgIndex < MSG2_POOL_SIZE)
  {
    MessageBuff[MsgIndex] = msg;   
    MsgIndex++;
  }
  else
  {
    for(i=1;i<MSG2_POOL_SIZE;i++)
    {
        tmp =  MessageBuff[i];
        MessageBuff[i-1] = tmp;       
    }
    MessageBuff[MSG2_POOL_SIZE-1] = msg;
    MsgIndex = MSG2_POOL_SIZE;
  }
}

/************************************************************
@//后进后出
************************************************************/
void put_msg_lifo(u8 msg)
{
  u8 i;
  u8 tmp;
  
  i = MsgIndex;
  while(i--)
  {
    if(i < MSG2_POOL_SIZE-1)
    {
      tmp =  MessageBuff[i];
      MessageBuff[i+1] = tmp;  
    }
  }
  MessageBuff[0] = msg;
  if(MsgIndex < MSG2_POOL_SIZE)
  {
    MsgIndex++;
  }
    
}

/************************************************************
@获取消息
************************************************************/
u8 get_msg2()
{
    u8 msg;
    msg = NO_MSG;
     if(MsgIndex > 0)
    { 
      msg = MessageBuff[MsgIndex-1];
      MsgIndex--;
    }
    return msg;
}

/************************************************************
@打印消息池
************************************************************/
void printf_msg_pool()
{
  u8 i;
  deg_string("\nMsgIndex:");
  printf_dec_u8(MsgIndex);
  
  deg_string("\nbuf:");
  for(i=0;i<MSG2_POOL_SIZE;i++)
  {
    printf_dec_u8(MessageBuff[i]);
  }
}

/************************************************************
@消息测试函数
************************************************************/
void MSG2_Test()
{
  u8 msg;
  u8 tmp;
  deg_string("\n--------msg2 test-----------");
  
  SetTimerTick(100);
  while(1)
  {
      msg = GetMsg();  
      switch(msg)
      {
        case TIMER_TICK:
          tmp = get_msg2();
          //printf_msg_pool();  
          deg_string("\nget msg:");
          printf_dec_u8(tmp);          
          break;      
        case PS_PWR:
          put_msg_fifo(111);
          printf_msg_pool();
          break;
          
        case PL_MEM:
          tmp = get_msg2();
          printf_msg_pool();  
          deg_string("\nget msg:");
          printf_dec_u8(tmp);
          break;
      }
  }

}