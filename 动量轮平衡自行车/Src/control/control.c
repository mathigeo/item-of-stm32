#include "control.h"


/**
 * @brief �����ƺ���
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
 * @brief ֱ����PID
 * @param target Ŀ��ֵ
 * @param value ����ֵ
 * @para dvalue �������仯��
 * @retval ���ֵ
 */
float vertical(float target,float value,float dvalue)
{		
	static float kp=-1000,kd=-5;
	float err=0;
	
	err = target - value;
	
	return (kp*err + kd*(-dvalue));
}



/**
 * @brief �ٶȻ�
 * @param target Ŀ��ֵ
 * @param value ����ֵ
 * @retval ���
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
 * @brief ��ͨ�˲�
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


