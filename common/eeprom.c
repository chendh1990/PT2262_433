
#include "config.h"

/***********************************************************************************

EEPROM:
从0X4000开始是EEPROM存储的地址，最后是OPTION BYTE的空间。具体位置视芯片具体容量而定。

FLASH:
从0X8000开始是用户程序区，开始0X8000~0X8080是中断向量地址，共128字节，每个向量占4字节，所以有32个向量。

DATA EEPROM操作：
FLASH_DUKR写入两个秘钥,解锁成功后，DULL会为1，这时可以对EEPROM区域进行操作。
操作完后要记得上锁，上锁步奏是向FLASH_IAPSR的DULL位清零。

选项字节OPTION BYTE操作：
和EEPROM操作差不多，但是要使得FLASH_CR2的OPT位为1，FLASH_NCR2的NOPT为0，才能写入选项字节。
*********************************************************************************************************/

/************************************************************************************************
普通EEPROM区读写
*********************************************************************************************************/
#define 	EEPROM_START_ADDR 	0X4000
#define 	EEPROM_MAX_SIZE 	512



static void ee_delay()
{
  u8 cnt = 200;
  while(cnt--);
}

u8 EEPROM_Unlock(void)
{
  u8 timeOut = 0;

  while((FLASH_IAPSR & 0x08) == 0)
  {
    FLASH_DUKR = 0xAE;
    FLASH_DUKR = 0x56;
    if(timeOut++ >= 30)
    {
      return 1;
    }
  }
 return 0;
}

u8 Flash_Unlock(void)
{
  u8 timeOut = 0;

  while((FLASH_IAPSR & 0x02) == 0)
  {
    FLASH_PUKR = 0x56;
    FLASH_PUKR = 0xAE;
    if(timeOut++ >= 30)
    {
      return 1;
    }
  }
 return 0;
}


void EEPROM_Lock(void)
{
	FLASH_IAPSR = 0X00;				    //Clear DUL
}


u8 EEPROM_WriteByte(u16 addr,u8 *buf,u16 num)
{
  unsigned char *EEPROM_Address;
  u16 i;
  u8 timeOut;
//  u8 old_data;
  
  for (i = 0; i < num; i++)
  {
    EEPROM_Address = (u8 *)(EEPROM_START_ADDR+addr);
    
  //  old_data = (*EEPROM_Address);
  //  if(buf[i] != old_data)              //数据不一样，才需要写入
    {
      (*EEPROM_Address) = buf[i];
      addr++;
      timeOut = 0;
      while((FLASH_IAPSR & 0x04) == 0) 	//EOP = 1，表示写入成功
      {
        ee_delay();
        if(timeOut++ >= 200)
        {
          return 2;
        }
      }
    }
  }
  
  return 0;
}


//注意写入需要解锁，读取不需要解锁。
void EEPROM_ReadByte(u16 addr,u8 *buf,u16 num)
{
  unsigned char *EEPROM_Address;
  u16 i;

  for (i = 0; i < num; i++)
  {
    EEPROM_Address = (u8 *)(EEPROM_START_ADDR+addr);
    buf[i] = (*EEPROM_Address);
    addr++;
  }
}

/************************************************************************************************
选项字节地址可从芯片规格书中的Option bytes章节获取
*********************************************************************************************************/
#define 	EEPROM_OPT_ROP_ADDR 	0X4800 	 		//写入0XAA可以进行FLASH保护
#define 	EEPROM_OPT_UBC_ADDR 	0X4801 
#define 	EEPROM_OPT_UBC2_ADDR 	0X4802 
#define 	EEPROM_OPT_AFR_ADDR 	0X4803 
#define 	EEPROM_OPT_AFR2_ADDR 	0X4804 
#define 	EEPROM_OPT_MIC_ADDR 	0X4805   		//这里可以使能LSI_EN
#define 	EEPROM_OPT_MIC2_ADDR 	0X4806 
#define 	EEPROM_OPT_CLK_ADDR 	0X4807 
#define 	EEPROM_OPT_CLK2_ADDR 	0X4808 
#define 	EEPROM_OPT_HSE_ADDR 	0X4809 
#define 	EEPROM_OPT_HSE2_ADDR 	0X480A 	
#define 	EEPROM_OPT_RES_ADDR 	0X480B 
#define 	EEPROM_OPT_RES2_ADDR 	0X480C 
#define 	EEPROM_OPT_RES3_ADDR 	0X480D 
#define 	EEPROM_OPT_RES4_ADDR 	0X480E 
#define 	EEPROM_OPT_BLD_ADDR 	0X487E 
#define 	EEPROM_OPT_BLD2_ADDR 	0X487F 


//注意写入需要解锁，读取不需要解锁。
void EEPROM_ReadOPTByte(u16 addr,u8 *buf,u8 num)
{
	unsigned char *EEPROM_Address;
	u8 i;
    
    for(i=0;i<num;i++)
    {
      EEPROM_Address = (u8 *)(addr+i);
      buf[i] = (*EEPROM_Address);
    }
}


u8 EEPROM_WriteOPTByte(u16 addr,u8 *buf,u8 num)
{
	unsigned char *EEPROM_Address;
	u8 timeOut;
    u8 i;
	
    
    //if(Flash_Unlock())      return 1;
    
	timeOut = 0;
	while(FLASH_CR2 != 0X80) 		    //等待OPT位为1
	{
		FLASH_CR2 = 0X80;
		if(timeOut++>50) return 2;
	}
	timeOut = 0;
	while((FLASH_NCR2 != 0X7F)) 		//等待NOPT位为0
	{
		FLASH_NCR2 = 0X7F;
		if(timeOut++>50) return 3;
	}
    
	if(EEPROM_Unlock()) return 4;
 
    for(i=0;i<num;i++)
    {
      EEPROM_Address = (u8 *)(addr+i);
      (*EEPROM_Address) = buf[i];
 
      timeOut = 0;
      while((FLASH_IAPSR & 0x04) == 0) 	//EOP = 1，表示写入成功	
      {
        ee_delay();
        if(timeOut++ >= 200)
        {
          return 5;
        }
      }  
    }
	EEPROM_Lock();
	
	timeOut = 0;
	while(FLASH_CR2 != 0x00) 			//等待OPT位为0
	{
		FLASH_CR2 = 0x00;
		if(timeOut++>50) return 6;
	}
	timeOut = 0;
	while(FLASH_NCR2 != 0XFF) 	        //等待NOPT位为1
	{
		FLASH_NCR2 = 0XFF;
		if(timeOut++>50) return 7;
	}
	
	return 0;
}
/*****************************************************************
错误说明：
1.设置ROP不成功
2.设置MISC不成功
3.设置OPT成功，并且写入标志成功
4.设置OPT成功，但是写入标志不成功
5.已经写入过了OPT，但是重启后读出的ROP不对
6.已经写入过了OPT，但是重启后读出的MISC不对
0.已经写入过了OPT，并且读出的OPT正确
综上所述:只有3，0是成功的结果
****************************************************************/
u8 SystemSetOPTByte(void)
{
	u8 ROP = 0XAA;
	u8 miscOPT = 0X08;  		    //使能LSI_EN
	u8 timeOut;
    u8 writeBuffer[5];
    u8 readBuffer[5];   
    u8 wrOptRes;
	
	EEPROM_ReadByte(0x0000,readBuffer,3);
    
	if((readBuffer[0] != 0X55) || (readBuffer[1] != 0Xaa) || (readBuffer[2] != 0Xa5))	//从没有设过OPT
	{
		timeOut = 0;
        writeBuffer[0] = ROP;
		while(1)
		{
            wrOptRes = EEPROM_WriteOPTByte(EEPROM_OPT_ROP_ADDR,writeBuffer,1);
			if(wrOptRes) return (50+wrOptRes);           
			EEPROM_ReadOPTByte(EEPROM_OPT_ROP_ADDR,readBuffer,1);
            if(readBuffer[0] == ROP) break;
			if(timeOut++ >= 3)
			{
				return 1;
			}
		}	
		timeOut = 0;
        writeBuffer[0] = miscOPT;
        writeBuffer[1] =~miscOPT;        
		while(1)
		{
            wrOptRes = EEPROM_WriteOPTByte(EEPROM_OPT_MIC_ADDR,writeBuffer,2);
			if(wrOptRes) return (100+wrOptRes);
			EEPROM_ReadOPTByte(EEPROM_OPT_MIC_ADDR,readBuffer,2);
            if(readBuffer[0] == miscOPT) break;
			if(timeOut++ >= 3)
			{
				return 2;
			}
		}	
		writeBuffer[0] = 0X55; writeBuffer[1] = 0XAA; writeBuffer[2] = 0XA5;				//写入标志
        EEPROM_Unlock();
        wrOptRes = EEPROM_WriteByte(0X0000,writeBuffer,3);
		if(wrOptRes) return (150+wrOptRes);	 						
        EEPROM_Lock();
		EEPROM_ReadByte(0x0000,readBuffer,3);
		if((readBuffer[0] == 0X55) && (readBuffer[1] == 0Xaa) && (readBuffer[2] == 0Xa5))   //写入标志成功
		{
			return 3;
		}
		else
		{
			return 4;
		}
	}
	else
	{
      EEPROM_ReadOPTByte(EEPROM_OPT_ROP_ADDR,readBuffer,1);
      if(readBuffer[0] != ROP)
      {
          return 5;
      }	  
      EEPROM_ReadOPTByte(EEPROM_OPT_MIC_ADDR,readBuffer,2);
      if(readBuffer[0] != miscOPT)
      {
          return 6;
      }    
	}  
    return 0;
}


