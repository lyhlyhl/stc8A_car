

#ifndef I2C_H
#define I2C_H
#include "def.h"

void IIC_Start();		  //启动总线
void IIC_Stop();		  //停止总线
void Write_IIC_Byte(u8 c);	  //字节数据发送函数
u8  RcvByte(u8 ack);	  //字节数据接收函数	    

u8 IIC_Wait_Ack(void);	  //等待应答信号到来


#endif
