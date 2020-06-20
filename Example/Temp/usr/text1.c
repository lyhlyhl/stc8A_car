#include "stc8.h"
#include "delay.h"
#include "i2c.h"
#include "oled.h"
#include "common.h"
#include "adc.h"
#include <stdio.h>
#include <math.h>

void main(void)
{
   float V;
   char test[10];
   OLED_Init();
   while(1)
   {
//     P55=0;
//     Delay1ms(1000);
//     P55=1;
//     Delay1ms(1000);
      V = GetADCResult(0);
      V=V*5/4096;
      sprintf(test,"%.2f",V);
      OLED_ShowString(1,2,test);
      
   }
}