#include "PID.h"

struct P_pid pid_speed={   //�趨�ٶȻ�pid�ĳ�ֵ
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   0.0,
   
   
   5.0,
   0.0,
   0.0,
};

float PID_realize(float err,struct P_pid pid)   //pid����
{
   pid.err=err;
   pid.inegral+=pid.err;
   pid.PIDReturn =pid.Kp*pid.err+pid.Ki*pid.inegral+pid.Kd*(pid.err-pid.Last_err);
   pid.Last_err=pid.err;
   return pid.PIDReturn; 
}
