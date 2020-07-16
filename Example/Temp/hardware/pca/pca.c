#include "pca.h"
#include "common.h"
#include "LED.h"
unsigned long length = 0;

void pca_input_init(void)  //输入捕获初始化
{
   CCON = 0x00;
   CMOD = 0x09;
   CL = 0x00;
   CH = 0x00;
   CCAPM0 = 0x10;
   CCAP0L = 0x00;
   CCAP0H = 0x00;
   CR = 1;
   EA = 1;
}
			 
void Pca_isr() interrupt 7
{
   static unsigned char cnt = 0;
   static unsigned int count0 = 0;
   static unsigned int count1 = 0;
   if(CF)
   {
      CF = 0;
      cnt++;
   }
   if(CCF0)
   {
      CCF0 = 0;
      count0=count1;
      count1 = CCAP0H<<8 | CCAP0L;
      length = 0;
      length = count1+65536*cnt;
      CL = 0x00;
      CH = 0x00;
      cnt = 0;
      
      //LED = ~LED;
   }
}