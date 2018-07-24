#include "config.h"

#define KEY_ENABLE      0xCC
#define KEY_REFRESH     0xAA
#define KEY_ACCESS      0x55

u8 IWDG_Open_Flag;

/************************************************************
@
************************************************************/
void IWDG_Init(void)
{
    IWDG_KR = 0xCC; //启动IWDG
    IWDG_KR = 0x55; //解除 PR 及 RLR 的写保护
    IWDG_RLR = 0xFF; //看门狗计数器重装载数值      
    IWDG_PR = 0x06; //分频系数为256，最长超时时间为：1.02S
    IWDG_KR = 0xAA; //刷新IDDG，避免产生看门狗复位，同时恢复 PR 及 RLR 的写保护状态
}

/************************************************************
@
************************************************************/
void IWDG_Refresh(void)
{
    IWDG_KR = 0xAA;
}