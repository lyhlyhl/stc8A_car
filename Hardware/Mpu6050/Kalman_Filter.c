#include "Kalman_Filter.h"


float Angle = 0;         //????????  
float Gyro_y = 0;


float Q_angle=0.01;  
float Q_gyro=0.001;
float R_angle=0.5;
float dt=0.3;	                  //dt?kalman???????;
char  C_0 = 1;
float Q_bias = 0, Angle_err;
float PCt_0, PCt_1, E;
float K_0, K_1, t_0, t_1;
float Pdot[4] ={0,0,0,0};
float PP[2][2] = { { 1, 0 },{ 0, 1 } };
      
float Kalman_Filter(float Accel,float Gyro)    
{  
 

   Angle+=(Gyro - Q_bias) * dt; //????  
     
   Pdot[0]=Q_angle - PP[0][1] - PP[1][0]; // Pk-????????????  
     
   Pdot[1]=- PP[1][1];  
   Pdot[2]=- PP[1][1];  
   Pdot[3]=Q_gyro;  
     
   PP[0][0] += Pdot[0] * dt;   // Pk-??????????????  
   PP[0][1] += Pdot[1] * dt;   // =?????????  
   PP[1][0] += Pdot[2] * dt;  
   PP[1][1] += Pdot[3] * dt;  
     
   Angle_err = Accel - Angle;  
   //zk-????  
     
   PCt_0 = C_0 * PP[0][0];  
   PCt_1 = C_0 * PP[1][0];  
     
   E = R_angle + C_0 * PCt_0;  
     
   K_0 = PCt_0 / E;  
   K_1 = PCt_1 / E;  
     
   t_0 = PCt_0;  
   t_1 = C_0 * PP[0][1];  
     
   PP[0][0] -= K_0 * t_0;  
   //?????????  
   PP[0][1] -= K_0 * t_1;  
   PP[1][0] -= K_1 * t_0;  
   PP[1][1] -= K_1 * t_1;  
     
   Angle += K_0 * Angle_err ;  
   //????  
   Q_bias  += K_1 * Angle_err; //????  
   Gyro_y   = Gyro - Q_bias;  
   //???(????)???=???  
   return  Angle;  
}
