#ifndef __MYSTRING_H__
#define __MYSTRING_H__


u8 my_strstr(const char *s1,u8 s1len,const char *s2);
u8 my_str1str2(char *s1,u8 s1len,char *s2,u8 s2len);

u8 get_checksum(u8 *p,u16 len);
u8 get_checksumINV(u8 *p,u16 len);
#endif