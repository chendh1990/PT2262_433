#ifndef __MAIN_H__
#define __MAIN_H__

#define DIS_INTERRUPT    asm("sim")
#define EN_INTERRUPT    asm("rim")
#define CHIP_STANBY     asm("halt")

//数码管显示内容定义
#define FALSE       0
#define TRUE        1
#define ERROR       2
#define ALARM       3
#define SET_PH      4


extern unsigned long delay_counter;
void DelayMs(u8 cnt);
#endif