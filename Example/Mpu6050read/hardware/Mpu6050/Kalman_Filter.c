#include "Kalman_Filter.h"


//??????????

float dt=0.001;//??:dt????kalman???????

float angle, angle_dot;//??????

float PP[2][2] = {(1, 0),(0, 1)};

float Pdot[4] ={ 0,0,0,0};

float Q_angle=0.001, Q_gyro=0.005; //角度置信度,角速度置信度

float R_angle=0.5 ,C_0 = 1;

float q_bias, angle_err, PCt_0, PCt_1, E, K_0, K_1, t_0, t_1;

float Kalman_Filter(float angle_m, float gyro_m)//angleAx ? gyroGy
{
        angle+=(gyro_m-q_bias) * dt;
        angle_err = angle_m - angle;
        Pdot[0]=Q_angle - PP[0][1] - PP[1][0];
        Pdot[1]=- PP[1][1];
        Pdot[2]=- PP[1][1];
        Pdot[3]=Q_gyro;
        PP[0][0] += Pdot[0] * dt;
        PP[0][1] += Pdot[1] * dt;
        PP[1][0] += Pdot[2] * dt;
        PP[1][1] += Pdot[3] * dt;
        PCt_0 = C_0 * PP[0][0];
        PCt_1 = C_0 * PP[1][0];
        E = R_angle + C_0 * PCt_0;
        K_0 = PCt_0 / E;
        K_1 = PCt_1 / E;
        t_0 = PCt_0;
        t_1 = C_0 * PP[0][1];
        PP[0][0] -= K_0 * t_0;
        PP[0][1] -= K_0 * t_1;
        PP[1][0] -= K_1 * t_0;
        PP[1][1] -= K_1 * t_1;
        angle += K_0 * angle_err; //????
        q_bias += K_1 * angle_err;
        angle_dot = gyro_m-q_bias;//?????
        return angle;
}

