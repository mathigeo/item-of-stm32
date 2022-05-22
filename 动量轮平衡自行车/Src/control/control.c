#include "control.h"


/**
 * @brief 主控制函数
 * @param None
 * @retval None
 */
void main_ctrl(void)
{
	static int pwm;
	
	wheel_speed = read_encoder();
	
	pwm = vertical(-1+velocity(0,wheel_speed),mpudata.roll,mpudata.gyrox);
	
	if(pwm > 7000)
		pwm = 7000;
	if(pwm < -7000)
		pwm = -7000;
	
	if(mpudata.roll > 35 || mpudata.roll < -35)
	{
		wheel_load(0);
	}
	else
	{
		wheel_load(pwm);
	}
}



/**
 * @brief 直立环PID
 * @param target 目标值
 * @param value 测量值
 * @para dvalue 测量量变化量
 * @retval 输出值
 */
float vertical(float target,float value,float dvalue)
{		
	static float kp=-1000,kd=-5;
	float err=0;
	
	err = target - value;
	
	return (kp*err + kd*(-dvalue));
}



/**
 * @brief 速度环
 * @param target 目标值
 * @param value 测量值
 * @retval 输出
 */ 
float velocity(float target,float value)
{
	static float kp=-0.12f,ki=-0.12f/200.0f;
	static float ite=0;
	float err;
	
	err = target - value;
	
	lowpass(&err);
	ite += err;
	
	ite = ite>10000?10000:ite;
	ite = ite<-10000?-10000:ite;
	
	return (kp*err + ki*ite);
}



/**
 * @brief 低通滤波
 * @param None
 * @retval None
 */
void lowpass(float *p)
{
	static float a = 0.7;
	static float flt = 0;
	
	(*p) = a*flt + (1-a)*(*p);
	
	flt = (*p);
}	


