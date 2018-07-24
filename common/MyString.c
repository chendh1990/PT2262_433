#include "config.h"

#define ERR 0XFF

/************************************************************
@比较常数字符串
************************************************************/
u8 my_strstr(const char *s1,u8 s1len,const char *s2)
{

  int len2;
  int i;

  if(s1len >= 0XFF)         //比较的长度不能大于等于255
  {
    return ERR;
  }
  if(!(len2=strlen(s2)))    //如果字符串2的长度为0，则错误返回
  {
     return ERR;
  }

  for(i=0;i+len2<=s1len;i++)
  {                                 
    if((*s1==*s2) && (strncmp(s1,s2,len2)==0))      //以字符串2的长度为准，全字匹配
    {
       return i;                                
    }
    s1++;
  }

  return ERR;
}

/************************************************************
@比较变量字符串
************************************************************/
u8 my_str1str2(char *s1,u8 s1len,char *s2,u8 s2len)
{

  int i;

  if(s1len >= 0XFF || s1len == 0)           //比较的长度不能大于等于255或者0
  {
    return ERR;
  }
  if(!(s2len))                              //如果字符串2的长度为0，则错误返回
  {
     return ERR;
  }

  for(i=0;i+s2len<=s1len;i++)
  {                                 
    if((*s1==*s2) && (strncmp(s1,s2,s2len)==0))      //以字符串2的长度为准，全字匹配
    {
       return i;                                
    }
    s1++;
  }

  return ERR;
} 


/************************************************************
@cs=所有数之和
cs = BYTE1+BYTE2+...
************************************************************/
u8 get_checksum(u8 *p,u16 len)
{
  u8 cs = 0;

  while(len--)
  {
    cs += *p;
    p++;
  }

  return cs;
}

/************************************************************
@cs=所有数之和的负数
cs = -(BYTE1+BYTE2+...)
************************************************************/
u8 get_checksumINV(u8 *p,u16 len)
{
  u8 cs = 0;

  while(len--)
  {
    cs -= *p;
    p++;
  }

  return cs;
}

  
  