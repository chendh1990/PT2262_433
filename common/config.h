#ifndef __CONFIG_H__
#define __CONFIG_H__

/*********定义是哪个PCB**********************************/
#define PCB_M9


#ifndef NULL
#define NULL ((void *) 0L)
#endif

#define TRUE    1
#define FALSE   0

#define u8 unsigned char
#define u16 unsigned int
#define u32 unsigned long

#define s8 signed char
#define s16 signed int
#define s32 signed long

#define bit bool
#define BOOL bool

#define BIT(x) ((u8)(1<<x))

//system
#include "iostm8s003f3.h"
#include "stdbool.h"
#include "clock.h"
#include "uart.h"
#include "msg2.h"
#include "idle.h"
#include "msg.h"
#include "key.h"
#include "isr.h"
#include "wdt.h"
#include "string.h"
#include "MyString.h"
#include "eeprom.h"
#include "adc.h"
#include "timer_pwm.h"
#include "timer4.h"
#include "timer2.h"
#include "timer1.h"
#include "main.h"
//M9 remote工程应用
#include "1621.h"
#include "RFOOK.h"
#include "PT2622.h"



#ifdef PCB_M9
#include "RemoteLcd.h"
#else
#include "OL_LCD.h"
#endif


#endif



