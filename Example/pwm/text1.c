
//P2.1输出pwm波

#include "stc8.h"

main()
{
   P_SW2=0x80;  //需要将最高位EAXFR先置为1才能访问特殊寄存器
   PWMCKS=0x00;   //PWM时钟选择分频 0x00不分频
   PWMC=0x0600;   //计数器的值
   
   PWM2T1=0x0500; //高低电平计数器的值
   //PWM1T2=0x0300;
   PWM4T1=0x0100;
   
   PWM2CR=0x80;   //PWM控制寄存器
   PWM4CR=0x80;
   P_SW2=0x00;    //关闭寄存器操作
   
   PWMCR=0x80; //使能PWM波
   while(1);
}