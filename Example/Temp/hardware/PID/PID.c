#include "PID.h"
#include "common.h"
struct P_pid pid_speed,pid_angle;
void pid_init()
{
   pid_speed.err = 0;
   pid_speed.Last_err=0;
   pid_speed.Kp = 3.0;
   pid_speed.Ki = 0.0;
   pid_speed.Kd = 0.0;
   pid_speed.inegral = 0.0;
   
   pid_angle.err = 0;
   pid_angle.Last_err=0;
   pid_angle.Kp = 45;
   pid_angle.Kd = 0.0;
   pid_angle.Kd = 0.0;
   pid_angle.inegral = 0.0;
   
}

float PID_realize(float err, struct P_pid *pid) //pid的计算公式
{
    pid->err = err;
    pid->inegral += pid->err;
    pid->PIDReturn = pid->Kp * pid->err ; //pid->Ki * pid->inegral + pid->Kd * (pid->err - pid->Last_err);
    pid->Last_err = pid->err;
    return pid->PIDReturn;
}
