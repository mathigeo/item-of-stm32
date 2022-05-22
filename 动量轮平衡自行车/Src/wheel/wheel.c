#include "wheel.h"
#include "stm32f10x_gpio.h"

/**
 * @brief ������PWM��ʼ��
 * @param psc Ԥ��Ƶϵ��
 * @param arr �Զ���װ��ֵ
 * @retval None
 */
void wheel_pwm_init(u16 psc,u16 arr)
{
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;	
	
	
	// ����Ƚ�ͨ��2 GPIO ��ʼ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// ������ʱ��ʱ��,���ڲ�ʱ�� CK_INT=72M
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);
	
	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	
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
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
	


	// ����Ϊ PWM ģʽ 1
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	// ���ʹ��
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	// ���ͨ����ƽ��������
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
	// ����Ƚ�ͨ�� 2
	TIM_OCInitStructure.TIM_Pulse = 0;
	
	TIM_OC2Init(TIM3,&TIM_OCInitStructure);
	TIM_OC3Init(TIM3,&TIM_OCInitStructure);
	
	TIM_OC2PreloadConfig(TIM3,TIM_OCPreload_Enable);
	TIM_OC3PreloadConfig(TIM3,TIM_OCPreload_Enable);
	// ʹ�ܼ�����
	TIM_Cmd(TIM3,ENABLE);
}


/**
 * @brief ����������������ת���ų�ʼ��
 * @param None
 * @retval None
 * @note
	PB9��������ת
	PB8�ߵ�ƽ����
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
 * @brief �������
 * @param v ת��
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










