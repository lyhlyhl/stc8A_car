#ifndef _Kalman_Filter_H
#define _Kalman_Filter_H

#include "common.h"
#include "math.h"
float Kalman_Filter(float Accel,float Gyro);

float GetAngle(void);
#endif