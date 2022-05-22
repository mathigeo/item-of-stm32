#include "usart.h"		 


/**
 * @brief  Retargets the C library printf function to the USART.
 * @param  None
 * @retval None
 */
int fputc(int ch, FILE *f)
{      
	while((USART1->SR&0X40)==0){}; 
    USART1->DR = (u8) ch;      
	return ch;
}




/**
 * @brief USART1初始化函数
 * @param bound 波特率
 * @retval None
 */
void usart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	
	// 打开串口 GPIO 的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// 打开串口外设的时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	
	// 将 USART Tx 的 GPIO 配置为推挽复用模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// 将 USART Rx 的 GPIO 配置为浮空输入模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	// 配置波特率
	USART_InitStructure.USART_BaudRate = bound;
	// 配置 针数据字长
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// 配置停止位
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// 配置校验位
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// 配置硬件流控制
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	// 配置工作模式，收发一起
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	// 完成串口的初始化配置
	USART_Init(USART1, &USART_InitStructure);
	
	
	
	
	/* 配置 USART 为中断源 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	/* 抢断优先级为 1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* 子优先级为 1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* 使能中断 */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* 初始化配置 NVIC */
	NVIC_Init(&NVIC_InitStructure);	
	
	
	
	// 使能串口接收中断
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	// 使能串口
	USART_Cmd(USART1,ENABLE);
}



/**
 * @brief 发送一个字节
 * @param pUSARTx 串口结构体
 * @param ch 字节数据
 * @retval None
 */
void usart_sendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* 发送一个字节数据到 USART */
	USART_SendData(pUSARTx,ch);

	/* 等待发送数据寄存器为空 */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}




/**
 * @brief 发送一个字符串
 * @param pUSARTx 串口结构体
 * @param str 字符串
 * @retval None
 */
void usart_sendString(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do{
		usart_sendByte( pUSARTx, *(str + k) );
		k++;
	}while (*(str + k)!='\0');

	/* 等待发送完成 */
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {
	}
}



/**
 * @brief USART1中断函数
 * @param None
 * @retval None
 */
void USART1_IRQHandler(void)
{
	uint8_t temp;
	if (USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET) 
	{
		temp = USART_ReceiveData(USART1);
		USART_SendData(USART1,temp);
	}
}
