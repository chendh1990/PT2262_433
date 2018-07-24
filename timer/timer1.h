#ifndef __TIMER1_H__
#define __TIMER1_H__


void TIM1_Init(void);
void TIM1_Disable(void);
void TIM_SetCounter(u8 TIMx,u16 cnt);
u16 TIM_GetCounter(u8 TIMx);
void _delay_us_timer(u16 t);
void _delay_ms_timer(u16 t);








void Init_Timer1(void);

void Init_Timer1_PWM_ch1();
void TestTimer1_main();
void Init_Timer1_CounterNoIntterupt();
#endif