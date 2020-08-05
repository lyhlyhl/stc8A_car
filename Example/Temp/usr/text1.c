#include "common.h"
#include "main.h"

extern int mpu_gyro_x, mpu_gyro_y, mpu_gyro_z;
extern int flag;
extern struct P_pid pid_speed,pid_angle;
extern unsigned long length;

char flag_angle=0, flag_speed=0,flag_turn=0;
extern int Balance_Pwm,Velocity_Pwm,last_Velocity_Pwm,Turn_Pwm;

int AD_val_1_min=0;
int AD_val_1_max=4095;
int h1,h2,h3,h4,h5;
float dcc;

int uflag=0;

int Encoder_Left,Encoder_Right; 

char jifenflag  =0;

extern int cnt_speed;
extern int set_speed;
int guiyi(int AD_VAL1)
{
	float ad_VAL1;
	if(AD_VAL1>AD_val_1_max)  AD_VAL1=AD_val_1_max;			
						//归一化
  ad_VAL1=100*(float)(AD_VAL1 - AD_val_1_min)/(AD_val_1_max-AD_val_1_min);
	
	return (int)ad_VAL1;
}

void main(void)
{
	int i = 0,flag_1 = 0,a=0;
	int dat11 = 0,dat22 =0,a1=0;
	char test[50] ;
	
	
	init_all();
	P42= 1;P41 =0;
	while (1)
	{	
		if (uflag == 1)
		{
			spilt_str();
			uflag =0;
		}
		
		
		if (KEYScan(2) == 2)
		{
			P43 = ~P43;
		}
		if(flag_angle == 1)
		{		
			flag_angle =0;
		
			stand();
      if (turn_off(tangle)==1||flag_stop ==0)
      { Pwm_set(0,0);}
      else
		 { 
//	    if (Moto1>5)	 a=-200;
//	    if (Moto1<-5)	 a=+100; 
      Pwm_set(Moto1-a,Moto2);				
			}
		}
		
		if (flag_speed == 1)
		{
			//P55=~P55;
			flag_speed =0;	 
			jifenflag=1;
			SpeedControl(set_speed);
		}
		
	/*	{
//				P55=1;
//				h1 = adc_once(ADC_P01, ADC_12BIT);
//				h2 = adc_once(ADC_P11, ADC_12BIT);
//				h3= adc_once(ADC_P12, ADC_12BIT);
//				h4= adc_once(ADC_P16, ADC_12BIT);
//				h5= adc_once(ADC_P17, ADC_12BIT);
//				dcc=(float)(h1-h5)/(h1+h3+h5)*100;
//				
////				sprintf(test,"%d\r\n",(int)dcc);
////				uart_putstr(test);
//				guiyi(h1);
//				//sprintf(test,"%d %d\r\n",guiyi(h1),h1);
//				//uart_putstr(test);
//				P55=0;
	
				
//				sprintf(test,"%d %d %d %d % d\r\n",h1,h2,h3,h4,h5);
//				uart_putstr(test);
            //		if(tsl1401_finish_flag)
            //		{
            //			//发送图像到上位机
            //			ccd_send_data(UART_1, ccd_data);

            //			//采集完成标志位清除
            //			tsl1401_finish_flag = 0;
            //		}  
					}*/
	}     
}

void init_all()
{

	P42= 0;P41 =0;
      EA = 0;
//  OLED_Init();
    simiic_init();
    mpu6050_init();
	
		adc_init(ADC_P10,ADC_SYSclk_DIV_2);//5
		adc_init(ADC_P03,ADC_SYSclk_DIV_2);//4
		adc_init(ADC_P02,ADC_SYSclk_DIV_2);//3
		adc_init(ADC_P01,ADC_SYSclk_DIV_2);//2
		adc_init(ADC_P00,ADC_SYSclk_DIV_2);//1
	
//      //pca_input_init();
//   
//      //speed_count_init();

      Timer_uart_init();       	//串口蓝牙
      Timer0_init();						//电机控制
////      //ccd_init();
      pid_init();		
      EA = 1;
}