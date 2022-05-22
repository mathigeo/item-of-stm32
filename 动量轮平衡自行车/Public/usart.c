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
 * @brief USART1��ʼ������
 * @param bound ������
 * @retval None
 */
void usart_init(u32 bound)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	

	
	// �򿪴��� GPIO ��ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	// �򿪴��������ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
	
	
	
	// �� USART Tx �� GPIO ����Ϊ���츴��ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	// �� USART Rx �� GPIO ����Ϊ��������ģʽ
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	
	// ���ò�����
	USART_InitStructure.USART_BaudRate = bound;
	// ���� �������ֳ�
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	// ����ֹͣλ
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	// ����У��λ
	USART_InitStructure.USART_Parity = USART_Parity_No;
	// ����Ӳ��������
	USART_InitStructure.USART_HardwareFlowControl =USART_HardwareFlowControl_None;
	// ���ù���ģʽ���շ�һ��
	USART_InitStructure.USART_Mode = USART_Mode_Rx|USART_Mode_Tx;
	// ��ɴ��ڵĳ�ʼ������
	USART_Init(USART1, &USART_InitStructure);
	
	
	
	
	/* ���� USART Ϊ�ж�Դ */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	/* �������ȼ�Ϊ 1 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	/* �����ȼ�Ϊ 1 */
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	/* ʹ���ж� */
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	/* ��ʼ������ NVIC */
	NVIC_Init(&NVIC_InitStructure);	
	
	
	
	// ʹ�ܴ��ڽ����ж�
	USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);
	// ʹ�ܴ���
	USART_Cmd(USART1,ENABLE);
}



/**
 * @brief ����һ���ֽ�
 * @param pUSARTx ���ڽṹ��
 * @param ch �ֽ�����
 * @retval None
 */
void usart_sendByte( USART_TypeDef * pUSARTx, uint8_t ch)
{
	/* ����һ���ֽ����ݵ� USART */
	USART_SendData(pUSARTx,ch);

	/* �ȴ��������ݼĴ���Ϊ�� */
	while (USART_GetFlagStatus(pUSARTx, USART_FLAG_TXE) == RESET);
}




/**
 * @brief ����һ���ַ���
 * @param pUSARTx ���ڽṹ��
 * @param str �ַ���
 * @retval None
 */
void usart_sendString(USART_TypeDef * pUSARTx, char *str)
{
	unsigned int k=0;
	do{
		usart_sendByte( pUSARTx, *(str + k) );
		k++;
	}while (*(str + k)!='\0');

	/* �ȴ�������� */
	while (USART_GetFlagStatus(pUSARTx,USART_FLAG_TC)==RESET) {
	}
}



/**
 * @brief USART1�жϺ���
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
