
//P2.1���pwm��

#include "stc8.h"

main()
{
   P_SW2=0x80;  //��Ҫ�����λEAXFR����Ϊ1���ܷ�������Ĵ���
   PWMCKS=0x00;   //PWMʱ��ѡ���Ƶ 0x00����Ƶ
   PWMC=0x0800;   //��������ֵ
   PWM1T1=0x0380; //�ߵ͵�ƽ��������ֵ
   PWM1T2=0x0580;
   PWM1CR=0x80;   //PWM���ƼĴ���
   P_SW2=0x00;    //�رռĴ�������
   
   PWMCR=0x80; //ʹ��PWM��
   while(1);
}