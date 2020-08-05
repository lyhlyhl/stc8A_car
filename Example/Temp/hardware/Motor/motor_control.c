#include "motor_control.h"

extern struct P_pid pid_angle,pid_speed,pid_turn;
extern float Turn[5][4];
float set_angle = 45,tangle=0;

extern int mpu_gyro_y ,mpu_gyro_z;
extern int Encoder_Left,Encoder_Right;
int sudu=0;
int Flag_Left,Flag_Right;
int  Moto1,Moto2;

int set_speed=1200;
float last_Velocity;
int Balance_Pwm=0,Velocity_Pwm=0,last_Velocity_Pwm=0,Turn_Pwm=0;
float 
Direct_Parameter = 0,// 转向系数
	Direct_Last = 0,
	Radius = 0;		// 目标转向半径倒数


int velocityPWM=0;
char SpeedControlPeriod = 0;
float Ratio1=0,Ratio2=0;
void stand()
{
   char test[30];
	int Vel_Pwm=0; float a1=0;
	static int ff = 0,cn=0;
	
//			int dat11 = 0,dat22 =0;

//		dat11 = (int)(T3H << 8);
//		dat11 = dat11 | (int)T3L;
//		dat22 = (int)(T4H << 8);
//		dat22 = dat22 | (int)T4L;
//		T4T3M = 0x44;
//		T3H = 0;
//		T3L = 0;
//		T4H = 0;
//		T4L = 0;
//		T4T3M = 0xCC;
//		
//		if (P42 ==0 && P41 == 1)
//		{
//			Encoder_Right = dat11;
//			Encoder_Left = dat22;
//		}
//		if (P42 ==1 && P41 == 0)
//		{
//			Encoder_Right = -dat11;
//			Encoder_Left = -dat22;
//		}
	
  tangle = GetAngle();
			h1 = adc_once(ADC_P00, ADC_12BIT);
			h2 = adc_once(ADC_P01, ADC_12BIT);
			h3= adc_once(ADC_P02, ADC_12BIT);
			h4= adc_once(ADC_P03, ADC_12BIT);
			h5= adc_once(ADC_P10, ADC_12BIT);

			dcc=(float)(h1-h5)/(h1+h3+h5)*100;
			
//	 sprintf(test,"%d %d %d %.2f\r\n",h1,h3,h5,dcc);
//   uart_putstr(test);
	
	
		SpeedControlOutput();
		Balance_Pwm =balance(tangle,mpu_gyro_y,&pid_angle);       
    
		//Radius = -PlacePID_Control(&Turn_PID, Turn[Fre], Middle_Err, 0);//动态PID，动态范围0-0.04	，大误差时起作用，
		//Direct_Parameter = -PID_Realize(&Turn_gyro_PID, Turn_gyro, (int32)(mpu_gyro_z),Radius*Speed_Min);	// 转向环左正右负
		
//	  Direct_Parameter = -PID_Realize(&Turn_gyro_PID, Turn_gyro, (int32)(mpu_gyro_z),40);	// 转向环左正右负
//    Direct_Parameter = range_protect(Direct_Parameter, -800, 800);
	
//		Turn_Pwm  =turn(Encoder_Left,Encoder_Right,mpu_gyro_z,&pid_turn,Turn[0]);     
		if (dcc>20.0 || dcc<-20.0)
		{
			Turn_Pwm  = (int)(dcc *Turn[0][0]+Turn[0][1]*mpu_gyro_z); 
		}
		else
		{
			Turn_Pwm  = (int)(dcc *Turn[1][0]+Turn[1][1]*mpu_gyro_z);
		}
		
		if (dcc<-20 || dcc>20)
		{
			cn = 0;
			ff++;
			if (ff == 10)
			{
				set_speed=1800;
				ff = 0;	
			}
				
		}
		if(dcc>-20 || dcc<20)
		{
			if(cn == 20)
			{
				set_speed=1600;
				cn = 0;
			}
				cn++;
		}
	if (Turn_Pwm<-450)
	{
		Turn_Pwm = -450;
	}
	if(Turn_Pwm>450)
	{
		Turn_Pwm =450;
	}
//		sprintf(test,"%d %.2f %.2f\r\n",Turn_Pwm,dcc,Turn[0][0]);
//		uart_putstr(test);

//		Moto1=Balance_Pwm+Velocity_Pwm-Turn_Pwm;                 
//		Moto2=Balance_Pwm+Velocity_Pwm+Turn_Pwm;  
//		sprintf(test,"%d %d\r\n",Moto1, Moto2);
//		uart_putstr(test);			

//		Moto1=Balance_Pwm;//+velocityPWM-Turn_Pwm;                 
//		Moto2=Balance_Pwm;//+velocityPWM+Turn_Pwm; 
		Moto1=Balance_Pwm-Turn_Pwm;                 
		Moto2=Balance_Pwm+Turn_Pwm;  
		
}

void SpeedControlOutput(void) //速度平滑输出函数
{
		float fValue;
	
		fValue = Velocity_Pwm -last_Velocity_Pwm;
		velocityPWM = fValue * (SpeedControlPeriod + 1)/9 + last_Velocity_Pwm;
	  SpeedControlPeriod++;
}

void SpeedControl(int sspeed)
{
		int dat11 = 0,dat22 =0;
	 char test[20];
		dat11 = (int)(T3H << 8);
		dat11 = dat11 | (int)T3L;
		dat22 = (int)(T4H << 8);
		dat22 = dat22 | (int)T4L;
		T4T3M = 0x44;
		T3H = 0;
		T3L = 0;
		T4H = 0;
		T4L = 0;
		T4T3M = 0xCC;
		
		if (P42 ==0 && P41 == 1)
		{
			Encoder_Right = dat11;
			Encoder_Left = dat22;
		}
		if (P42 ==1 && P41 == 0)
		{
			Encoder_Right = -dat11;
			Encoder_Left = -dat22;
		}
//	 sprintf(test,"%d %d\r\n",Encoder_Right,Encoder_Left);
//   uart_putstr(test);
		
		last_Velocity_Pwm=Velocity_Pwm;
		Velocity_Pwm=velocity(Encoder_Left,Encoder_Right,&pid_speed,sspeed);  
		
//			 sprintf(test,"%d \r\n",Velocity_Pwm);
//  uart_putstr(test);
		
}
	

int balance(float Angle,float Gyro,struct P_pid *pid)
{  
   float Bias;
	 int balance;
	 Bias=Angle-set_angle;             
	 balance=pid->Kp*(Bias+(int)(velocityPWM/500))+Gyro*pid->Kd; //velocityPWM Velocity_Pwm
	if(balance > 1300)
		{
			balance = 1300;
		}			
		else if (balance<-1300)
		{
			balance = -1300;
		}  
	 return balance;
}



extern char jifenflag;
int velocity(int encoder_left,int encoder_right, struct P_pid *pid,int speed)
{  
    static float Velocity,Encoder_Least,Encoder,last_Encoder,Movement=0; 
	  static float Encoder_Integral;

  	Encoder_Least =(encoder_left+encoder_right)-speed;   
		Encoder *= 0.75;		                              
		Encoder += Encoder_Least*0.25;	               
		Encoder_Integral +=Encoder;                                  
               
		if(Encoder_Integral>12000)  	Encoder_Integral=12000;        
		if(Encoder_Integral<-12000)	Encoder_Integral=-12000;
		
		Velocity=Encoder*pid->Kp+Encoder_Integral*pid->Ki; 
	  //Velocity=Encoder*kp+Encoder_Integral*ki + kd * (Encoder - last_Encoder); 
	
//		last_Encoder = Encoder;
	  if(turn_off(tangle)==1)  Encoder_Integral=0;    
		
	
	  return Velocity;
}

//float Velocity,LastVelocity;
//int velocity(int encoder_left,int encoder_right, struct P_pid *pid,int speed)   //222
//{  
//    static float Real_speed,Encoder_Least,Encoder,Encoder_Bias; 
//	  static float Encoder_Integral;

//		Real_speed = (encoder_left+encoder_right)/2;
//		Encoder_Bias =  ((encoder_left+encoder_right)/2)-speed;
//		Encoder_Integral+=Encoder_Bias;  //对偏差积分
//		//积分限幅
//		if (Encoder_Integral>100) Encoder_Integral=100;
//		if (Encoder_Integral>100) Encoder_Integral=-100;
//		LastVelocity = Velocity;
//		//pi控制
//		Velocity = pid->Kp*Encoder_Bias+pid->Ki*Encoder_Integral;
//	
//	  if(turn_off(tangle)==1)  Encoder_Integral=0;    
//		
//	
//	  return Velocity;
//}




int Flag_sudu = 2;
int turn(int encoder_left,int encoder_right,float gyro,struct P_pid *pid,float *PID)//转向控制
{
	  static float Turn_Target,Turn =0 ,Encoder_temp,Turn_Convert=0.9,Turn_Count;
	  float Turn_Amplitude=88/Flag_sudu;     
	 
  	if(1==Flag_Left||1==Flag_Right)                      //这一部分主要是根据旋转前的速度调整速度的起始速度，增加小车的适应性
		{
			if(++Turn_Count==1)
			Encoder_temp=myabs(encoder_left+encoder_right);
			Turn_Convert=50/Encoder_temp;
			if(Turn_Convert<0.6)Turn_Convert=0.6;
			if(Turn_Convert>3)Turn_Convert=3;
		}	
	  else
		{
			Turn_Convert=0.9;
			Turn_Count=0;
			Encoder_temp=0;
		}			
		if(1==Flag_Left)	           Turn_Target-=Turn_Convert;
		else if(1==Flag_Right)	     Turn_Target+=Turn_Convert; 
		else Turn_Target=0;
	
    if(Turn_Target>Turn_Amplitude)  Turn_Target=Turn_Amplitude;    //转向限幅
	  if(Turn_Target<-Turn_Amplitude) Turn_Target=-Turn_Amplitude;
//		if(Flag_Qian==1||Flag_Hou==1)  Kd=1;        
//		else Kd=0;   //转向的时候取消陀螺仪的纠正 有点模糊PID的思想
  
		  //Turn=-Turn_Target*Kp -gyro*Kd;
		Turn=-dcc*PID[KP] -gyro*PID[KD];  
		if(Turn > 400)
		{
			Turn = 400;
		}			
		else if (Turn<-400)
		{
			Turn = -400;
		}
	  return Turn;
}





u8 turn_off(float tangle)
{	
	u8 temp;
	if(tangle <20|| tangle > 78) 
  {	
		temp = 1;   
  }
	else
  temp=0;
  return temp;	
	
}

int myabs(int a)
{ 		   
	  int temp;
		if(a<0)  temp=-a;  
	  else temp=a;
	  return temp;
}