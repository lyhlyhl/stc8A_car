

#ifndef I2C_H
#define I2C_H
#include "def.h"

void IIC_Start();		  //��������
void IIC_Stop();		  //ֹͣ����
void Write_IIC_Byte(u8 c);	  //�ֽ����ݷ��ͺ���
u8  RcvByte(u8 ack);	  //�ֽ����ݽ��պ���	    

u8 IIC_Wait_Ack(void);	  //�ȴ�Ӧ���źŵ���


#endif
