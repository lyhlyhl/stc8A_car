#ifndef _MOTOR_h
#define _MOTOR_h

#include "common.h"

extern int  Moto1,Moto2;
extern int  Flag_Left,Flag_Right;
extern float tangle;
extern char SpeedControlPeriod;

void stand();
void SpeedControl(int sspeed);


u8 turn_off(float tangle); //�رյ��



int range_protect(int duty, int min, int max);//�޷�����
int balance(float Angle,float Gyro,struct P_pid *pid);
int velocity(int encoder_left,int encoder_right, struct P_pid *pid,int speed);
int turn(int encoder_left,int encoder_right,float gyro,struct P_pid *pid,float *PID);//ת�����

void SpeedControlOutput(void); //�ٶ�ƽ���������
int myabs(int a);
#endif