#ifndef _REMOTE_LCD_H
#define _REMOTE_LCD_H


#define  MOV(x)         ((u16)(x<<4))

//数码管1 
#define  CAP_SHI_SEG_A         (MOV(0)|BIT(3))
#define  CAP_SHI_SEG_B         (MOV(1)|BIT(3))
#define  CAP_SHI_SEG_C         (MOV(1)|BIT(1))
#define  CAP_SHI_SEG_D         (MOV(0)|BIT(0))
#define  CAP_SHI_SEG_E         (MOV(0)|BIT(1))
#define  CAP_SHI_SEG_F         (MOV(0)|BIT(2))
#define  CAP_SHI_SEG_G         (MOV(1)|BIT(2))
//数码管2
#define  CAP_GE_SEG_A           (MOV(2)|BIT(3))
#define  CAP_GE_SEG_B           (MOV(3)|BIT(3))
#define  CAP_GE_SEG_C           (MOV(3)|BIT(1))
#define  CAP_GE_SEG_D           (MOV(2)|BIT(0))
#define  CAP_GE_SEG_E           (MOV(2)|BIT(1))
#define  CAP_GE_SEG_F           (MOV(2)|BIT(2))
#define  CAP_GE_SEG_G           (MOV(3)|BIT(2))
//数码管3
#define  CAP_UNIT_SEG_A         (MOV(4)|BIT(3))
#define  CAP_UNIT_SEG_B         (MOV(5)|BIT(3))
#define  CAP_UNIT_SEG_C         (MOV(5)|BIT(1))
#define  CAP_UNIT_SEG_D         (MOV(4)|BIT(0))
#define  CAP_UNIT_SEG_E         (MOV(4)|BIT(1))
#define  CAP_UNIT_SEG_F         (MOV(4)|BIT(2))
#define  CAP_UNIT_SEG_G         (MOV(5)|BIT(2))
//数码管4
#define  PERCENT_SHI_SEG_A         (MOV(13)|BIT(3))
#define  PERCENT_SHI_SEG_B         (MOV(14)|BIT(3))
#define  PERCENT_SHI_SEG_C         (MOV(14)|BIT(1))
#define  PERCENT_SHI_SEG_D         (MOV(13)|BIT(0))
#define  PERCENT_SHI_SEG_E         (MOV(13)|BIT(1))
#define  PERCENT_SHI_SEG_F         (MOV(13)|BIT(2))
#define  PERCENT_SHI_SEG_G         (MOV(14)|BIT(2))
//数码管5
#define  PERCENT_GE_SEG_A         (MOV(15)|BIT(3))
#define  PERCENT_GE_SEG_B         (MOV(16)|BIT(3))
#define  PERCENT_GE_SEG_C         (MOV(16)|BIT(1))
#define  PERCENT_GE_SEG_D         (MOV(15)|BIT(0))
#define  PERCENT_GE_SEG_E         (MOV(15)|BIT(1))
#define  PERCENT_GE_SEG_F         (MOV(15)|BIT(2))
#define  PERCENT_GE_SEG_G         (MOV(16)|BIT(2))

//数码管6
#define  TIME_BAI_SEG_A         (MOV(18)|BIT(3))
#define  TIME_BAI_SEG_B         (MOV(19)|BIT(3))
#define  TIME_BAI_SEG_C         (MOV(19)|BIT(1))
#define  TIME_BAI_SEG_D         (MOV(18)|BIT(0))
#define  TIME_BAI_SEG_E         (MOV(18)|BIT(1))
#define  TIME_BAI_SEG_F         (MOV(18)|BIT(2))
#define  TIME_BAI_SEG_G         (MOV(19)|BIT(2))
//数码管7
#define  TIME_SHI_SEG_A         (MOV(26)|BIT(3))
#define  TIME_SHI_SEG_B         (MOV(27)|BIT(3))
#define  TIME_SHI_SEG_C         (MOV(27)|BIT(1))
#define  TIME_SHI_SEG_D         (MOV(26)|BIT(0))
#define  TIME_SHI_SEG_E         (MOV(26)|BIT(1))
#define  TIME_SHI_SEG_F         (MOV(26)|BIT(2))
#define  TIME_SHI_SEG_G         (MOV(27)|BIT(2))
//数码管8
#define  TIME_GE_SEG_A          (MOV(28)|BIT(3))
#define  TIME_GE_SEG_B          (MOV(29)|BIT(3))
#define  TIME_GE_SEG_C          (MOV(29)|BIT(1))
#define  TIME_GE_SEG_D          (MOV(28)|BIT(0))
#define  TIME_GE_SEG_E          (MOV(28)|BIT(1))
#define  TIME_GE_SEG_F          (MOV(28)|BIT(2))
#define  TIME_GE_SEG_G          (MOV(29)|BIT(2))


#define  CAP_DOT_SEG            (MOV(1)|BIT(0))
#define  CAP_SIGNAL_S1          (MOV(5)|BIT(0))
#define  CAP_SIGNAL_S2          (MOV(3)|BIT(0))
#define  CAP_SIGNAL_S3          (MOV(17)|BIT(0))
#define  CAP_SIGNAL_S4          (MOV(17)|BIT(1))
#define  CAP_SIGNAL_S5          (MOV(17)|BIT(2))
#define  CAP_SIGNAL_S6          (MOV(17)|BIT(3))
#define  CAP_PERCENT_SYMBOL     (MOV(16)|BIT(0))





void LcdDispTime(u16 dat);
void LcdDispPercent(u8 dat);
void LcdDispCAP(u8 dat);
void LcdDispCAP_Icon(u8 flag);
void LcdDispSignal(u8 dat);
void LcdDispPercentSymbol(u8 flag);
void LcdDispCAPDot(u8 flag);
void LcdDispOff(void);
void LCD_DispFlowAndPercent(u8 dat);

#endif


