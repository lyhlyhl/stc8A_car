#ifndef _PID_h
#define _PID_h
#include "stc8.h"
struct P_pid
{
   float SetEle;     //定义设定值
   float ActualEle;  //定义实际值
   float err;        //定义偏差值
   float Last_err;   //定义上一个偏差值
   float Kp,Ki,Kd;   //定义积分值
   float PID;    //定义输出值
   float inegral;    //定义积分量
   float PIDReturn;
};
void pid_init(void);
float PID_realize(float err,struct P_pid *pid);
#endif
 

