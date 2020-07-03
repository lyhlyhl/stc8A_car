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
   char test[10];
   OLED_Init();
   simiic_init();
   mpu6050_init();
   //mpu6050_self1_check();
   while(1)
   {
      mpu6050_get_accdata();
      OLED_ShowNum(0,0,mpu_gyro_x,5);
      OLED_ShowNum(0,1,mpu_gyro_y,5);
      OLED_ShowNum(0,2,mpu_gyro_z,5);
      sprintf(test,"%d %d %d",mpu_gyro_x,mpu_gyro_x,mpu_gyro_z);
      OLED_ShowString(0,3,test);
        LED=0;
        Delay1ms(100);
        LED=1;
        Delay1ms(100);
     
      //LED = 0;
   }
}