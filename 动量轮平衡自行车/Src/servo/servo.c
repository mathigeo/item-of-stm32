#include "servo.h"



/**
 * @brief �����ʼ��(TIM2-CH1)
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
	
	

	// �Զ���װ�ؼĴ�����ֵ
	TIM_TimeBaseStructure.TIM_Period=arr;
	// ���� CNT ��������ʱ��
	TIM_TimeBaseStructure.TIM_Prescaler= psc;
	// ʱ�ӷ�Ƶ������������ʱ��ʱ��Ҫ�õ�
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	// ����������ģʽ������Ϊ���ϼ���
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	// �ظ���������ֵ��û�õ����ù�
	TIM_TimeBaseStructure.TIM_RepetitionCounter=0;
	// ��ʼ����ʱ��
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);
	
	
	
	// ����Ϊ PWM ģʽ 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
	
	
	// ����Ƚ�ͨ�� 1
	TIM_OCInitStructure.TIM_Pulse = 0;
	TIM_OC1Init(TIM2,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM2,TIM_OCPreload_Enable);
	
	
	
	// ʹ�ܼ�����
	TIM_Cmd(TIM2, ENABLE);
}



/**
 * @brief �������
 * @param angle �Ƕ�(0-180)
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


