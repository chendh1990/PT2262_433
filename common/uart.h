#ifndef __UART_H__
#define __UART_H__


#define UART_DEG_EN 1

#define MAX_UART_BUF  512+10
#define RX_CMD      0
#define RX_DATA     1

extern u8 rx_cmd_flag;
extern u8 dataBuffer[];


void printf_u8(u8 dat);
void Init_UART();
void UART_sendbyte(unsigned char c);
char putchar(char c);
void printf_u16(u16 dat);
void deg_string(u8 * pd);
void printf_dec_u8(u8 dat);

void printf_dec_u16(u16 dat);
void printf_dec_u32(u32 dat);
void UartSendBuffer(u8 * payload,u8 len);

void UartInfoReceive(u8 UART_BUF);

#endif