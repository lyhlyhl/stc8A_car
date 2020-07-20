#include "timer.h"
#include "LED.h"
int flag = 0;
void Timer_uart_init() //串口中断初始化
{
   SCON |= 0x50;                          //REN=1允许串行接受状态，串口工作模式2
   TMOD |= 0x00;                          //定时器1为模式0（16位自动重载）
   AUXR = 0X40;                           //开启1T模式`    PS：这一行不能或等于不然串口无法打开
   TL1 = (65535 - (24000000 / 4 / 9600)); //设置波特率重装值
   TH1 = (65535 - (24000000 / 4 / 9600)) >> 8;
   TR1 = 1; //开启定时器1
   ES = 1;  //开串口中断
   EA = 1;  // 开总中断
}

void Timer0_init() //定时器中断0初始化
{
   TMOD |= 0x00;
   //AUXR|=0x80; //开启1T模式
   TL0 = 0x30; //定时器1ms
   TH0 = 0xf8;
   TR0 = 1;
   ET0 = 1;
   EA = 1;
}

void speed_count_init() //设定T3T4计数器读取编码器的值
{
   T3L = 0x00;
   T3H = 0x00;

   T4L = 0x00;
   T4H = 0x00;

   IE2 = 0x60;
   T4T3M = 0xcc;

   EA = 1;
}

float GetCarSpeed(int dat)
{
   float speed;
   speed = (float)dat;
   speed = speed / 70 * 0.045 * 3.14;
   speed = speed * 50;
   return speed;
}

void time0_itp() interrupt 1 //定时器0中断服务函数
{
   static int cnt = 0; //设置计数 到50读取计数器计数值
   if (cnt >= 20)
   {
      flag = 1;
      cnt = 0;
      LED = ~LED;
   }
   cnt++;
}
void TM3() interrupt 19
{
   //LED = !LED;
   AUXINTIF &= ~T3IF;
}

void TM4() interrupt 20
{
   //LED = !LED;
   AUXINTIF &= ~T4IF;
}