
//  �жϺ���
//  P32��  ���½��ر仯  �����ϵ�����ָʾ�ƻᷢ����Ӧ�ķ�ת



#include "stc8.h"


sbit  led=P5^5;



main()
{

   EX0=1;   //�����ⲿ�ж�0  ��P3.2
   IT0=0;	//�½��ش���   IT0=1 Ϊ ������ �½��ؾ���
   EA=1;	//�������ж�
   while(1);

}


void zhong() interrupt 0
{
led=!led;
}
