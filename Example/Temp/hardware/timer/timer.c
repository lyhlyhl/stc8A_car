#include "timer.h"

int flag = 0;
u8 busy[5];	


void Timer_uart_init() //�����жϳ�ʼ��
{
   SCON |= 0x50;                          //REN=1�����н���״̬�����ڹ���ģʽ2
   TMOD |= 0x00;                          //��ʱ��1Ϊģʽ0��16λ�Զ����أ�
   AUXR = 0X40;                           //����1Tģʽ`    PS����һ�в��ܻ���ڲ�Ȼ�����޷���
   TL1 = (65535 - (22118400 / 4 / 115200)); //���ò�������װֵ
   TH1 = (65535 - (22118400 / 4 / 115200)) >> 8;
   TR1 = 1; //������ʱ��1
   ES = 1;  //�������ж�
   EA = 1;  // �����ж�
	 busy[1] = 0;
}


//UART1�ж�
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
//  @brief      �����ֽ����
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      dat             ��Ҫ���͵��ֽ�
//  @return     void        
//  Sample usage:               uart_putchar(UART_1,0xA5);       // ����1����0xA5
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
//  @brief      ���ڷ�������
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      *buff           Ҫ���͵������ַ
//  @param      len             ���ͳ���
//  @return     void
//  Sample usage:               uart_putbuff(UART_1,&a[0],5);
//-------------------------------------------------------------------------------------------------------------------
void uart_putbuff(UARTN_enum uart_n,u8 *p,u16 len)
{
    while(len--)
        uart_putchar(uart_n,*p++);
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ���ڷ����ַ���
//  @param      uart_n          ����ģ���(USART_1,USART_2,USART_3,USART_4)
//  @param      *str            Ҫ���͵��ַ�����ַ
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



void Timer0_init() //��ʱ���ж�0��ʼ��
{
   TMOD |= 0x00;
   //AUXR|=0x80; //����1Tģʽ
   TL0 = 0x30; //��ʱ��1ms
   TH0 = 0xf8;
   TR0 = 1;
   ET0 = 1;
   EA = 1;
}

void speed_count_init() //�趨T3T4��������ȡ��������ֵ
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
void time0_itp() interrupt 1 //��ʱ��0�жϷ�����
{
   static int cnt = 0; //���ü��� ��50��ȡ����������ֵ
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