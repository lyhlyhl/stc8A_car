																								
/*

串口1通讯实验  		定时器T1 工作模式0  串口工作模式2
发送16进制数据 8A 会返回  我爱单片机		 这样实现一个串口收发的过程
说明 串口1波特率为9600   STC15内部晶振频率为11.0592MHz
*/



#include "stc8.h"

char  code  MESSAGE[]= "我爱单片机 ";	//定义到程序空间中




void ISP_Check(unsigned char tmp)		//串口收到数据处理并发送数据
{
  unsigned char a;
    if(tmp==0x8A) 						//收到的数据为0x15
     {
   
     ES= 0;								//关闭串口中断
	  a=0;
	   while(MESSAGE[a]!= '\0')
   	   {
		SBUF = MESSAGE[a];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
         while(!TI);				// 等特数据传送	(TI发送中断标志)
		 TI = 0;					// 清除数据传送标志
		
		a++;					    // 下一个字符
       } 
 
     ES= 1;								 //开启串口中断
     }

  }   




void main() 			 //主函数
{

       SCON=0x50;        //REN=1允许串行接受状态，串口工作模式2     	   
	   TMOD= 0x00;       //定时器1为模式0（16位自动重载）                
	   AUXR=0X40;		 //开启1T模式
       TL1=(65535-(24000000/4/9600));    //设置波特率重装值
	   TH1=(65535-(24000000/4/9600))>>8;

                        // 如有不明白请查 STC15手册上有详细说明 	 619页
      
	   TR1  = 1;        //开启定时器1  
	   ES   = 1;        //开串口中断                                                                     
	   EA   = 1;        // 开总中断 
	   while(1);
}



void uart_int(void) interrupt 4 using 1
{ 
unsigned char tmp;
    
	if (RI) 
    {

      tmp = SBUF;

	  ISP_Check(tmp); 

      RI = 0;
    }
}  


 



