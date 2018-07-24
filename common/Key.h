/******************************************************************
KEY.H  file
作者：
建立日期: 
修改日期: 
版本：V1.1
版权所有，盗版必究。
Copyright(C) 
All rights reserved            
*******************************************************************/

#ifndef __KEY_H__
#define __KEY_H__


#define KEY_SCAN_TIMES		(2)  //按键防抖的扫描次数
#define KEY_SHORT_TIMES		(5)
#define KEY_LONG_TIMES		(0x80)	//长按键的次数
#define KEY_HOLD_TIMES          (0x20)//连按的频率次数

#define NO_KEY                  0xff
							 
#define KEY_LONG		0x10
#define KEY_HOLD		0x20
#define KEY_SHORT_UP            0x30 
#define KEY_LONG_UP             0x40

#define KEY_MEM			0x01
#define KEY_TIME		0x02
#define KEY_PWR			0x04
#define KEY_MOD			0x08


#define PR_MEM			KEY_MEM
#define PS_MEM			(KEY_MEM|KEY_SHORT_UP)
#define PU_MEM			(KEY_MEM|KEY_LONG_UP)
#define PL_MEM			(KEY_MEM|KEY_LONG)
#define PH_MEM			(KEY_MEM|KEY_HOLD)

#define PR_TIME			KEY_TIME
#define PS_TIME			(KEY_TIME|KEY_SHORT_UP)
#define PU_TIME			(KEY_TIME|KEY_LONG_UP)
#define PL_TIME			(KEY_TIME|KEY_LONG)
#define PH_TIME			(KEY_TIME|KEY_HOLD)

#define PR_PWR			KEY_PWR
#define PS_PWR			(KEY_PWR|KEY_SHORT_UP)
#define PU_PWR			(KEY_PWR|KEY_LONG_UP)
#define PL_PWR			(KEY_PWR|KEY_LONG)
#define PH_PWR			(KEY_PWR|KEY_HOLD)

#define PR_MOD			KEY_MOD
#define PS_MOD			(KEY_MOD|KEY_SHORT_UP)
#define PU_MOD			(KEY_MOD|KEY_LONG_UP)
#define PL_MOD			(KEY_MOD|KEY_LONG)
#define PH_MOD			(KEY_MOD|KEY_HOLD)


#define KEY_TIME_INPUT              PA_IDR_IDR3                  //2
#define KEY_PWR_INPUT               PB_IDR_IDR5                  //1
#define KEY_MEM_INPUT               PB_IDR_IDR4                 //0

#define RF_INPUT          PA_IDR_IDR2
#define ZERO_INPUT        PA_IDR_IDR1


#define BEEP_PORT       PD_ODR_ODR4
#define LED3_PORT       PD_ODR_ODR2
#define LED2_PORT       PC_ODR_ODR7
#define LED1_PORT       PC_ODR_ODR6
#define JK3_PORT       PC_ODR_ODR5
#define JK2_PORT       PC_ODR_ODR4
#define JK1_PORT       PC_ODR_ODR3




void KeyInit();
void KeyScan_jxh(void);

#endif
