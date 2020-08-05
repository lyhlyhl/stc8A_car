#include "timer.h"

int flag = 0;

void Timer_uart_init() //串口中断初始化
{
   SCON |= 0x50;                            //REN=1允许串行接受状态，串口工作模式2
   TMOD |= 0x00;                            //定时器1为模式0（16位自动重载）
   AUXR = 0X40;                             //开启1T模式`    PS：这一行不能或等于不然串口无法打开
   TL1 = (65535 - (24000000 / 4 / 115200)); //设置波特率重装值
   TH1 = (65535 - (24000000 / 4 / 115200)) >> 8;
   TR1 = 1; //开启定时器1
   ES = 1;  //开串口中断

}

/*{
//UART1中断
//void UartIsr() interrupt 4
//{
//   u8 res;

//   if (SCON & 0x02)
//   {
//      SCON &= ~0x02; // UART1_CLEAR_TX_FLAG;
//      busy[1] = 0;
//   }
//   if (SCON & 0x01)
//   {
//      SCON &= ~0x01; //  UART1_CLEAR_RX_FLAG;

//      res = SBUF;
//   }
//}
}*/
void Timer0_init() //定时器中断0初始化
{
   TMOD |= 0x00;
   //AUXR|=0x80; //开启1T模式
   TL0 = 0x30; //定时器1ms
   TH0 = 0xf8;
   TR0 = 1;
   ET0 = 1;
}

void speed_count_init() //设定T3T4计数器读取编码器的值
{
   T3L = 0x00;
   T3H = 0x00;

   T4L = 0x00;
   T4H = 0x00;

   IE2 = 0x60;
   T4T3M = 0xcc;
}



extern int  Encoder_Left, Encoder_Right;
int a1=0;
int cnt_speed = 0 ;
void time0_itp() interrupt 1 //定时器0中断服务函数
{
   static int cnt = 0,cnt_stand = 0; //设置计数 到5读取计数器计数值
   float a=0;
   char test[30];
	
	if (cnt == 5)
	{
		flag_angle = 1;
		
		if (SpeedControlPeriod == 9)
			SpeedControlPeriod=0;
		
		cnt =0;

	}
	if (cnt_speed == 45)
	{
		flag_speed = 1;
		cnt_speed =0;
	}
	/*{
	
//   if (cnt_stand== 9)
//   {
//		  //P55 =1;
//      dat11 = (int)(T3H << 8);
//      dat11 = dat11 | (int)T3L;
//      dat22 = (int)(T4H << 8);
//      dat22 = dat22 | (int)T4L;
//      T4T3M = 0x44;
//      T3H = 0;
//      T3L = 0;
//      T4H = 0;
//      T4L = 0;
//      T4T3M = 0xCC;
//			if (P42 ==0 && P40 == 1)
//			{
//				Encoder_Right = -dat11;
//				Encoder_Left = -dat22;
//			}
//			if (P42 ==1 && P40 == 0)
//			{
//				Encoder_Right = dat11;
//				Encoder_Left = dat22;
//			}
//			h1 = adc_once(ADC_P01, ADC_12BIT);
//			h2 = adc_once(ADC_P11, ADC_12BIT);
//			h3= adc_once(ADC_P12, ADC_12BIT);
//			h4= adc_once(ADC_P16, ADC_12BIT);
//			h5= adc_once(ADC_P17, ADC_12BIT);
//			guiyi(h1);
//			guiyi(h2);
//			guiyi(h3);
//			guiyi(h4);
//			guiyi(h5);
//			dcc=(float)(h1-h5)/(h1+h3+h5)*100;
//			a1 =(float)(h1-h5)/(h1+h5)*100;
////		 	sprintf(test,"%d %d %d %d %d\r\n",(int)dcc,h1,guiyi(h3),h5 , a1);
////      uart_putstr(test);
//		  //P55 =0;
//		 cnt_stand = 0;
//   }
//	 
//   if(cnt_stand == 2)
//   {
//		// P55 =1;
//		 
//     stand();		 
//		 if (turn_off(tangle)==1||flag_stop ==0)
//		 { Pwm_set(0,0);}
//		 else
//		 { 
//			 if (Moto1>5)	
//				 a=-200;
//			 if (Moto1<-5)	
//				 a=+100; 
//			
//		 Pwm_set(Moto1-a,Moto2);}

////      sprintf(test,"%.2f\r\n",motor_pwm);
////      uart_putstr(test);
//    //  P55 =0;
//		 
//   }
}*/
   cnt_speed++;
   cnt_stand++;
   cnt++;
}

void uart_int(void) interrupt 4    //串口中断函数
{
   if(RI)
   {
		 uart_get_data();
		 RI = 0;
   }
}


void TM3() interrupt 19 //下面俩个都是计数器的中断服务函数，但是计数器不可能计满所以没用
{
   //LED = !LED;
   AUXINTIF &= ~T3IF;
}

void TM4() interrupt 20
{
   //LED = !LED;
   AUXINTIF &= ~T4IF;
}