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
    IWDG_KR = 0xCC; //����IWDG
    IWDG_KR = 0x55; //��� PR �� RLR ��д����
    IWDG_RLR = 0xFF; //���Ź���������װ����ֵ      
    IWDG_PR = 0x06; //��Ƶϵ��Ϊ256�����ʱʱ��Ϊ��1.02S
    IWDG_KR = 0xAA; //ˢ��IDDG������������Ź���λ��ͬʱ�ָ� PR �� RLR ��д����״̬
}

/************************************************************
@
************************************************************/
void IWDG_Refresh(void)
{
    IWDG_KR = 0xAA;
}