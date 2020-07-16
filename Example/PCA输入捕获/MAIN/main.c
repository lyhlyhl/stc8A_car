						 
/*

   PCA测试
   说明 此程序利用16位PCA定时器 产生脉冲  在主频24M下 产生一个50000分频的脉冲 来控制led灯闪烁
	      PCA定时器的续值和定时器完全是不一样的  在手册794 16位软件定时器模式 有详细介绍
     
*/





#include  "stc8.h"		  //STC15头文件
#include  "def.h"	    		  //宏定义 常用函数
#include  "delay.h"				  //延时函数
#include  "pca.h"



void main()
{  	

	pca();					   //PCA16位定时器脉冲输出测试
	while(1);				   //防止程序跑飞
   	
}






