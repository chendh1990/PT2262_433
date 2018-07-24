#include "config.h"

unsigned long delay_counter;

/************************************************************
@
************************************************************/
void GetResetStatus()
{
    u8 dat;
    dat = RST_SR;
    deg_string("\nRST_SR:");
    printf_u8(dat);
    RST_SR = 0x00;
}

/************************************************************
@
************************************************************/
void main( void )
{
    //初始化系统
    clock_init();
    //-------------------应用开始--------------------------------------//
    RF433_Main();
    
    
//    OXY_Test();
    
    IWDG_Init();
//    Timer1CounterTest();
//    RelayMain();
 //   RF433_Test();
//    ADC_Test();
  //  FlashDownLoad_main();
//   GsmMain(); 
//   ADC_Test();
//    LCD5110_main();
    
//    PWM_Test();
//    TestTimer1_main();
//    BJ501TimerTest();
//    W25X_main();
//    IIC_test_main();
//    LCD5110_main();
//    SetTimerTick(50);
//    SPI_SDEF_Main();
//    //MSG2_Test();
    //test_ms();
    //Init_Timer2();
//    asm("nop");
//    asm("nop");
//    asm("nop");
//    Test_write_onebyte();
//    eeprom_main();
    //GetResetStatus();
//    IWDG_Init();
//    asm("nop");
//    asm("nop");
//    asm("nop");    
    while(1)
    {
    }
}





