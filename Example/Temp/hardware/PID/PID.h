#ifndef _PID_h
#define _PID_h
#include "stc8.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3

struct P_pid
{
   float SetEle;     //�����趨ֵ
   float ActualEle;  //����ʵ��ֵ
   float err;        //����ƫ��ֵ
   float Last_err;   //������һ��ƫ��ֵ
	 float PrevError;  //��������һ��ƫ��ֵ
   float Kp,Ki,Kd;   //�������ֵ
   float PID;    //�������ֵ
   float inegral;    //���������
	
   float PIDReturn;
	 float SumError;
};
extern float Turn[5][4]; 
	
void pid_init(void);
int PlacePID_Control(float NowPiont, float SetPoint,struct P_pid *pid, float *PID);
float PID_realize(float err, struct P_pid *pid, int gyro_y);
float PID_Increase(float NowData, float Point,struct P_pid *pid);
#endif
 

