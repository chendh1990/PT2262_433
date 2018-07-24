#ifndef __EEPROM_H__
#define __EEPROM_H__


u8 EEPROM_Unlock(void);
void EEPROM_Lock(void);
u8 EEPROM_WriteByte(u16 addr,u8 *buf,u16 num);
void EEPROM_ReadByte(u16 addr,u8 *buf,u16 num);

void eeprom_main(void);
void Test_write_onebyte();
u8 SystemSetOPTByte(void);

#endif