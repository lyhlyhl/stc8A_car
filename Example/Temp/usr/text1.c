#include "common.h"
#include "SEEKFREE_TSL1401.h"

extern int mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
extern int flag;
extern struct P_pid pid_speed;
extern unsigned long length;


int dat1, dat2;
void main(void)
{
      int i=0;
      float speed_L, speed_R, speed_set = 1.0;
      char test[20] = "abc";
//		P_SW2 = 0x80;
//	XOSCCR = 0xc0; 			// 启动外部晶振
//	while (!(XOSCCR & 1)); 	// 等待时钟稳定
//	CLKDIV = 0x00; 			// 时钟不分频
//	CKSEL = 0x01; 			// 选择外部晶振
//	P_SW2 = 0x00;
      OLED_Init();
      //simiic_init();
      //mpu6050_init();
      //pca_input_init();
      speed_count_init();
	
      Timer_uart_init();
      Timer0_init();
			ccd_init();	
      while (1)
      {
				
		if(tsl1401_finish_flag)
		{
			//发送图像到上位机
			ccd_send_data(UART_1, ccd_data);

			//采集完成标志位清除			
			tsl1401_finish_flag = 0;	
		}				
            Pwm_set(-50, -60);

				
//            speed_L = GetCarSpeed(dat1);
//            speed_R = GetCarSpeed(dat2);
//            OLED_Show_float(0, 2, speed_L);
//            OLED_Show_float(0, 3, speed_R);
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
            PID_realize(speed_set - (speed_L + speed_R));
            //mpu6050_get_accdata();
            //mpu6050_get_gyro();
            //sprintf(test,"%d %d %d",mpu_gyro_x,mpu_gyro_y,mpu_gyro_z);
            //OLED_ShowString(0,3,test);
            //Delay1ms(100);
            //LED = 0;
            //TR0 = 0;
      }
}
