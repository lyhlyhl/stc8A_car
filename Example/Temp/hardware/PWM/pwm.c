#include "pwm.h"
#include "stc8.h"

void Pwm_set(float R, float L)
{
	
   if (L >= 1500)  //限制进入计算的pid值为5000到-5000之间
   {
      L = 1500;
   }
   else if (L <= -1500)
   {
      L = -1500;
   }

   if (R >= 1500)
   {
      R = 1500;
   }
   else if (R <= -1500)
   {
      R = -1500;
   }

   P_SW2 = 0x80; //pwm配置
   PWMCKS = 0x00;
   PWMC = 0x0600; //设置初始的pwm值
   if (L < 0)
   {
			  L = -L;
      PWM2T1 = (PWMC * (L / 5000)); //T2高电平时间
      PWM2CR = 0x80;
      PWM3CR = 0x00;
      P23 = 0;
	 }
	 else if(L == 0)
   {
      PWM2CR = 0x00;
      PWM3CR = 0x00;
      P22 = 0;
      P23 = 0;
     
   }
      
   else
   {
      PWM3T1 = (PWMC * (L / 5000));
      PWM2CR = 0x00;
      P22 = 0;
      PWM3CR = 0x80;
   }
	 
   if (R < 0)
   {
				R = -R;
      PWM5T1 = (PWMC * (R / 5000));
      PWM4CR = 0x00;
      P24 = 0;
      PWM5CR = 0x80;
   }
   else if(R == 0)
   {
      PWM4CR = 0x00;
      PWM5CR = 0x00;
      P24 = 0;
      P25 = 0;
   }
   else
   {

      PWM4T1 = (PWMC * (R / 5000));
      PWM5CR = 0x00;
      P25 = 0;
      PWM4CR = 0x80;
   }
	 
   P_SW2 = 0x00;

   PWMCR = 0x80; //使能pwm波
}