#include "timer.h"

int flag = 0;
u8 busy[5];	


void Timer_uart_init() //串口中断初始化
{
   SCON |= 0x50;                          //REN=1允许串行接受状态，串口工作模式2
   TMOD |= 0x00;                          //定时器1为模式0（16位自动重载）
   AUXR = 0X40;                           //开启1T模式`    PS：这一行不能或等于不然串口无法打开
   TL1 = (65535 - (22118400 / 4 / 115200)); //设置波特率重装值
   TH1 = (65535 - (22118400 / 4 / 115200)) >> 8;
   TR1 = 1; //开启定时器1
   ES = 1;  //开串口中断
   EA = 1;  // 开总中断
	 busy[1] = 0;
}


//UART1中断
void UartIsr() interrupt 4
{
    u8 res;
	
    if(SCON  & 0x02)
    {
      SCON  &= ~0x02; // UART1_CLEAR_TX_FLAG;
        busy[1] = 0;
    }
    if(SCON  & 0x01)
    {
      SCON  &= ~0x01;//  UART1_CLEAR_RX_FLAG;

      res = SBUF;

    }
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口字节输出
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      dat             需要发送的字节
//  @return     void        
//  Sample usage:               uart_putchar(UART_1,0xA5);       // 串口1发送0xA5
//-------------------------------------------------------------------------------------------------------------------
void uart_putchar(UARTN_enum uart_n,u8 dat)
{
//	switch(uart_n)
//	{
//		case UART_1:
			while (busy[1]);
			busy[1] = 1;
			SBUF = dat;
//		    break;
//		case UART_2:
//			while (busy[2]);
//			busy[2] = 1;
//			S2BUF = dat;
//		    break;
//		case UART_3:
//			while (busy[3]);
//			busy[3] = 1;
//			S3BUF = dat;
//		    break;
//		case UART_4:
//			while (busy[4]);
//			busy[4] = 1;
//			S4BUF = dat;
//		    break;
//	}
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送数组
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      *buff           要发送的数组地址
//  @param      len             发送长度
//  @return     void
//  Sample usage:               uart_putbuff(UART_1,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uart_n,u8 *p,u16 len)
{
    while(len--)
        uart_putchar(uart_n,*p++);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      串口发送字符串
//  @param      uart_n          串口模块号(USART_1,USART_2,USART_3,USART_4)
//  @param      *str            要发送的字符串地址
//  @return     void
//  Sample usage:               uart_putstr(UART_1,"i lvoe you"); 
//-------------------------------------------------------------------------------------------------------------------
void uart_putstr(UARTN_enum uart_n,u8 *str)
{
    while(*str)
    {
        uart_putchar(uart_n,*str++);
    }
}



void Timer0_init() //定时器中断0初始化
{
   TMOD |= 0x00;
   //AUXR|=0x80; //开启1T模式
   TL0 = 0x30; //定时器1ms
   TH0 = 0xf8;
   TR0 = 1;
   ET0 = 1;
   EA = 1;
}

void speed_count_init() //设定T3T4计数器读取编码器的值
{
   T3L = 0x00;
   T3H = 0x00;

   T4L = 0x00;
   T4H = 0x00;

   IE2 = 0x60;
   T4T3M = 0xcc;

   EA = 1;
}

float GetCarSpeed(int dat)
{
   float speed;
   speed = (float)dat;
   speed = speed / 70 * 0.045 * 3.14;
   speed = speed * 20;
   return speed;
}

extern int dat1, dat2;
void time0_itp() interrupt 1 //定时器0中断服务函数
{
   static int cnt = 0; //设置计数 到50读取计数器计数值
   if (cnt >= 50)
   {
		  TR0 = 0;

      flag = 1;
      cnt = 0;
      LED = ~LED;
		 
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
		 	TR0 = 1;
   }
   cnt++;
}
void TM3() interrupt 19
{
   //LED = !LED;
   AUXINTIF &= ~T3IF;
}

void TM4() interrupt 20
{
   //LED = !LED;
   AUXINTIF &= ~T4IF;
}