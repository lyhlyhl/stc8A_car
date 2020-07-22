#include "motor_control.h"
extern struct P_pid pid_angle;
float stand()
{
//   char test[10];
   float set_angle = -102.5,angle_err,pid_return,angle;
   angle = GetAngle();
   angle_err = set_angle-angle;
   if(angle > -30 || angle < -170)
   {
      Pwm_set(0,0);
      return 0;
   }
      
//   sprintf(test,"%.2f %.2f\r\n",angle,abs(angle_err));
//   uart_putstr(test);
   else
   {
      pid_return = PID_realize(angle_err,&pid_angle);
      return pid_return;
   }
   
}