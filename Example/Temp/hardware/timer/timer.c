#include "timer.h"

int flag = 0;
u8 busy[5];

void Timer_uart_init() //�����жϳ�ʼ��
{
   SCON |= 0x50;                            //REN=1�����н���״̬�����ڹ���ģʽ2
   TMOD |= 0x00;                            //��ʱ��1Ϊģʽ0��16λ�Զ����أ�
   AUXR = 0X40;                             //����1Tģʽ`    PS����һ�в��ܻ���ڲ�Ȼ�����޷���
   TL1 = (65535 - (24000000 / 4 / 115200)); //���ò�������װֵ
   TH1 = (65535 - (24000000 / 4 / 115200)) >> 8;
   TR1 = 1; //������ʱ��1
   ES = 1;  //�������ж�
   EA = 1;  // �����ж�
   busy[1] = 0;
}

//UART1�ж�
void UartIsr() interrupt 4
{
   u8 res;

   if (SCON & 0x02)
   {
      SCON &= ~0x02; // UART1_CLEAR_TX_FLAG;
      busy[1] = 0;
   }
   if (SCON & 0x01)
   {
      SCON &= ~0x01; //  UART1_CLEAR_RX_FLAG;

      res = SBUF;
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
}

float GetCarSpeed(int dat)
{
   float speed;
   speed = (float)dat;
   speed = speed / 16 * 0.049 * 3.14;
   speed = speed * 200;
   return speed;
}

extern int dat1, dat2;
void time0_itp() interrupt 1 //��ʱ��0�жϷ�����
{
   static int cnt = 0; //���ü��� ��5��ȡ����������ֵ
   if (cnt >= 5)
   {
      cnt = 0;
      dat1 = (int)(T3H << 8);
      dat1 = dat1 | (int)T3L;
      dat2 = (int)(T4H << 8);
      dat2 = dat2 | (int)T4L;
      T4T3M = 0x44;
      T3H = 0;
      T3L = 0;
      T4H = 0;
      T4L = 0;
      T4T3M = 0xCC;
   }
   cnt++;
}
void uart_int(void) interrupt 4 using 1   //�����жϺ���
{
   if (RI)
   {
      uart_get_data();
      RI = 0;
   }
}
void TM3() interrupt 19 //�����������Ǽ��������жϷ����������Ǽ����������ܼ�������û��
{
   //LED = !LED;
   AUXINTIF &= ~T3IF;
}

void TM4() interrupt 20
{
   //LED = !LED;
   AUXINTIF &= ~T4IF;
}