#include "stc8.h"
#include "delay.h"
#include "i2c.h"
#include "oled.h"
#include "common.h"
#include "adc.h"
#include <stdio.h>
#include <math.h>
#include "SEEKFREE_IIC.h"
#include "SEEKFREE_MPU6050.h"
#include "LED.h"
#include "Kalman_Filter.h"

extern int mpu_gyro_x,mpu_gyro_y,mpu_gyro_z;
extern int mpu_acc_x,mpu_acc_y,mpu_acc_z;
void main(void)
{
   float V;
   char test[30];
   unsigned char a, i;
   float angleAx,gyroGy;
   float Angle;
   int Angle_i;
   //int i_x,i_y,i_z,;
   //int *p_x=&i_x, *p_y=&i_y, *p_z=&i_z;
   OLED_Init();
   simiic_init();
   mpu6050_init();
   mpu6050_self1_check();
   
   SCON=0x50;        //REN=1�����н���״̬�����ڹ���ģʽ2     	   
   TMOD= 0x00;       //��ʱ��1Ϊģʽ0��16λ�Զ����أ�                
   AUXR=0X40;		 //����1Tģʽ`
    TL1=(65535-(24000000/4/19200));    //���ò�������װֵ
   TH1=(65535-(24000000/4/19200))>>8;
   TR1  = 1;        //������ʱ��1  
   ES   = 1;        //�������ж�                                                                     
   EA   = 1;        // �����ж� 
   while(1)
   {
      mpu6050_get_accdata();
      mpu6050_get_gyro();
      angleAx=atan2(mpu_acc_x,mpu_acc_z)*180/3.14;
      gyroGy= (-mpu_gyro_y)/16.40;
      Angle = Kalman_Filter(angleAx,gyroGy);
      
      Angle_i=(int)Angle;
      //mpu6050_get_gyro_mean(p_x, p_y, p_z,5);  
      //sprintf(test,"%c%c%c%c%c%c%c%c",0x03,0xFC,(char)Angle_i,(char)(Angle_i>>4),(char)(Angle_i>>8),(char)(Angle_i>>12),0xFC,0x03);
      //OLED_ShowString(0,3,test);
      sprintf(test,"%d %.2f %.2f\n",Angle_i, angleAx,gyroGy);
//      for(i = 0;i < 8;i++)
//   	{
//         SBUF = test[i];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
//         while(!TI);				// �������ݴ���	(TI�����жϱ�־)
//         TI = 0;					// ������ݴ��ͱ�־
//      } 
      for(i = 0;test[i] != '\0';i++)
   	{
         SBUF = test[i];	        //SUBF����/���ͻ�����(�ֽд���ͨ�����⹦�ܼĴ���)
         while(!TI);				// �������ݴ���	(TI�����жϱ�־)
         TI = 0;					// ������ݴ��ͱ�־
      } 
      

   }
}

 