#include "timer.h"
#include "LED.h"
int flag = 0;
void Timer_uart_init() //�����жϳ�ʼ��
{
   SCON |= 0x50;                          //REN=1�����н���״̬�����ڹ���ģʽ2
   TMOD |= 0x00;                          //��ʱ��1Ϊģʽ0��16λ�Զ����أ�
   AUXR = 0X40;                           //����1Tģʽ`    PS����һ�в��ܻ���ڲ�Ȼ�����޷���
   TL1 = (65535 - (24000000 / 4 / 9600)); //���ò�������װֵ
   TH1 = (65535 - (24000000 / 4 / 9600)) >> 8;
   TR1 = 1; //������ʱ��1
   ES = 1;  //�������ж�
   EA = 1;  // �����ж�
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
   speed = speed * 50;
   return speed;
}

void time0_itp() interrupt 1 //��ʱ��0�жϷ�����
{
   static int cnt = 0; //���ü��� ��50��ȡ����������ֵ
   if (cnt >= 20)
   {
      flag = 1;
      cnt = 0;
      LED = ~LED;
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