/******************************************************************
*msg.c
*
*       
*******************************************************************/
#include "config.h"

u8 aQMsgSysBuff[MSG_POOL_SIZE];

u8 TimerTick;
u8 iTimerTick;

#define START_IDX 3

/************************************************************
@
************************************************************/
void create_msg(u8 *buf,u8 size)
{
  size = size;
  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
}

/************************************************************
@
************************************************************/
void flush_msg(u8 *buf)
{
  buf[0] = 0;
  buf[1] = 0;
  buf[2] = 0;
}

/************************************************************
@
************************************************************/
static u8 idx;
u8 send_msg(u8 *buf,u8 msg)
{
  if(buf[0] < 16)
  {
          
    idx = buf[1];
    buf[START_IDX+(idx & (16-1))] = msg;
    idx++;
    if(idx > (16-1))
            idx = 0;
    buf[1] = idx;
    buf[0]++;
    return 0;//OK
  }
  return 1;//fail
}
/************************************************************
@
************************************************************/
u8 get_msg(u8 *buf)
{
  u8 msg;

  msg = NO_MSG;
  if(buf[0] > 0)
  {
    u8 idx;
    
    idx = buf[2];
    msg = buf[START_IDX+(idx & (16-1))];
    idx++;
    if(idx > (16-1))
            idx = 0;                 
    buf[2] = idx;
    buf[0]--;
    return msg;//OK
  }
  return msg;//fail
}

/************************************************************
@
************************************************************/
void PutMsg(u8 msg)
{
    //send_msg(aQMsgSysBuff,msg);	 
    put_msg_fifo(msg);
}

/************************************************************
@
************************************************************/
u8 GetMsg(void)
{
    u8 msg;
    IWDG_Refresh();
    //msg = get_msg(aQMsgSysBuff);
    msg = get_msg2();
    
    return msg;
}
/************************************************************
@
************************************************************/
void FlushMsg()
{
    flush_msg2();
    flush_msg(aQMsgSysBuff);
}




/*******************************************************************/
