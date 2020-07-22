#include "KEY.h"


u8 KEYScan(u8 key)   //°´¼üÉ¨Ãè¼ì²âº¯Êý
{
   if(key == 2 )
   {
      if(P20 == 0)
      {
         Delay1ms(5);
         if(P20 == 0)
            return 2;
      }
   }
   else if(key == 3)
   {
      if(P53 == 0)
      {
         Delay1ms(5);
         if(P53 == 0)
            return 3;
      }
   }
   else if(key == 4)
   {
      if(P52 == 0)
      {
         Delay1ms(5);
         if(P52 == 0)
            return 4;
      }
   }
   return 0;

}