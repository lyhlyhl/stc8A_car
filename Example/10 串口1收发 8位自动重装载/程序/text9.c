 



//串口通讯实验  
//这里写好程序 下载到单片机里
//直接 用下载软件的串口助手   以16进制 发送 8A  会接收到  我爱单片机
//此程序虽然很少 但是它有着串口通讯和接收的所有功能  
//需要用串口的朋友只要用它改改就可以实现自己想要的效果 



#include "stc8.h"

char  code  MESSAGE[]= "我爱单片机 ";




void main() 
{


        SCON = 0x50;       //REN=1允许串行接受状态，串口工作模式2     	   
	    TMOD= 0x20;      //定时器工作方式2       8位 自动重装载定时器  实现波特率                

	   AUXR=0X40;		 //开启1T模式   
	   TH1 =TL1= 0xB1;			//  设置波特率为9600  公式 TH1=256-(24000000/32/9600)=256-36=220  0xDC	
                              // 如有不明白请查 STC8手册上有详细说明     
		TR1  = 1;        //开启定时器1                                                      
		ES   = 1;        //开串口中断                  
		EA   = 1;        // 开总中断 
}






void ISP_Check(unsigned char tmp)
{
  unsigned char a;
    if(tmp==0x8A) 
     {
   
     ES= 0;
	  a=0;
	   while(MESSAGE[a]!= '\0')
   	   {
		SBUF = MESSAGE[a];	        //SUBF接受/发送缓冲器(又叫串行通信特殊功能寄存器)
         while(!TI);				// 等特数据传送	(TI发送中断标志)
		 TI = 0;					// 清除数据传送标志
		
		a++;					    // 下一个字符
       } 
 
     ES= 1;
     }

    }   



void Serial_int(void) interrupt 4 using 1
{ unsigned char tmp;
    
	if (RI) 
    {

      tmp = SBUF;

	  ISP_Check(tmp); 

      RI = 0;
    }
}  
