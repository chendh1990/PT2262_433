#include "config.h"


/************************************************************
@
************************************************************/
void CLK_LSI(void)
{
  CLK_SWCR |= 0x02;                             /* ʹ��ת�� */        
  CLK_SWR   = 0xD2;                             /* ʱ��Դѡ�� ѡ��LSE*/
  while (!(CLK_SWCR & 0x08));                   /* �ȴ�ֱ��ת����� */        
  CLK_CKDIVR = 0;
  CLK_ICKR &= ~BIT(0);
}


/************************************************************
@
************************************************************/
void CLK_HSI(void)
{
  CLK_SWCR |= 0x02;                           /* ʹ��ת�� */        
  CLK_SWR   = 0xE1;                      /* ʱ��Դѡ�� ѡ��HSE*/
  while (!(CLK_SWCR & 0x08));                /* �ȴ�ֱ��ת����� */        
  CLK_CKDIVR = 0;
  CLK_ICKR &= ~BIT(3);
}

/************************************************************
@
************************************************************/
void clock_init()
{
	//�����ڲ����پ������޷�Ƶ16MHz
	CLK_ICKR|=0x01;                  //�����ڲ�HSI
	while(!(CLK_ICKR&0x02));        //HSI׼������
	CLK_SWR=0xe1;                   //HSIΪ��ʱ��Դ
	CLK_CKDIVR=0x00;                //HSI����Ƶ
        
        
//	for(i=0;i<10;i++)    //��˸LED
//	{
//		LED_PORT^=0x20;
//		delay_ms(500);
//	}
//	//�����ڲ����پ�����8��Ƶ(�ڲ�ʼ�շ�Ƶ)2MHz
//	CLK_CKDIVR=0x18;   //HSI8��Ƶ��2M����λ���Ĭ��ֵ
//	for(i=0;i<10;i++)   //��˸LED
//	{
//		LED_PORT^=0x20;
//		delay_ms(500);
//	}
        
        
//  //�����ڲ����پ������޷�Ƶ16MHz
//				
//          CLK_SWCR|=0x02; //�����л�
//          CLK_ICKR|=0x01;      //�����ڲ�HSI
//          while(!(CLK_ICKR&0x02));//HSI׼������
//          CLK_SWR=0xe1;        //HSIΪ��ʱ��Դ
//          while((CLK_SWCR & 0x01)==0x01);//�ȴ��л����
//          CLK_CKDIVR=0x00;     //HSI����Ƶ
//          CLK_SWCR&=(~0x02); //�ر��л�
//                
//          for(i=0;i<20;i++)
//          {
//              LED_PORT^=0x20;
//              delay_ms(500);
//          }
//          LED_PORT|=0x20;//Ϩ��LED������
//          delay_ms(500);
//          delay_ms(500);
//          delay_ms(500);
//          delay_ms(500);
//       //�����ڲ����پ�����8��Ƶ(�ڲ�ʼ�շ�Ƶ)2MHz
//        CLK_CKDIVR=0x18;
//        for(i=0;i<20;i++)
//        {
//		LED_PORT^=0x20;
//		delay_ms(500);
//	}
//	LED_PORT|=0x20;//Ϩ��LED������
//	delay_ms(500);
//	delay_ms(500);
//	//�����ڲ����پ������޷�Ƶ
//			  
//        CLK_SWCR|=0x02; //�����л�
//        CLK_ICKR|=0x08; //����LSI
//	while(!(CLK_ICKR&0x10));//HSI׼������
//	CLK_SWR=0xd2;   //LSRΪ��ʱ��Դ
//        while((CLK_SWCR & 0x01)==0x01);//�ȴ��л����
//        CLK_CKDIVR=0x00;   //LSI����Ƶ
//        CLK_SWCR&=(~0x02); //�ر��л�
//        for(i=0;i<20;i++)
//        {
//		LED_PORT^=0x20;
//		delay_ms(500);
//        }
//	LED_PORT|=0x20;//Ϩ��LED������
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//	delay_ms(500);
//		
//       //�����ⲿ���پ�����16��Ƶ500KHz
//        CLK_SWCR|=0x02; //�����л�
//        CLK_SWR=0xb4;
//        while((CLK_SWCR & 0x01)==0x01);
//        CLK_CKDIVR=0x04;
//        CLK_SWCR&=(~0x02); //�ر��л�
//        for(i=0;i<10;i++)
//        {
//						LED_PORT=0xff;
//						delay_ms(500);
//						LED_PORT=(~0xff);
//						delay_ms(500);
//        }       

}