#ifndef _1621_DRIVER_H
#define _1621_DRIVER_H

/**********************************************************************
                           模式设置相关的宏
**********************************************************************/
#define BIAS            0x29
#define SYSDIS          0x00            //系统使能
#define SYSEN           0x01            //系统使能
#define LCDOFF          0x02            //LCD关
#define LCDON           0x03            //LCD开
#define RC256           0X1             /*使用内部256KRC 振荡器*/
#define WDTDIS          0X06            /*关闭WDT*/
#define TIMERDIS        0X04            /*关闭时基输出*/
/**********************************************************************
                           相关函数
**********************************************************************/
void LcdInit(void);    //初始化
void WriteAll_1621(u8 dat);  //清屏
void Write_1621_8bit(unsigned char addr,unsigned char data); //写8bit数据
void Write_1621_4bit(unsigned char addr,unsigned char data);//写4bit数据



void Lcd1621_DisplayClear();
void Lcd1621_DisplayAll();
void Lcd1621_Update_Display();
void Lcd1621_Shut(void);
void Lcd1621_On(void);



#endif


