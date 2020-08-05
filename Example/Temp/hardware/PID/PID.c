#include "PID.h"
#include "common.h"


struct P_pid pid_speed,pid_angle, pid_turn;			//速度  角度 角加速度

float Turn[5][4]  = {{40, 0.000,0, 0},	// 130	// 转向外环动态PID	中线法
					{6, 0, 0, 0},	// 140
					{0, 0, 0, 0},	// 150
					{0, 0, 0, 0},	// 1608
					{0, 0, 0, 0}};	// 170
 
void pid_init()
{
   pid_speed.err = 0;
   pid_speed.Last_err=0;
   pid_speed.Kp = 1.6;  //-15  -5     -20
   pid_speed.Ki = 0.02;  //-0.06  -0.01  -0.05
   pid_speed.Kd = 0; 
   pid_speed.inegral = 0.0;
   	
	
   pid_angle.err = 0;
   pid_angle.Last_err=0;
   pid_angle.Kp = 360;    //170        250
   pid_angle.Ki = 0.0;
   pid_angle.Kd = 1.6;   //0.6         0.4
   pid_angle.inegral = 0.0;
	 pid_angle.PrevError =0; 
	
	 pid_turn.err = 0;
   pid_turn.Last_err=0;
   pid_turn.Kp = 0;
   pid_turn.Kd = 0.0;
   pid_turn.Kd = 0.0;
   pid_turn.inegral = 0.0;
}

float PID_realize(float err, struct P_pid *pid, int gyro_y) //pid的计算公式
{
    pid->err = err;
    pid->inegral += pid->err;
    pid->PIDReturn = pid->Kp * pid->err + pid->Kd * gyro_y;// pid->Ki * pid->inegral + pid->Kd * (pid->err - pid->Last_err);
    pid->Last_err = pid->err;
    return pid->PIDReturn;
}


// 位置式动态PID控制
int PlacePID_Control(float NowPiont, float SetPoint,struct P_pid *pid, float *PID)
{
	//定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
	float iError;	//当前误差
	int  Actual;	//最后得出的实际输出值
	float Kp;		//动态P
	
	iError = SetPoint - NowPiont;	//计算当前误差
	pid->SumError += iError*0.01;
	if (pid->SumError >= PID[KT])
	{
		pid->SumError = PID[KT];
	}
	else if (pid->SumError <= PID[KT])
	{
		pid->SumError = -PID[KT];
	}
	//二次函数是为了达到 误差越大  反应越快 回复力越大 其中 KI值是误差为0时的P 也就是直道上的P值
	Kp = 1.0 * (iError*iError) /PID[KP] + PID[KI];	//P值与差值成二次函数关系，此处P和I不是PID参数，而是动态PID参数，要注意！！！
	
	Actual = Kp * iError
		   + PID[KD] * ((0.8*iError + 0.2*pid->Last_err) - pid->Last_err);//不完全微分  
	pid->Last_err = iError;		//更新上次误差

	//Actual = range_protect(Actual, -260, 260);

	return Actual;
}

/*{
//// 位置式PID控制
//int32 PID_Realize(PID *sptr, float *PID, int32 NowData, int32 Point)
//{
//	//当前误差，定义为寄存器变量，只能用于整型和字符型变量，提高运算速度
//	int32 Realize;	// 最后得出的实际增量

//	sptr->Dis_Err = Point - NowData;	// 计算当前误差
//	sptr->SumError += PID[KI] * sptr->Dis_Err;	// 误差积分
//	
//	if (sptr->SumError >= PID[KT])
//	{
//		sptr->SumError = PID[KT];
//	}
//	else if (sptr->SumError <= -PID[KT])
//	{
//		sptr->SumError = -PID[KT];
//	}
//	
//	Realize = PID[KP] * sptr->Dis_Err
//			+ sptr->SumError
//			+ PID[KD] *(sptr->Dis_Err  - sptr->LastError);
////			+ PID[KB] * ( NowData- sptr->LastData); //微分先行
//	
//	sptr->PrevError = sptr->LastError;	// 更新前次误差
//	sptr->LastError = sptr->Dis_Err;		  	// 更新上次误差
//	sptr->LastData  = NowData;			// 更新上次数据

//	return Realize;	// 返回实际值
//}
}*/



// 增量式PID电机控制
float PID_Increase(float NowData, float Point,struct P_pid *pid)
{
	float iError,	//当前误差
		Increase;	//最后得出的实际增量

	iError = Point - NowData;	// 计算当前误差

	Increase =  pid->Kp * (iError - pid->Last_err)
			  + pid->Ki * iError
			  + pid->Kd * (iError - 2 * pid->Last_err + pid->PrevError);
	
	pid->PrevError = pid->Last_err;	// 更新前次误差
	pid->Last_err = iError;		  	// 更新上次误差
	
	return Increase;	// 返回增量
}

int range_protect(int duty, int min, int max)//限幅保护
{
	if (duty >= max)
	{
		return max;
	}
	if (duty <= min)
	{
		return min;
	}
	else
	{
		return duty;
	}
}
