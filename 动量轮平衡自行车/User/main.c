#include "system.h"  
#include "systick.h"
#include "oled.h"
#include "adc.h"
#include "encoder.h"
#include "mpu6050.h"
#include "inv_mpu.h"
#include "mpu_exti.h"
#include "plog.h"
#include "wheel.h"
#include "servo.h"
#include "n20.h"



int main(void)
{		
	//�ж����ȼ�����
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//OLED��ʼ��
	OLED_Init();
	//�����ʼ��
	servo_init(719,1999);
	//��������ʼ��
	encoder_TIM4_Init();
	//MPUԭʼ���ݶ�ȡ��ʼ��
	PLOG(1,MPU6050_Init());
	//dmp��ʼ��
	PLOG(2,mpu_dmp_init());
	//MPU�жϳ�ʼ��
	MPU6050_EXTI_Init();
	//OLED�����Ļ
	OLED_Clear();
	//������pwm��ʼ��
	wheel_pwm_init(0,7199);
	//������������ʼ��
	wheel_driver_init();
	//ADC��ʼ��
	adcx_init();
	//n20���������ʼ��
	n20_driver_init();
	//n20���PWM��ʼ��
//	n20_pwm_init();
//	n20_setPWM(0);
//	n20_back();
	while(1)
	{
		oledPrint(1,1,"s:%6d",wheel_speed);
		oledPrint(2,1,"roll:%4.1f",mpudata.roll);
		oledPrint(3,1,"grox:%6d",mpudata.gyrox);
		oledPrint(4,1,"pwr:%4.1f",adc_dat.vol);
	} 
}


//PA13/JTMS/SWDIO��PA14/JTCK/SWCLK
//PA15/JTDI��PB3/JTDO��PB4/JNTRST

