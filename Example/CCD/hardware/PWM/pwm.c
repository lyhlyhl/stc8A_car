#include "pwm.h"
#include "stc8.h"

void Pwm_set(float L,float R)
{
   P_SW2=0x80;  //��Ҫ�����λEAXFR����Ϊ1���ܷ�������Ĵ���
   PWMCKS=0x00;   //PWMʱ��ѡ���Ƶ 0x00����Ƶ
   PWMC=0x0600;   //��������ֵ
   if(L > 0)
   {
      
        PWM2T1=(PWMC*(L/100)); //�ߵ͵�ƽ��������ֵ
        P24 = 0;
        PWM2CR=0x80;
      //PWM1T2=0x0300;
      //PWM4T1=PWMC-PWM2T1;
   }
   else
   {
      L = -L;
      //PWM4T1=(PWMC*(L/100)); //�ߵ͵�ƽ��������ֵ
      PWM4T1=(PWMC*(L/100));
      P22 = 0;
      PWM4CR=0x80;
   }
   if(R > 0)
   {
      PWM3T1=(PWMC*(R/100));
      P26 = 0;
      PWM3CR=0x80;
   }
   else
   {
      
      R = -R;
      PWM6T1=(PWMC*(R/100));
      P23 = 0;
      PWM6CR=0x80;
   }
   P_SW2=0x00;    //�رռĴ�������
   
   PWMCR=0x80; //ʹ��PWM��
}