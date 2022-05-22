#include "n20.h"


/**
 * @brief n20���������ʼ��(PA5,PA6��������ת)
 * @param None
 * @retval None
 */
void n20_driver_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);  

	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5|GPIO_Pin_6; 
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;         
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_InitStruct);	
}



/**
 * @brief n20pwm��ʼ��(PB0���PWM)
 * @param None
 * @retval None
 */
void n20_pwm_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_0;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStruct);
	
	//��ʱ�����������Ѿ���wheel�����ʼ����
	
}


