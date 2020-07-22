#include "pwm.h"
#include "stc8.h"

void Pwm_set(float L, float R)
{
   if (L >= 100)  //限制进入计算的pid值为100到-100之间
   {
      L = 100;
   }
   else if (L <= -100)
   {
      L = -100;
   }

   if (R >= 100)
   {
      R = 100;
   }
   else if (R <= -100)
   {
      R = -100;
   }

   P_SW2 = 0x80; //pwm配置
   PWMCKS = 0x00;
   PWMC = 0x0600; //设置初始的pwm值
   if (L > 0)
   {

      PWM2T1 = (PWMC * (L / 100)); //T2高电平时间
      PWM2CR = 0x80;
      P24 = 0;
   }
   else
   {
      L = -L;
      PWM4T1 = (PWMC * (L / 100));
      P22 = 0;
      PWM4CR = 0x80;
   }
   if (R > 0)
   {
      PWM3T1 = (PWMC * (R / 100));
      P26 = 0;
      PWM3CR = 0x80;
   }
   else
   {

      R = -R;
      PWM6T1 = (PWMC * (R / 100));
      P23 = 0;
      PWM6CR = 0x80;
   }
   P_SW2 = 0x00;

   PWMCR = 0x80; //使能pwm波
}