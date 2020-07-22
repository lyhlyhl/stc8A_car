#include "pwm.h"
#include "stc8.h"

void Pwm_set(float L, float R)
{
   if (L >= 4000)  //限制进入计算的pid值为5000到-5000之间
   {
      L = 4000;
   }
   else if (L <= -4000)
   {
      L = -4000;
   }

   if (R >= 4000)
   {
      R = 4000;
   }
   else if (R <= -4000)
   {
      R = -4000;
   }

   P_SW2 = 0x80; //pwm配置
   PWMCKS = 0x00;
   PWMC = 0x0600; //设置初始的pwm值
   if (L > 0)
   {

      PWM2T1 = (PWMC * (L / 5000)); //T2高电平时间
      PWM2CR = 0x80;
      PWM4CR = 0x00;
      P24 = 0;
      
   }
   else if(L == 0)
   {
      PWM2CR = 0x00;
      PWM4CR = 0x00;
      P22 = 0;
      P24 = 0;
     
   }
      
   else
   {
      L = -L;
      PWM4T1 = (PWMC * (L / 5000));
      PWM2CR = 0x00;
      P22 = 0;
      PWM4CR = 0x80;
   }
   if (R > 0)
   {
      PWM3T1 = (PWMC * (R / 5000));
      PWM6CR = 0x00;
      P26 = 0;
      PWM3CR = 0x80;
   }
   else if(R == 0)
   {
      PWM3CR = 0x00;
      PWM6CR = 0x00;
      P23 = 0;
      P26 = 0;
   }
   else
   {

      R = -R;
      PWM6T1 = (PWMC * (R / 5000));
      PWM3CR = 0x00;
      P23 = 0;
      PWM6CR = 0x80;
   }
   P_SW2 = 0x00;

   PWMCR = 0x80; //使能pwm波
}