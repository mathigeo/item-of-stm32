#include "stepper.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


uint32_t pulse_num = 0;



/**
 * @brief 步进电机初始化
 * @param None
 * @retval None
 */
void stepper_init(uint16_t psc,uint16_t arr)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);	
	
	

	
	// 自动重装载寄存器的值，累计 TIM_Period+1 个频率后产生一个更新或者中断
	TIM_TimeBaseStructure.TIM_Period=arr;
	// 驱动 CNT 计数器的时钟 = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// 时钟分频因子 ，配置死区时间时需要用到
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// 计数器计数模式，设置为向上计数
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// 重复计数器的值，没用到不用管
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// 初始化定时器
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


	// 设置中断来源
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
	// 设置主优先级为 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// 设置抢占优先级为 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);



	// 配置为 PWM 模式 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
	// 输出比较通道 
	TIM_OCInitStructure.TIM_Pulse = arr/2;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_FLAG_Update,ENABLE);
	
	
	// 使能计数器
	TIM_Cmd(TIM4,DISABLE);
}


/**
 * @brief 步进电机走多少脉冲
 * @param n 脉冲数
 * @retval None
 */
void stepper_pulse(int32_t n)
{
	if(pulse_num == 0)
	{
		pulse_num = n;
		TIM_Cmd(TIM4,ENABLE);
	}
}



/**
 * @brief 定时器中断服务函数
 * @param None
 * @retval None
 */
void TIM4_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM4,TIM_IT_Update)!= RESET) 
	{
		if(pulse_num != 0)
		{
			pulse_num--;
		}
		else
		{
			TIM_Cmd(TIM4,DISABLE);
		}
		TIM_ClearITPendingBit(TIM4,TIM_FLAG_Update);
	}
}



