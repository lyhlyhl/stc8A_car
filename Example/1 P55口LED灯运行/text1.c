/*
   ��˸��ʵ�� 
   �˶�ָʾ��ֱ�ӽ���P55����
   ֻҪ����io����Ӧ��ƽ�仯����
   */

#include "stc8.h"

void Delay1ms(int m)		//@24MHz ��ʱ1ms 
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