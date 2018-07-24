#ifndef _1621_DRIVER_H
#define _1621_DRIVER_H

/**********************************************************************
                           ģʽ������صĺ�
**********************************************************************/
#define BIAS            0x29
#define SYSDIS          0x00            //ϵͳʹ��
#define SYSEN           0x01            //ϵͳʹ��
#define LCDOFF          0x02            //LCD��
#define LCDON           0x03            //LCD��
#define RC256           0X1             /*ʹ���ڲ�256KRC ����*/
#define WDTDIS          0X06            /*�ر�WDT*/
#define TIMERDIS        0X04            /*�ر�ʱ�����*/
/**********************************************************************
                           ��غ���
**********************************************************************/
void LcdInit(void);    //��ʼ��
void WriteAll_1621(u8 dat);  //����
void Write_1621_8bit(unsigned char addr,unsigned char data); //д8bit����
void Write_1621_4bit(unsigned char addr,unsigned char data);//д4bit����



void Lcd1621_DisplayClear();
void Lcd1621_DisplayAll();
void Lcd1621_Update_Display();
void Lcd1621_Shut(void);
void Lcd1621_On(void);



#endif


