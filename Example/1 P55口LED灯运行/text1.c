/*
   闪烁灯实验 
   运动指示灯直接接在P55口上
   只要控制io口相应电平变化即可
   */

#include "stc8.h"

void Delay1ms(int m)		//@24MHz 延时1ms 
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

main()
{

   while(1)
   {
     P55=0;
     Delay1ms(1000);
     P55=1;
     Delay1ms(1000);
   }
}