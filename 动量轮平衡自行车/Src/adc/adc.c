#include "adc.h"


ADC_dat_t adc_dat = {0};


/**
 * @brief ADC��ʼ��
 * @param None
 * @retval None
 */
void adcx_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	
	// �� ADC IO �˿�ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	// �� ADC ʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE );	
	
	
	
	// ���� ADC IO ����ģʽ
	// ����Ϊģ������
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	

	// ADC ģʽ����
	// ֻʹ��һ�� ADC�����ڶ���ģʽ
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	// ��ֹɨ��ģʽ����ͨ����Ҫ����ͨ������Ҫ
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
	// ����ת��ģʽ
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// �����ⲿ����ת���������������
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// ת������Ҷ���
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// ת��ͨ�� 1 ��
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	// ��ʼ�� ADC
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	
	//�ж����ȼ�����
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	
	
	// ���� ADCʱ��CLK2��8��Ƶ��9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	// ���� ADC ͨ��ת��˳��Ϊ 1����һ��ת��������ʱ��Ϊ 55.5 ��ʱ������
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,1,ADC_SampleTime_55Cycles5);
	// ADC ת�����������жϣ����жϷ�������ж�ȡת��ֵ
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	// ���� ADC ������ʼת��
	ADC_Cmd(ADC1, ENABLE);
	// ��ʼ�� ADC 
	ADC_ResetCalibration(ADC1);
	// �ȴ�У׼�Ĵ�����ʼ�����
	while (ADC_GetResetCalibrationStatus(ADC1));
	// ADC ��ʼУ׼
	ADC_StartCalibration(ADC1);
	// �ȴ�У׼���
	while (ADC_GetCalibrationStatus(ADC1));
	// ����û�в����ⲿ����������ʹ��������� ADC ת��
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


/**
 * @brief ADC�жϷ�����
 * @param None
 * @retval None
 */
void ADC1_2_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) 
	{
		// ��ȡ ADC ��ת��ֵ
		adc_dat.raw = ADC_GetConversionValue(ADC1);
		adc_dat.vol = 11.09f*(3.3f*(float)(adc_dat.raw)/(float)0x0fff);
	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}




