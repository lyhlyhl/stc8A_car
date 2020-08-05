#ifndef _PID_h
#define _PID_h
#include "stc8.h"

#define KP 0
#define KI 1
#define KD 2
#define KT 3

struct P_pid
{
   float SetEle;     //定义设定值
   float ActualEle;  //定义实际值
   float err;        //定义偏差值
   float Last_err;   //定义上一个偏差值
	 float PrevError;  //定义上上一个偏差值
   float Kp,Ki,Kd;   //定义积分值
   float PID;    //定义输出值
   float inegral;    //定义积分量
	
   float PIDReturn;
	 float SumError;
};
extern float Turn[5][4]; 
	
void pid_init(void);
int PlacePID_Control(float NowPiont, float SetPoint,struct P_pid *pid, float *PID);
float PID_realize(float err, struct P_pid *pid, int gyro_y);
float PID_Increase(float NowData, float Point,struct P_pid *pid);
#endif
 

