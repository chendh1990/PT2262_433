#ifndef __TIMER_PWM_H__
#define __TIMER_PWM_H__


extern u8 PWM_SW;
extern u8 PWM_R;
extern u8 PWM_D;
extern u8 PWM_CNT;
extern u8 PWM_INV;

extern void PWM_Run();
extern void PWM_Test();

#define PWM_Init()    PA_DDR |= (1<<3);PA_CR1 |= (1<<3);PA_CR2 = 0x00;PWM_SW=0;\
                      PWM_R=0;PWM_D=0;PWM_CNT=0;PWM_INV=0;
#define PWM_OUT_PIN   PA_ODR_ODR3//SPI_CR2_SSI//PA_ODR_ODR3

#endif