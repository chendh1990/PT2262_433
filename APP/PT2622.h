#ifndef __PT2622_H__
#define __PT2622_H__

#define D_IR_sample 1

#define D_IR_SYNC_MAX		(12000/D_IR_sample)	//SYNC max time ////////////单位us 例如这里是12000us
#define D_IR_SYNC_MIN		(8000 /D_IR_sample)	//SYNC min time
#define D_IR_SYNC_DIVIDE	(9500/D_IR_sample)	//decide data 0 or 1

#define D_IR_DATA_MAX		(1300 /D_IR_sample)	//data max time
#define D_IR_DATA_MIN		(150  /D_IR_sample)//(300  /D_IR_sample)	//data min time

#define D_IR_SUM_MAX	        (1700 /D_IR_sample)
#define D_IR_SUM_MIN	        (1000 /D_IR_sample)

#define D_IR_BIT_NUMBER		48					//bit number

union RF_DataForm
{
  u32 rf_data;
  u8 buf[4];
};

//////////////////////////////////////////////////////////////
#define RF_KEY_MAX              10              //一个灯可以学习的按键数目         

#define EE_IDX_ADDR             512             //记忆码个数存储地址，用于信息存放的累加        
#define EE_USER_ID_ADDR         600             //STM8F003的EEPROM大小为640字节
#define EE_USER_ID              0XA5       

///////////////////////////////////////////////////////
#define RF_PAIR_TIMEOUT         20
#define RF_UP_CNT               300000/TIMER_INT_US    //300ms       



#define EE_RF_SIZE      sizeof(EE_Info)

struct __EE_INFO_
{
  u32 k0_tg_cmp[RF_KEY_MAX];
  u32 k0_on_cmp[RF_KEY_MAX];
  u32 k0_off_cmp[RF_KEY_MAX];
  
  u32 k1_tg_cmp[RF_KEY_MAX];
  u32 k1_on_cmp[RF_KEY_MAX];
  u32 k1_off_cmp[RF_KEY_MAX];
  
  u32 k2_tg_cmp[RF_KEY_MAX];
  u32 k2_on_cmp[RF_KEY_MAX];
  u32 k2_off_cmp[RF_KEY_MAX];
};


extern struct __EE_INFO_ EE_Info;


union _RF_INFO_
{
   struct __EE_INFO_ stru;
  u8 ee_buf[EE_RF_SIZE];
};

extern union _RF_INFO_ RF_Info;



#define EE_RF_IDX_SIZE      sizeof(EE_RF_Idx)

struct __EE_RF_IDX_
{
  u8 idx[9];
};

extern struct __EE_RF_IDX_ EE_RF_Idx;



void PT2262_RX(void);
void KEY_Study(u8 key);
void EE_ReadRFMask(void);
void RFKeyHandle(void);


#endif