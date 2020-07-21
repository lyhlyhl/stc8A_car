#include "PID.h"

struct P_pid pid_speed = {

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

float PID_realize(float err, struct P_pid pid) //pid的计算公式
{
    pid.err = err;
    pid.inegral += pid.err;
    pid.PIDReturn = pid.Kp * pid.err + pid.Ki * pid.inegral + pid.Kd * (pid.err - pid.Last_err);
    pid.Last_err = pid.err;
    return pid.PIDReturn;
}
