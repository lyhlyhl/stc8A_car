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
#include "pwm.h"
#include "pca.h"
#include "timer.h"

extern int mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
extern int flag;

extern unsigned long length;
void main(void)
{
      char i;
      int dat1, dat2 = 2;
      char test[20] = "abc";
      OLED_Init();
      //simiic_init();
      //mpu6050_init();
      //pca_input_init();
      //speed_count_init();
      //Timer_uart_init();
      //Timer0_init();
      while (1)
      {
            Pwm_set(50, 50);
            if (flag == 1)
            {
                  EA = 0;
                  flag = 0;
                  dat1 = (int)(T3H << 8);
                  dat1 = dat1 | (int)T3L;
                  dat2 = (int)(T4H << 8);
                  dat2 = dat2 | (int)T4L;
                  T4T3M = 0x44;
                  T3H = 0;
                  T3L = 0;
                  T4H = 0;
                  T4L = 0;
                  EA = 1;
            }
            OLED_ShowNum(0, 0, dat1, 5);
            OLED_ShowNum(0, 1, dat2, 5);

            //mpu6050_get_accdata();
            //mpu6050_get_gyro();

            //sprintf(test,"%d %d %d",mpu_gyro_x,mpu_gyro_y,mpu_gyro_z);
            //OLED_ShowString(0,3,test);
            Delay1ms(10);
            //LED = 0;

            //TR0 = 0;
      }
}
