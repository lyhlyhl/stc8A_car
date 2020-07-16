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
#include "KEY.h"
#include "PID.h"
extern int mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
extern int flag;
extern struct P_pid pid_speed;
extern unsigned long length;
void main(void)
{
      char i;
      int dat1, dat2;
      float speed_L, speed_R, speed_set = 1.0;
      char test[20] = "abc";
      OLED_Init();
      //simiic_init();
      //mpu6050_init();
      //pca_input_init();
      speed_count_init();
      //Timer_uart_init();
      Timer0_init();
      while (1)
      {
            Pwm_set(-60, -60);
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
                  T4T3M = 0xCC;
            }
            speed_L = GetCarSpeed(dat1);
            speed_R = GetCarSpeed(dat2);
            OLED_Show_float(0, 2, speed_L);
            OLED_Show_float(0, 3, speed_R);
            OLED_Show_float(0, 4, speed_set);
            OLED_ShowNum(0, 0, dat1, 5);
            OLED_ShowNum(0, 1, dat2, 5);

            if (KEYScan(3) == 3)
            {
                  speed_set += 0.1;
            }
            else if (KEYScan(4) == 4)
            {
                  speed_set -= 0.1;
            }
            PID_realize(speed_set - (speed_L + speed_R))
            //mpu6050_get_accdata();
            //mpu6050_get_gyro();

            //sprintf(test,"%d %d %d",mpu_gyro_x,mpu_gyro_y,mpu_gyro_z);
            //OLED_ShowString(0,3,test);
            //Delay1ms(10);
            //LED = 0;

            //TR0 = 0;
      }
}
