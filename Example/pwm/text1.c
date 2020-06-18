
//P2.1输出pwm波

#include "stc8.h"

main()
{
   P_SW2=0x80;  //需要将最高位EAXFR先置为1才能访问特殊寄存器
   PWMCKS=0x00;   //PWM时钟选择分频 0x00不分频
   PWMC=0x0800;   //计数器的值
   PWM1T1=0x0380; //高低电平计数器的值
   PWM1T2=0x0580;
   PWM1CR=0x80;   //PWM控制寄存器
   P_SW2=0x00;    //关闭寄存器操作
   
   PWMCR=0x80; //使能PWM波
   while(1);
}