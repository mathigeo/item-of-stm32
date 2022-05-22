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
	//中断优先级分组
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	//OLED初始化
	OLED_Init();
	//舵机初始化
	servo_init(719,1999);
	//编码器初始化
	encoder_TIM4_Init();
	//MPU原始数据读取初始化
	PLOG(1,MPU6050_Init());
	//dmp初始化
	PLOG(2,mpu_dmp_init());
	//MPU中断初始化
	MPU6050_EXTI_Init();
	//OLED清空屏幕
	OLED_Clear();
	//动量轮pwm初始化
	wheel_pwm_init(0,7199);
	//动量轮驱动初始化
	wheel_driver_init();
	//ADC初始化
	adcx_init();
	//n20电机驱动初始化
	n20_driver_init();
	//n20电机PWM初始化
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


//PA13/JTMS/SWDIO、PA14/JTCK/SWCLK
//PA15/JTDI、PB3/JTDO、PB4/JNTRST

