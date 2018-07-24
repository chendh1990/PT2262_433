/*
           段式屏驱动芯片1621系列底层驱动driver.c      
*/
#include "config.h"

#define LCD_BUFFER_SIZE         32


u8 lcdBuffer[LCD_BUFFER_SIZE];

#ifdef PCB_M9 /************************************************/

#define CS1     PB_ODR_ODR5 = 1
#define CS0     PB_ODR_ODR5 = 0

#define WR1     PB_ODR_ODR4 = 1
#define WR0     PB_ODR_ODR4 = 0

#define DAT1    PC_ODR_ODR3 = 1
#define DAT0    PC_ODR_ODR3 = 0

void LCD_GPIOInit()
{
  //初始化SPI端口CS,WR,DATA
  PB_DDR |= (BIT(4)|BIT(5));             //PD4,PD5,PD6为输出
  PB_CR1 |= (BIT(4)|BIT(5));             //PD4,PD5,PD6推挽输出        
  PB_CR2 = 0X00;   
  
  PC_DDR |= (BIT(3));             //PD4,PD5,PD6为输出
  PC_CR1 |= (BIT(3));             //PD4,PD5,PD6推挽输出        
  PC_CR2 = 0X00;  
}

#else  /************************************************/

#define CS1     PD_ODR_ODR4 = 1
#define CS0     PD_ODR_ODR4 = 0

#define WR1     PD_ODR_ODR5 = 1
#define WR0     PD_ODR_ODR5 = 0

#define DAT1    PD_ODR_ODR6 = 1
#define DAT0    PD_ODR_ODR6 = 0

void LCD_GPIOInit()
{
  //初始化SPI端口CS,WR,DATA
  PD_DDR |= (BIT(4)|BIT(5)|BIT(6));             //PD4,PD5,PD6为输出
  PD_CR1 |= (BIT(4)|BIT(5)|BIT(6));             //PD4,PD5,PD6推挽输出        
  PD_CR2 = 0X00;   
}

#endif  /************************************************/
/**********************************************************************
                             延时函数
**********************************************************************/
void Delay0(void)
{
  unsigned char i,j;
  for(i=0;i<1;i++);
    for(j=0;j<10;j++);
}
/**********************************************************************
    发送命令/发送命令数据,高位在前
    命令: 100(0x80)   COMMOND
          101(0Xa0)   WRITE
    eg: SendBit_1621(0x80,3)  发送写”命令“命令
    eg: SendBit_1621(0xa0,3)  发送写“数据”命令
    由时序分析可得发送命令与发送命令数据时的顺序为 bit8.。。bit7
**********************************************************************/
void SendBit_1621(unsigned char data,unsigned char cnt) //data的高cnt位写入HT1621，高位在前
{
  unsigned char i;
  for(i =0; i <cnt; i ++)
  {
    if((data&0x80)==0) 
    DAT0;
    else 
    DAT1;
    WR0;
    Delay0();
    Delay0();
    WR1;
    data<<=1;
    Delay0();
    Delay0();
  }
}
/**********************************************************************
                发送RAM数据,低位在前
  由时序图可知: 发送RAM数据时在RAM里的储存的顺序为bit0.。bit4 
                也就是先发的数据储存在低地址处
**********************************************************************/
void SendDataBit_1621(unsigned char data,unsigned char cnt) //data 的低cnt 位写入HT1621，低位在前
{
  unsigned char i;
  for(i =0; i <cnt; i ++)
  {
    if((data&0x01)==0) DAT0;
    else DAT1;
    WR0;
    Delay0();
    Delay0();
    WR1;
    data>>=1;
    Delay0();
    Delay0();
  }
}
///**********************************************************************
//               供应用层调用的函数:指定连续的两个地址写入8位数据，低位在前
//**********************************************************************/
//void Write_1621_8bit(unsigned char addr,unsigned char data)
//{
//   CS0;
//   SendBit_1621(0xa0,3);        //写入标志码"101"
//   SendBit_1621(addr<<2,6);     //写入6 位addr
//   SendDataBit_1621(data,8);    //写入data，高位在前
//   CS1;
//}
///**********************************************************************
//               供应用层调用的函数:地址写入4位数据低位在前
//**********************************************************************/
//void Write_1621_4bit(unsigned char addr,unsigned char data)
//{
//   CS0;
//   SendBit_1621(0xa0,3);        //写入标志码"101"
//   SendBit_1621(addr<<2,6);     //写入6 位addr
//   SendDataBit_1621(data,4);    //写入data，高位在前
//   CS1;
//}
/**********************************************************************
              初始化函数里边调用该函数，设置
**********************************************************************/
void SendCmd(unsigned char command)
{
   CS0;
   SendBit_1621(0x80,3); //写入标志码"100"
   SendBit_1621(command,9); //写入9 位数据,其中前8 位为command 命令,最后1 位任意
   CS1;
}

/**********************************************************************
              填充一个点
**********************************************************************/
void LcdFillUnit(u16 mask,u8 flag)
{
  u8 addr;
  u8 dat;
  
  dat = mask&0x000f;
  addr = (mask>>4)&0x00ff;
  
  
  if(flag == 0)
  {
    lcdBuffer[addr] &=~dat;
  }
  else
  {
    lcdBuffer[addr] |= dat;
  }
}


/**********************************************************************
              显示数据0~9
**********************************************************************/
void LcdFillNum(u8 dat,u16 SEG_A,u16 SEG_B,u16 SEG_C,u16 SEG_D,u16 SEG_E,u16 SEG_F,u16 SEG_G)
{

  switch(dat)
  {
    case 0://ABDEF
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,1);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,0);
      break;
      
    case 1://BC
      LcdFillUnit(SEG_A,0);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,0);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,0);LcdFillUnit(SEG_G,0);
      break;  
      
     case 2://ABDEG
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,0);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,1);LcdFillUnit(SEG_F,0);LcdFillUnit(SEG_G,1);
      break; 
      
      case 3://ABCDG
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,0);LcdFillUnit(SEG_G,1);
      break;  
      
      case 4://BCFG
      LcdFillUnit(SEG_A,0);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,0);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,1);
      break;   
      
      case 5://AFGCD
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,0);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,1);
      break;   
      
      case 6://ACDEFG
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,0);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,1);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,1);
      break;  
      
      case 7://ABC
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,0);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,0);LcdFillUnit(SEG_G,0);
      break;      
      
      case 8://ABCDEFG
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,1);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,1);
      break;  
      
      case 9://ABCDFG
      LcdFillUnit(SEG_A,1);LcdFillUnit(SEG_B,1);LcdFillUnit(SEG_C,1);LcdFillUnit(SEG_D,1);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,1);LcdFillUnit(SEG_G,1);
      break;     
      
    default:  
      LcdFillUnit(SEG_A,0);LcdFillUnit(SEG_B,0);LcdFillUnit(SEG_C,0);LcdFillUnit(SEG_D,0);
      LcdFillUnit(SEG_E,0);LcdFillUnit(SEG_F,0);LcdFillUnit(SEG_G,0);      
      break;
      
  }
}

/**********************************************************************
              显示时间
**********************************************************************/
void LcdDispTime(u16 dat)
{
  u8 bai,shi,ge;
  
  
  bai = (dat%1000)/100;
  shi = (dat%100)/10;
  ge = (dat%10)/1;

  
  LcdFillNum(bai,TIME_BAI_SEG_A,TIME_BAI_SEG_B,TIME_BAI_SEG_C,TIME_BAI_SEG_D,TIME_BAI_SEG_E,TIME_BAI_SEG_F,TIME_BAI_SEG_G);
  LcdFillNum(shi,TIME_SHI_SEG_A,TIME_SHI_SEG_B,TIME_SHI_SEG_C,TIME_SHI_SEG_D,TIME_SHI_SEG_E,TIME_SHI_SEG_F,TIME_SHI_SEG_G);
  LcdFillNum(ge,TIME_GE_SEG_A,TIME_GE_SEG_B,TIME_GE_SEG_C,TIME_GE_SEG_D,TIME_GE_SEG_E,TIME_GE_SEG_F,TIME_GE_SEG_G);
}

/**********************************************************************
              显示OFF
**********************************************************************/
void LcdDispOff(void)
{
  LcdFillUnit(TIME_BAI_SEG_A,1);LcdFillUnit(TIME_BAI_SEG_B,1);LcdFillUnit(TIME_BAI_SEG_C,1);LcdFillUnit(TIME_BAI_SEG_D,1);
  LcdFillUnit(TIME_BAI_SEG_E,1);LcdFillUnit(TIME_BAI_SEG_F,1);LcdFillUnit(TIME_BAI_SEG_G,0);

  LcdFillUnit(TIME_SHI_SEG_A,1);LcdFillUnit(TIME_SHI_SEG_B,0);LcdFillUnit(TIME_SHI_SEG_C,0);LcdFillUnit(TIME_SHI_SEG_D,0);
  LcdFillUnit(TIME_SHI_SEG_E,1);LcdFillUnit(TIME_SHI_SEG_F,1);LcdFillUnit(TIME_SHI_SEG_G,1);
  
  LcdFillUnit(TIME_GE_SEG_A,1);LcdFillUnit(TIME_GE_SEG_B,0);LcdFillUnit(TIME_GE_SEG_C,0);LcdFillUnit(TIME_GE_SEG_D,0);
  LcdFillUnit(TIME_GE_SEG_E,1);LcdFillUnit(TIME_GE_SEG_F,1);LcdFillUnit(TIME_GE_SEG_G,1);
}

/**********************************************************************
             显示百分比
**********************************************************************/
void LcdDispPercent(u8 dat)
{
  u8 shi,ge;
  
  
  if(dat >= 100)
  {
    dat = 40-(dat-100)/2;
  }
  else if(dat>= 80)
  {
    dat = 50-(dat-80)/2;
  }
  else if(dat>= 60)
  {
    dat = 60-(dat-60)/2;
  }  
  else if(dat>= 40)
  {
    dat = 90-(dat-40)/2*3;
  }  
  
  shi = (dat%100)/10;
  ge = (dat%10)/1;
  
  LcdFillNum(shi,PERCENT_SHI_SEG_A,PERCENT_SHI_SEG_B,PERCENT_SHI_SEG_C,\
                PERCENT_SHI_SEG_D,PERCENT_SHI_SEG_E,PERCENT_SHI_SEG_F,PERCENT_SHI_SEG_G);
  LcdFillNum(ge,PERCENT_GE_SEG_A,PERCENT_GE_SEG_B,PERCENT_GE_SEG_C,\
                PERCENT_GE_SEG_D,PERCENT_GE_SEG_E,PERCENT_GE_SEG_F,PERCENT_GE_SEG_G);
}

/**********************************************************************
              显示容量
**********************************************************************/
void LcdDispCAP(u8 dat)
{
  u8 shi,ge;
  
  shi = (dat%100)/10;
  ge = (dat%10)/1;
  
  LcdFillNum(shi,CAP_SHI_SEG_A,CAP_SHI_SEG_B,CAP_SHI_SEG_C,\
                CAP_SHI_SEG_D,CAP_SHI_SEG_E,CAP_SHI_SEG_F,CAP_SHI_SEG_G);
  LcdFillNum(ge,CAP_GE_SEG_A,CAP_GE_SEG_B,CAP_GE_SEG_C,\
                CAP_GE_SEG_D,CAP_GE_SEG_E,CAP_GE_SEG_F,CAP_GE_SEG_G);
}


/**********************************************************************
             显示百分比
**********************************************************************/
void LCD_DispFlowAndPercent(u8 dat)
{
  u8 shi,ge;
  float flow;
  float sub = 10.0;
  
  LcdDispSignal(dat);  
  LcdDispCAP(dat);
  LcdDispCAP_Icon(1);
  LcdDispCAPDot(1);
  LcdDispPercentSymbol(1);
  
  flow = dat/sub;
  
  if(flow == 2.0)   dat = 91;
  if(flow == 2.1)   dat = 69;
  if(flow == 2.2)   dat = 70;
  if(flow == 2.3)   dat = 67;
  if(flow == 2.4)   dat = 68;
  if(flow == 2.5)   dat = 65;
  if(flow == 2.6)   dat = 66;
  if(flow == 2.7)   dat = 63;
  if(flow == 2.8)   dat = 64;
  if(flow == 2.9)   dat = 61;
  if(flow == 3.0)   dat = 61;
  if(flow == 3.1)   dat = 59;
  if(flow == 3.2)   dat = 60;
  if(flow == 3.3)   dat = 57;
  if(flow == 3.4)   dat = 56;
  if(flow == 3.5)   dat = 55;
  if(flow == 3.6)   dat = 56;
  if(flow == 3.7)   dat = 53;
  if(flow == 3.8)   dat = 52;
  if(flow == 3.9)   dat = 51;
  if(flow == 4.0)   dat = 52;
  if(flow == 4.1)   dat = 51;
  if(flow == 4.2)   dat = 50;
  if(flow == 4.3)   dat = 47;
  if(flow == 4.4)   dat = 48;
  if(flow == 4.5)   dat = 45;
  if(flow == 4.6)   dat = 46;
  if(flow == 4.7)   dat = 45;
  if(flow == 4.8)   dat = 42;
  if(flow == 4.9)   dat = 43;  
  if(flow == 5.0)   dat = 41;
  if(flow == 5.1)   dat = 41;
  if(flow == 5.2)   dat = 38;
  if(flow == 5.3)   dat = 37;
  if(flow == 5.4)   dat = 38;
  if(flow == 5.5)   dat = 35;
  if(flow == 5.6)   dat = 36;
  if(flow == 5.7)   dat = 33;
  if(flow == 5.8)   dat = 34;
  if(flow == 5.9)   dat = 33;  
  if(flow == 6.0)   dat = 30;  
  
  shi = (dat%100)/10;
  ge = (dat%10)/1;
  
  LcdFillNum(shi,PERCENT_SHI_SEG_A,PERCENT_SHI_SEG_B,PERCENT_SHI_SEG_C,\
                PERCENT_SHI_SEG_D,PERCENT_SHI_SEG_E,PERCENT_SHI_SEG_F,PERCENT_SHI_SEG_G);
  LcdFillNum(ge,PERCENT_GE_SEG_A,PERCENT_GE_SEG_B,PERCENT_GE_SEG_C,\
                PERCENT_GE_SEG_D,PERCENT_GE_SEG_E,PERCENT_GE_SEG_F,PERCENT_GE_SEG_G);
  
  
  
}

/**********************************************************************
              显示升单位L
**********************************************************************/
void LcdDispCAP_Icon(u8 flag)
{
  if(flag&0x01)
  {
      LcdFillUnit(CAP_UNIT_SEG_A,0);LcdFillUnit(CAP_UNIT_SEG_B,0);LcdFillUnit(CAP_UNIT_SEG_C,0);LcdFillUnit(CAP_UNIT_SEG_D,1);
      LcdFillUnit(CAP_UNIT_SEG_E,1);LcdFillUnit(CAP_UNIT_SEG_F,1);LcdFillUnit(CAP_UNIT_SEG_G,0); 
  }
  else
  {     
      LcdFillUnit(CAP_UNIT_SEG_A,0);LcdFillUnit(CAP_UNIT_SEG_B,0);LcdFillUnit(CAP_UNIT_SEG_C,0);LcdFillUnit(CAP_UNIT_SEG_D,0);
      LcdFillUnit(CAP_UNIT_SEG_E,0);LcdFillUnit(CAP_UNIT_SEG_F,0);LcdFillUnit(CAP_UNIT_SEG_G,0);
  }
}

/**********************************************************************
              显示格子
**********************************************************************/
void LcdDispSignal(u8 dat)
{
  LcdFillUnit(CAP_SIGNAL_S1,0);
  LcdFillUnit(CAP_SIGNAL_S2,0);
  LcdFillUnit(CAP_SIGNAL_S3,0);
  LcdFillUnit(CAP_SIGNAL_S4,0);
  LcdFillUnit(CAP_SIGNAL_S5,0);
  LcdFillUnit(CAP_SIGNAL_S6,0);
  
//  dat = dat%10;
  
  if(dat >= 60)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    
  }
  else if(dat >= 50)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    LcdFillUnit(CAP_SIGNAL_S2,1);
  }
  else if(dat >= 40)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    LcdFillUnit(CAP_SIGNAL_S2,1);
    LcdFillUnit(CAP_SIGNAL_S3,1);
  }
  else if(dat >= 30)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    LcdFillUnit(CAP_SIGNAL_S2,1);
    LcdFillUnit(CAP_SIGNAL_S3,1);
    LcdFillUnit(CAP_SIGNAL_S4,1);
  }
   else if(dat >= 20)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    LcdFillUnit(CAP_SIGNAL_S2,1);
    LcdFillUnit(CAP_SIGNAL_S3,1);
    LcdFillUnit(CAP_SIGNAL_S4,1);
    LcdFillUnit(CAP_SIGNAL_S5,1);
  }
  else if(dat == 70)
  {
    LcdFillUnit(CAP_SIGNAL_S1,1);
    LcdFillUnit(CAP_SIGNAL_S2,1);
    LcdFillUnit(CAP_SIGNAL_S3,1);
    LcdFillUnit(CAP_SIGNAL_S4,1);
    LcdFillUnit(CAP_SIGNAL_S5,1);
    LcdFillUnit(CAP_SIGNAL_S6,1);
  }
}

/**********************************************************************
              显示百分号%
**********************************************************************/
void LcdDispPercentSymbol(u8 flag)
{
  if(flag&0x01)
  {
    LcdFillUnit(CAP_PERCENT_SYMBOL,1);
  }
  else
  {
    LcdFillUnit(CAP_PERCENT_SYMBOL,0);
  }

}

/**********************************************************************
              显示小数点
**********************************************************************/
void LcdDispCAPDot(u8 flag)
{
  if(flag&0x01)
  {
    LcdFillUnit(CAP_DOT_SEG,1);
  }
  else
  {
    LcdFillUnit(CAP_DOT_SEG,0);
  }

}


/**********************************************************************
             清屏函数
**********************************************************************/
void Lcd1621_Update_Display()
{
   unsigned char i;
   CS0;
   SendBit_1621(0xa0,3);                //写入标志码"101"
   SendBit_1621(0X00,6);                //写入6 位addr
  for(i =0; i <LCD_BUFFER_SIZE; i++)    //连续写入数据
  {
   SendDataBit_1621(lcdBuffer[i],4);
   Delay0();
  }
  CS1;
}

/**********************************************************************
              填满buffer为0XFF
**********************************************************************/
void Lcd1621_DisplayAll()
{
  memset(lcdBuffer,0XFF,LCD_BUFFER_SIZE);
}

/**********************************************************************
              填满buffer为0X00
**********************************************************************/
void Lcd1621_DisplayClear()
{
  memset(lcdBuffer,0X00,LCD_BUFFER_SIZE);
}

/**********************************************************************
              关闭1621，节省功耗
**********************************************************************/
void Lcd1621_Shut(void)
{
  SendCmd(SYSDIS);               //打开系统振荡器
  SendCmd(LCDOFF);      
}

/**********************************************************************
              启动1621，进行显示
**********************************************************************/
void Lcd1621_On(void)
{
  SendCmd(BIAS);                //设置偏压和占空比
  SendCmd(SYSEN);               //打开系统振荡器
  SendCmd(RC256);               //设置偏压和占空比
  SendCmd(WDTDIS);              //打开系统振荡器
  SendCmd(TIMERDIS);            //打开LCD 偏压发生器
  SendCmd(LCDON);               //打开LCD 偏压发生器
}

/**********************************************************************
                  初始化函数
**********************************************************************/
void LcdInit(void)
{
  LCD_GPIOInit();
  
  Lcd1621_On();
}

/**********************************************************************
                            LCD测试函数
**********************************************************************/
void LcdTest(void)
{
  u8 i;
  
 //初始化SPI端口CS,WR,DATA
  PD_DDR |= (BIT(4)|BIT(5)|BIT(6));             //PD4,PD5,PD6为输出
  PD_CR1 |= (BIT(4)|BIT(5)|BIT(6));             //PD4,PD5,PD6推挽输出        
  PD_CR2 = 0X00;   
  
 
  DelayMs(10);
  Lcd1621_On();
  
  
  while(GetMsg() != KEY_PWR);
  Lcd1621_DisplayAll();
  Lcd1621_Update_Display();  
  
  while(GetMsg() != KEY_PWR);
  Lcd1621_DisplayClear();

  
  i = 0;
  while(1)
  {
    LcdDispPercent(i);
    LcdDispCAP(i);
    LcdDispTime(i);
    LcdDispCAP_Icon(i);
    LcdDispSignal(i);
    LcdDispPercentSymbol(i);
    Lcd1621_Update_Display(); 
    
    i++;
    DelayMs(30);

  
  }
 
}


