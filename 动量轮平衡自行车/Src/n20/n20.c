#include "n20.h"


/**
 * @brief n20电机驱动初始化(PA5,PA6控制正反转)
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
 * @brief n20pwm初始化(PB0输出PWM)
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
	
	//定时器其他部分已经在wheel里面初始化了
	
}


