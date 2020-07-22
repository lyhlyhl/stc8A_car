#ifndef _PID_h
#define _PID_h
#include "stc8.h"
struct P_pid
{
   float SetEle;     //�����趨ֵ
   float ActualEle;  //����ʵ��ֵ
   float err;        //����ƫ��ֵ
   float Last_err;   //������һ��ƫ��ֵ
   float Kp,Ki,Kd;   //�������ֵ
   float PID;    //�������ֵ
   float inegral;    //���������
   float PIDReturn;
};
void pid_init(void);
float PID_realize(float err,struct P_pid *pid);
#endif
 

