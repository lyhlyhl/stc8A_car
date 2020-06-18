#include "stc8.h"
#include "delay.h"
#include "i2c.h"
#include "oled.h"
#include "common.h"
main()
{
   OLED_Init();
   while(1)
   {
//     P55=0;
//     Delay1ms(1000);
//     P55=1;
//     Delay1ms(1000);
      OLED_ShowChar(1,2,'a');
   }
}