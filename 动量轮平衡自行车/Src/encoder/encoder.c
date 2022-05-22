#include "encoder.h"

int wheel_speed = 0;

/**
 * @brief ������ʱ������(��ʱ��4)
 * @param None
 * @retval None
 */
void encoder_TIM4_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	
	/*-����ʱ��-*/
	//ʹ�ܶ�ʱ��4��ʱ��
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	//ʹ��PA�˿�ʱ��
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

	
	
	/*-�˿�����-*/
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;   
	//��������
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING; 
	//�����趨������ʼ��GPIOA
    GPIO_Init(GPIOB, &GPIO_InitStructure); 
	
	
	
	
	/*-����ʱ��-*/
    TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
	// Ԥ��Ƶ��
    TIM_TimeBaseStructure.TIM_Prescaler = 0x0000; 
	//�趨�������Զ���װֵ
    TIM_TimeBaseStructure.TIM_Period = 0XFFFF; 
	//ѡ��ʱ�ӷ�Ƶ������Ƶ
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	//TIM���ϼ���
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	//ʱ���ṹ���ʼ��
    TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);
	
	
	
	/*-������ģʽ�����벶������-*/
	//ʹ�ñ�����ģʽ3
    TIM_EncoderInterfaceConfig(TIM4,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
    TIM_ICStructInit(&TIM_ICInitStructure);
    TIM_ICInitStructure.TIM_ICFilter = 10;
    TIM_ICInit(TIM4, &TIM_ICInitStructure);	
	
	
	
	/*-����׼��-*/
    TIM_ClearFlag(TIM4, TIM_FLAG_Update);
    TIM_ITConfig(TIM4, TIM_IT_Update, ENABLE);
    TIM_SetCounter(TIM4,0);
    TIM_Cmd(TIM4, ENABLE);
}


/**
 * @brief ������������
 * @param None
 * @retval None
 */
int read_encoder(void)
{
	int dat;
	dat = (short)TIM4->CNT;
	TIM4->CNT=0;
	return dat;
}




/**
 * @brief ��ʱ��4�жϷ�����
 * @param None
 * @retval None
 */
void TIM4_IRQHandler(void)
{
	//����ж�
    if(TIM_GetITStatus(TIM4,TIM_IT_Update)!=0)
    {
    }
	//����жϱ�־λ
    TIM_ClearITPendingBit(TIM4,TIM_IT_Update);
}



