#ifndef __RFOOK_H__
#define __RFOOK_H__





#define TIM1    1
           




void RF433_Main(void);

void KeyCounterRun(void);
void BeepCounterRun(void);
void RF_KeyUpCounterRun(void);



extern u16 PairKeyCounter;
extern u16 BeepCounter;
extern u16 RF_KeyUpCounter;

/////////////////////////////////////////////////
void Timer1CounterTest();
#endif