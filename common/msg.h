/******************************************************************
   本程序只供学习使用，未经作者许可，不得用于其它任何用途
      我的邮箱：computer-lov@tom.com
        欢迎访问我的blog：  http://computer00.21ic.org

KEY.H  file

作者：Computer-lov
建立日期: 2007.03.20
修改日期: 2007.03.22
版本：V1.1
版权所有，盗版必究。
Copyright(C) Computer-lov 2007-2017
All rights reserved            
*******************************************************************/

#ifndef _MSG_H_
#define _MSG_H_


#define NO_MSG 0xff

#define MSG_POOL_SIZE (3+16)


extern u8 iTimerTick;

extern void create_msg(u8 *buf,u8 size);
extern void flush_msg(u8 *buf);
extern u8 send_msg(u8 *buf,u8 msg);
extern u8 get_msg(u8 *buf);

extern u8 aQMsgSysBuff[MSG_POOL_SIZE];
extern volatile u8  delayCounter;

extern u8 TimerTick;
extern void PutMsg(u8 msg);
extern u8 GetMsg(void);
extern void FlushMsg();
extern void SetTimerTick(u8 iTick);
extern void KillTimerTick();

void MSG2_Test();


enum
{

  TIMER_TICK = 0x50,
  UART_REV_ONE_FRAME,
  MSG_BTV4_SEND_OK,
  MSG_BTV4_SEND_FAIL,

};


#endif