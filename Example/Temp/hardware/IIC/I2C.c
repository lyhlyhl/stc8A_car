
/*************************�˲���ΪI2C���ߵ���������*************************************/

#include "stc8.h"
#include "i2c.h"
#include "delay.h"

sbit SCL = P1 ^ 5; //I2C  ʱ��
sbit SDA = P1 ^ 4; //I2C  ����

//SDA�������
void IO_SDA(u8 m)
{
  if (m == 1)
  {
    P1M1 = 0X40; //����SDAΪ����
    P1M0 = 0X00;
  }
  else
  {
    P1M1 = 0X00; //�ָ�SDA˫��io
    P1M0 = 0X00;
  }
}

//�����ߺ���
//Start_I2c();
//����:     ����I2C����,������I2C��ʼ����.
void IIC_Start()
{
  SDA = 1; //������ʼ�����������ź�
  SCL = 1;
  delay4us(2);
  SDA = 0; //������ʼ�ź�
  delay4us(2);
  SCL = 0; //ǯסI2C���ߣ�׼�����ͻ��������
}

//�������ߺ���
//Stop_I2c();
//����:     ����I2C����,������I2C��������.
void IIC_Stop()
{
  SCL = 0;
  SDA = 0; //���ͽ��������������ź�
  delay4us(2);
  SCL = 1; //������������ʱ�����4��s
  SDA = 1; //����I2C���߽����ź�
  delay4us(2);
}

//�ȴ�Ӧ���źŵ���
//����ֵ��1������Ӧ��ʧ��
//        0������Ӧ��ɹ�
u8 IIC_Wait_Ack(void)
{
  u8 Time = 0;
  IO_SDA(1); //����SDAΪ����
  SDA = 1;   //׼������Ӧ��λ
  delay4us(1);
  SCL = 1;
  delay4us(1);
  while (SDA)
  {
    Time++;
    if (Time > 250)
    {
      IIC_Stop();
      IO_SDA(0); //�ָ�SDA˫��io
      return 1;  //��Ӧ�𷵻�1
    }
  }
  SCL = 0; //ʱ�����0

  IO_SDA(0); //�ָ�SDA˫��io
  return 0;  //��Ӧ�𷵻�0
}

//�ֽ����ݷ��ͺ���
//SendByte(u8 c);
//����:     ������c���ͳ�ȥ,�����ǵ�ַ,Ҳ����������
void Write_IIC_Byte(u8 c)
{
  u8 BitCnt;
  //���� һ��Ҫ�������� ����SCL����0״̬ ���ܽ���д��
  for (BitCnt = 0; BitCnt < 8; BitCnt++) //Ҫ���͵����ݳ���Ϊ8λ
  {
    if ((c << BitCnt) & 0x80)
      SDA = 1; //�жϷ���λ  �������ɸ�λ��ʼ����
    else
      SDA = 0;
    delay4us(1);
    SCL = 1; //��ʱ����Ϊ�ߣ�֪ͨ��������ʼ��������λ
    delay4us(1);
    SCL = 0;
    delay4us(1);
  }
}

//����ACKӦ��
void I2C_Ack(void)
{
  SCL = 0;
  delay4us(2);
  SDA = 1;
  delay4us(2);
  SDA = 0;
  delay4us(2);
  SCL = 1;
  delay4us(2);
  SCL = 0;
  delay4us(2);
  SDA = 1;
  delay4us(2);
}
//������ACKӦ��
void I2C_NAck(void)
{
  SCL = 0;
  delay4us(2);
  SDA = 1;
  delay4us(2);
  SCL = 1;
  delay4us(2);
  SCL = 0;
  delay4us(2);
  SDA = 0;
  delay4us(2);
}

//�ֽ����ݽ��պ���
//RcvByte();
//����:  �������մ���������������,���ж����ߴ���(��Ӧ���ź�)
//ack  1 ����Ӧ��  0 ������Ӧ��
u8 RcvByte(u8 ack)
{
  u8 retc = 0,
     i;
  IO_SDA(1); //����SDAΪ����
  SDA = 1;
  delay4us(15);

  for (i = 0; i < 8; i++)
  {
    SCL = 0; //��ʱ����Ϊ�ͣ�׼����������λ
    delay4us(2);
    SCL = 1; //��ʱ����Ϊ��ʹ��������������Ч
    delay4us(1);
    retc <<= 1;
    if (SDA)
      retc++; //������λ,���յ�����λ����retc��
    delay4us(1);
  }
  IO_SDA(0); //�ָ�SDA˫��io
  if (!ack)
    I2C_NAck(); //����nACK
  else
    I2C_Ack(); //����ACK

  return retc;
}
