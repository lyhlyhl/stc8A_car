#include "delay.h"

void Delay1ms(int m)		//@24MHz —” ±1ms 
{
   unsigned int k;
	unsigned char i, j;
   
   for(k = 0; k < m; k++)
   {
      i = 31;
      j = 40;
      do
      {
         while (--j);
      } while (--i);
   }
}


void Delay1us(int m)		//@24.000MHz
{
   unsigned int k;
	unsigned char i;
   for(k = 0;k < m; k++)
   {
      i = 6;
      while (--i);
   }
}

void delay4us(u16 us)
 {
  u16 i;
  u8 m;
  for(i=0;i<us;i++)
  for(m=0;m<5;m++);
 }  