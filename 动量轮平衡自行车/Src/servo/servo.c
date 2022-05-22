#include "servo.h"



/**
 * @brief 舵机初始化(TIM2-CH1)
 * @param None
 * @retval None
 */
void servo_init(uint16_t psc,uint16_t arr)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);	
	
	

	// 自动重装载寄存器的值
	TIM_TimeBaseStructure.TIM_Period=arr;
	// 驱动 CNT 计数器的时钟
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// 时钟分频因子配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// 初始化定时器
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
	
	// 配置为 PWM 模式 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
	
	// 输出比较通道 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
	
	
	// 使能计数器
	TIM_Cmd(TIM2, ENABLE);
}



/**
 * @brief 舵机控制
 * @param angle 角度(0-180)
 * @retval None
 */
void servo_angle(uint16_t angle)
{
	if(angle > 180)
	{
		return ;
	}
	
	TIM2->CCR1 = (0.5+(float)angle*((2.5f-0.5f)/180.0f))*100;
}


