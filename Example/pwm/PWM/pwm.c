#include "pwm.h"
#include "stc8.h"

void Pwm_init(int L,int R)
{
   P_SW2=0x80;  //��Ҫ�����λEAXFR����Ϊ1���ܷ�������Ĵ���
   PWMCKS=0x00;   //PWMʱ��ѡ���Ƶ 0x00����Ƶ
   PWMC=0x0600;   //��������ֵ
   
   PWM2T1=(PWMC*(L/100)); //�ߵ͵�ƽ��������ֵ
   //PWM1T2=0x0300;
   PWM4T1=PWMC-PWM2T1;
   PWM3T1=(PWMC*(R/100));
   PWM6T1=PWMC-PWM3T1;
   
   PWM2CR=0x80;   //PWM���ƼĴ���
   PWM3CR=0x80;
   PWM4CR=0x80;
   PWM6CR=0x80;
   P_SW2=0x00;    //�رռĴ�������
   
   PWMCR=0x80; //ʹ��PWM��
   while(1);
}