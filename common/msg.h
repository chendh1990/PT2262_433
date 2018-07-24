/******************************************************************
   ������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
      �ҵ����䣺computer-lov@tom.com
        ��ӭ�����ҵ�blog��  http://computer00.21ic.org

KEY.H  file

���ߣ�Computer-lov
��������: 2007.03.20
�޸�����: 2007.03.22
�汾��V1.1
��Ȩ���У�����ؾ���
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