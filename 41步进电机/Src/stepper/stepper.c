#include "stepper.h"
#include "stm32f10x_gpio.h"
#include "stm32f10x_rcc.h"


uint32_t pulse_num = 0;



/**
 * @brief ���������ʼ��
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
	
	

	
	// �Զ���װ�ؼĴ�����ֵ���ۼ� TIM_Period+1 ��Ƶ�ʺ����һ�����»����ж�
	TIM_TimeBaseStructure.TIM_Period=arr;
	// ���� CNT ��������ʱ�� = Fck_int/(psc+1)
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// ʱ�ӷ�Ƶ���� ����������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);


	// �����ж���Դ
	NVIC_InitStructure.NVIC_IRQChannel = TIM4_IRQn ;
	// ���������ȼ�Ϊ 0
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	// ������ռ���ȼ�Ϊ 3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);



	// ����Ϊ PWM ģʽ 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
	// ����Ƚ�ͨ�� 
	TIM_OCInitStructure.TIM_Pulse = arr/2;
	TIM_OC1Init(TIM4, &TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	
	TIM_ClearFlag(TIM4,TIM_FLAG_Update);
	TIM_ITConfig(TIM4,TIM_FLAG_Update,ENABLE);
	
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM4,DISABLE);
}


/**
 * @brief ��������߶�������
 * @param n ������
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
 * @brief ��ʱ���жϷ�����
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



