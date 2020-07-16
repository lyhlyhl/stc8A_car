#include "pwm.h"
#include "stc8.h"

void Pwm_init(int L,int R)
{
   P_SW2=0x80;  //需要将最高位EAXFR先置为1才能访问特殊寄存器
   PWMCKS=0x00;   //PWM时钟选择分频 0x00不分频
   PWMC=0x0600;   //计数器的值
   
   PWM2T1=(PWMC*(L/100)); //高低电平计数器的值
   //PWM1T2=0x0300;
   PWM4T1=PWMC-PWM2T1;
   PWM3T1=(PWMC*(R/100));
   PWM6T1=PWMC-PWM3T1;
   
   PWM2CR=0x80;   //PWM控制寄存器
   PWM3CR=0x80;
   PWM4CR=0x80;
   PWM6CR=0x80;
   P_SW2=0x00;    //关闭寄存器操作
   
   PWMCR=0x80; //使能PWM波
   while(1);
}