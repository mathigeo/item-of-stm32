#include "wheel.h"
#include "stm32f10x_gpio.h"

/**
 * @brief 动量轮PWM初始化
 * @param psc 预分频系数
 * @param arr 自动重装载值
 * @retval None
 */
void wheel_pwm_init(u16 psc,u16 arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	
	// 输出比较通道2 GPIO 初始化
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 开启定时器时钟,即内部时钟 CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	
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
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	


	// 配置为 PWM 模式 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// 输出使能
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// 输出通道电平极性配置
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	// 输出比较通道 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	// 使能计数器
	TIM_Cmd(TIM3,ENABLE);
}


/**
 * @brief 动量轮启动、正反转引脚初始化
 * @param None
 * @retval None
 * @note
	PB9控制正反转
	PB8高电平启动
 */
void wheel_driver_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}



/**
 * @brief 电机控制
 * @param v 转速
 * @retval None
 */
void wheel_load(int v)
{
	if(v < 0)
	{
		v = -v;
		GPIO_ResetBits(GPIOB,GPIO_Pin_9);
	}
	else
	{
		GPIO_SetBits(GPIOB,GPIO_Pin_9);
	}
	TIM_SetCompare2(TIM3,v);
}










