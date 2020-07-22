#include "common.h"
#include "main.h"
extern int mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
extern int flag;
extern struct P_pid pid_speed;
extern unsigned long length;

int uflag=0;

int dat1, dat2,dat_set = 1;
void main(void)
{
      int i = 0,flag_1 = 0;
      float speed_L, speed_R,pwm_value = 50,pwm_init = 0;
      char test[20] = "abc";
      init_all();
      Pwm_set(pwm_init, pwm_init);
      while (1)
      {
				
				
				if (uflag == 1)
				{
					spilt_str();
					uflag =0;
				}

            //		if(tsl1401_finish_flag)
            //		{
            //			//发送图像到上位机
            //			ccd_send_data(UART_1, ccd_data);

            //			//采集完成标志位清除
            //			tsl1401_finish_flag = 0;
            //		}
            
//            a = dat_set - ((dat1+dat2)/2) ;
            
//            speed_L = GetCarSpeed(dat1);
//            speed_R = GetCarSpeed(dat2);
//            OLED_Show_float(0, 2, speed_L);
//            OLED_Show_float(0, 3, speed_R);
//            OLED_ShowNum(0, 4, dat_set,5);
//            OLED_Show_float(0, 5, pwm_value);
//            OLED_Show_float(0, 6 , pwm_init);
//            OLED_ShowNum(0, 0, dat1, 5);
//            OLED_ShowNum(0, 1, dat2, 5);
            

            
            
//            sprintf(test,"%.2f \r\n",angle);
//            uart_putstr(test);
            
//            pwm_value = PID_realize(a,pid_speed);
//            pwm_init += pwm_value;
//            Pwm_set(pwm_init,pwm_init);
            // sprintf(test, "%d %d\r\n", dat1, dat2);
            // uart_putstr(test);
//            if (KEYScan(3) == 3)
//            {
//                  dat_set += 1;
//                  flag_1 = 0;
//            }
//            else if (KEYScan(4) == 4)
//            {
//                  dat_set -= 1;
//                  flag_1 = 0;
//            }
//            else if (KEYScan(2) == 2)
//            {
//                  flag_1 = 1;
//            }
//            if(flag_1 == 1)
//            {
              
//            }
            //mpu6050_get_accdata();
            //mpu6050_get_gyro();
            //sprintf(test,"%d %d %d",mpu_gyro_x,mpu_gyro_y,mpu_gyro_z);
            //OLED_ShowString(0,3,test);
            //Delay1ms(100);
            //LED = 0;
            //TR0 = 0;
      }
}

void init_all()
{
      //		P_SW2 = 0x80;
      //	XOSCCR = 0xc0; 			// 启动外部晶振
      //	while (!(XOSCCR & 1)); 	// 等待时钟稳定
      //	CLKDIV = 0x00; 			// 时钟不分频
      //	CKSEL = 0x01; 			// 选择外部晶振
      //	P_SW2 = 0x00;
      EA = 0;
      OLED_Init();
      simiic_init();
      mpu6050_init();
      //pca_input_init();
   
      //speed_count_init();

      Timer_uart_init();
      Timer0_init();
      //ccd_init();
      pid_init();
      EA = 1;
}