#include "key.h"

uint8_t key[2] = {0};


/** 
 * @brief 按键初始化
 * @param None
 * @retval None
 */
void key_init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	
	
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);
	
	
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_5;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_Init(GPIOC,&GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOA,&GPIO_InitStruct);
}



/**
 * @brief 按键扫描
 * @param None
 * @retval None
 */
void key_scan(void)
{
	static uint8_t flag[2] = {0};
	uint8_t value[2];
	uint8_t i;
	
	value[0] = GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_5);
	value[1] = GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_15);
	
	for(i=0;i<2;i++)
	{
		if(flag[i] == 0 && value[i] == 0)
		{
			flag[i] = 1;
		}
		if(flag[i] == 1 && value[i] == 1)
		{
			key[i] = 1;
			flag[i] = 0;
		}
	}
}

