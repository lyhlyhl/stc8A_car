#include "stc8.h"
#include "delay.h"
#include "i2c.h"
#include "oled.h"
#include "common.h"
#include "adc.h"
#include <stdio.h>
#include <math.h>
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"
#include "LED.h"

extern int mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;

void main(void)
{
   float V;
   char test[30];
   unsigned char a, i;
   int i_x,i_y,i_z;
   int *p_x=&i_x, *p_y=&i_y, *p_z=&i_z;
   OLED_Init();
   simiic_init();
   mpu6050_init();
   mpu6050_self1_check();
   
   SCON=0x50;        //REN=1允许串行接受状态，串口工作模式2     	   
   TMOD= 0x00;       //定时器1为模式0（16位自动重载）                
   AUXR=0X40;		 //开启1T模式
    TL1=(65535-(24000000/4/9600));    //设置波特率重装值
   TH1=(65535-(24000000/4/9600))>>8;

                     // 如有不明白请查 STC15手册上有详细说明 	 619页
   
   TR1  = 1;        //开启定时器1  
   ES   = 1;        //开串口中断                                                                     
   EA   = 1;        // 开总中断 
   while(1)
   {
      //mpu6050_get_accdata();
      //mpu6050_get_gyro();
      OLED_ShowNum(0,0,mpu_gyro_x,5);
      OLED_ShowNum(0,1,mpu_gyro_y,5);
      OLED_ShowNum(0,2,mpu_gyro_z,5);
      mpu6050_get_gyro_mean(p_x, p_y, p_z,5);
      sprintf(test,"%c%c%c%c%c%c%c%c",0x03,0xFC,(char)i_x,(char)(i_x>>4),(char)(i_x>>8),(char)(i_x>>12),0xFC,0x03);
      //OLED_ShowString(0,3,test);
      for(i = 0;i < 8;i++)
   	{
         SBUF = test[i];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
         while(!TI);				// 等特数据传送	(TI发送中断标志)
         TI = 0;					// 清除数据传送标志
      } 
      

   }
}

void uart_int(void) interrupt 4 using 1
{ 
   ;
}  