
//  中断函数
//  P32口  有下降沿变化  板子上的运行指示灯会发生相应的翻转



#include "stc8.h"


sbit  led=P5^5;



main()
{

   EX0=1;   //开启外部中断0  即P3.2
   IT0=0;	//下降沿触发   IT0=1 为 上升沿 下降沿均可
   EA=1;	//开启总中断
   while(1);

}


void zhong() interrupt 0
{
led=!led;
}
