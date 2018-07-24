#include "config.h"

u8 uart_tmpbuf[10];
u8 uart_rx_index;
u8 dataBuffer[10];

/********************************************************************
UART1_TX->PD5
UART1_RX->PD6
*********************************************************************/

/************************************************************
@
************************************************************/
#ifdef UART2_R_OR_vector
void Init_UART(void)
{
      uart_rx_index = 0;
      
      UART2_CR1=0x00;
      UART2_CR2=0x00;
      UART2_CR3=0x00;
      // 设置波特率，必须注意以下几点：
      // (1) 必须先写BRR2
      // (2) BRR1存放的是分频系数的第11位到第4位，
      // (3) BRR2存放的是分频系数的第15位到第12位，和第3位
      // 到第0位
      // 例如对于波特率位9600时，分频系数=2000000/9600=208
      // 对应的十六进制数为00D0，BBR1=0D,BBR2=00
      //buad rate = fSYS/UART_DIV,UART_DIV填入UART1_BRR2,UART1_BRR1
      
      //2M,9600,  0x00d0
//      UART1_BRR2=0x00;
//      UART1_BRR1=0x0d;
      
      //16M,9600, 16000000/9600 = 0x0683
      UART2_BRR2=0x03;
      UART2_BRR1=0x68;      
      //16M,115200, 16000000/115200 = 0x008B
//     UART2_BRR2=0x0B;
//     UART2_BRR1=0x08;    
      
      UART2_CR2=0x2c;//允许接收，发送，开接收中断
}
#else
void Init_UART(void)
{
      uart_rx_index = 0;
      
      UART1_CR1=0x00;
      UART1_CR2=0x00;
      UART1_CR3=0x00;
      // 设置波特率，必须注意以下几点：
      // (1) 必须先写BRR2
      // (2) BRR1存放的是分频系数的第11位到第4位，
      // (3) BRR2存放的是分频系数的第15位到第12位，和第3位
      // 到第0位
      // 例如对于波特率位9600时，分频系数=2000000/9600=208
      // 对应的十六进制数为00D0，BBR1=0D,BBR2=00
      //buad rate = fSYS/UART_DIV,UART_DIV填入UART1_BRR2,UART1_BRR1
      
      //2M,9600,  0x00d0
//      UART1_BRR2=0x00;
//      UART1_BRR1=0x0d;
      
      //16M,9600, 16000000/9600 = 0x0683
//      UART1_BRR2=0x03;
//      UART1_BRR1=0x68; 
      UART1_BRR2=0x0B;
      UART1_BRR1=0x08;  
      //16M,115200, 16000000/115200 = 0x008B
//     UART2_BRR2=0x0B;
//     UART2_BRR1=0x08;    
      
      UART1_CR2=0x2c;//允许接收，发送，开接收中断
}

#endif

/************************************************************
@
************************************************************/
void UART_sendbyte(unsigned char c)
{
#if (UART_DEG_EN == 1)  
  
#ifdef UART2_R_OR_vector
  while((UART2_SR & 0x80)==0x00);
  UART2_DR=c;
#else
  while((UART1_SR & 0x80)==0x00);
  UART1_DR=c;     
#endif
  
#endif
}
/************************************************************
@
************************************************************/
char putchar(char c)
{
    if (c == '\n')
    {
        UART_sendbyte(0x0d);
        UART_sendbyte(0x0a);
    }
    else
    {
        UART_sendbyte(c);
    }

    return (c);
}

/************************************************************
@
************************************************************/
void get_hex_data(u8 dat)
{
   u8 dat0;
   if(dat<0x0a)
   {
       dat0 = dat+'0';
   }
   else
   {
       dat0 = dat+'A'-10;
   }
   putchar(dat0);
}  
/************************************************************
@
************************************************************/
void printf_u8(u8 dat)
{
    putchar(' ');
    get_hex_data(dat >> 4);
    get_hex_data(dat & 0xf);
    putchar(' ');
}

/************************************************************
@
************************************************************/
void printf_u16(u16 dat)
{
    putchar(' ');
    get_hex_data(((u8 *)(&dat))[0] >> 4);
    get_hex_data(((u8 *)(&dat))[0] & 0xf);

    get_hex_data(((u8 *)(&dat))[1] >> 4);
    get_hex_data(((u8 *)(&dat))[1] & 0xf);
    putchar(' ');
}

/************************************************************
@
************************************************************/
void printf_dec_u8(u8 dat)
{
    u8 bai,shi,ge;
    bai = dat/100+'0';
    shi = (dat%100)/10+'0';
    ge = dat%10+'0';
    putchar(bai);
    putchar(shi);
    putchar(ge);
    putchar(' ');

}

/************************************************************
@
************************************************************/
void printf_dec_u16(u16 dat)
{
  u8 buf[5];
  u8 i;
  
//	buf[0] = dat/1000000000+'0';
//	buf[1] = (dat%1000000000)/100000000+'0';
//	buf[2] = (dat%100000000)/10000000+'0';
//	buf[3] = (dat%10000000)/1000000+'0';
//	buf[4] = (dat%1000000)/100000+'0';
  buf[0] = (dat%100000)/10000+'0';
  buf[1] = (dat%10000)/1000+'0';
  buf[2] = (dat%1000)/100+'0';
  buf[3] = (dat%100)/10+'0';
  buf[4] = dat%10+'0';
  for(i=0;i<5;i++)
  {
    putchar(buf[i]);
  }
  putchar(' ');

}

/************************************************************
@
************************************************************/
void printf_dec_u32(u32 dat)
{
  u8 buf[10];
  u8 i;
  
  buf[0] = dat/1000000000+'0';
  buf[1] = (dat%1000000000)/100000000+'0';
  buf[2] = (dat%100000000)/10000000+'0';
  buf[3] = (dat%10000000)/1000000+'0';
  buf[4] = (dat%1000000)/100000+'0';
  buf[5] = (dat%100000)/10000+'0';
  buf[6] = (dat%10000)/1000+'0';
  buf[7] = (dat%1000)/100+'0';
  buf[8] = (dat%100)/10+'0';
  buf[9] = dat%10+'0';
  for(i=0;i<10;i++)
  {
    putchar(buf[i]);
  }
  putchar(' ');

}

/************************************************************
@
************************************************************/
void deg_string(u8 * pd)
{
  while(*pd)
  {
    putchar(*pd);
    pd++;
  }
}


/************************************************************
@
************************************************************/
void UartSendBuffer(u8 * payload,u8 len)
{
  while(len--)
  {
    putchar(*payload);
    payload++;
  }
}


void UartInfoReceive(u8 UART_BUF)
{
  static u8 uartRXIndex = 0;
  u8 RecOneFrame;
//  u8 cs;
//  u8 i;

  RecOneFrame = 0;
  dataBuffer[uartRXIndex++] = UART_BUF;
  
  if(uartRXIndex &&(dataBuffer[0] != 'F'))
     uartRXIndex = 0;
  else if((uartRXIndex>1)&&(dataBuffer[1] != 'A'))
     uartRXIndex = 0;
  else if((uartRXIndex > 3)&&(uartRXIndex == 4))
  {
    RecOneFrame = 1;
  }
                  
  if(RecOneFrame)
  {
//    cs = 0;
//		i = 0;
//    for(i=0;i<uartRXIndex-1;i++)
//    {
//      cs -= dataBuffer[i];
//    }
    
//    if(cs != dataBuffer[uartRXIndex-1])  
//    {
//      deg_string("\ninv");
//      uartRXIndex = 0;
//      return;
//    }
    put_msg_lifo(UART_REV_ONE_FRAME);  
    uartRXIndex = 0;		
  }

}


