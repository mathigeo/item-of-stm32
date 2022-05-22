#include "adc.h"


ADC_dat_t adc_dat = {0};


/**
 * @brief ADC初始化
 * @param None
 * @retval None
 */
void adcx_init(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	ADC_InitTypeDef ADC_InitStructure;
	NVIC_InitTypeDef NVIC_InitStructure;
	
	
	
	// 打开 ADC IO 端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
	// 打开 ADC 时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE );	
	
	
	
	// 配置 ADC IO 引脚模式
	// 必须为模拟输入
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA,&GPIO_InitStructure);	
	
	

	// ADC 模式配置
	// 只使用一个 ADC，属于独立模式
	ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
	// 禁止扫描模式，多通道才要，单通道不需要
	ADC_InitStructure.ADC_ScanConvMode = DISABLE ;
	// 连续转换模式
	ADC_InitStructure.ADC_ContinuousConvMode = ENABLE;
	// 不用外部触发转换，软件开启即可
	ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	// 转换结果右对齐
	ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
	// 转换通道 1 个
	ADC_InitStructure.ADC_NbrOfChannel = 1;
	// 初始化 ADC
	ADC_Init(ADC1, &ADC_InitStructure);
	
	
	
	//中断优先级配置
	NVIC_InitStructure.NVIC_IRQChannel = ADC1_2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);	
	
	
	
	// 配置 ADC时钟CLK2的8分频即9MHz
	RCC_ADCCLKConfig(RCC_PCLK2_Div8);
	// 配置 ADC 通道转换顺序为 1，第一个转换，采样时间为 55.5 个时钟周期
	ADC_RegularChannelConfig(ADC1, ADC_Channel_4,1,ADC_SampleTime_55Cycles5);
	// ADC 转换结束产生中断，在中断服务程序中读取转换值
	ADC_ITConfig(ADC1,ADC_IT_EOC,ENABLE);
	// 开启 ADC ，并开始转换
	ADC_Cmd(ADC1, ENABLE);
	// 初始化 ADC 
	ADC_ResetCalibration(ADC1);
	// 等待校准寄存器初始化完成
	while (ADC_GetResetCalibrationStatus(ADC1));
	// ADC 开始校准
	ADC_StartCalibration(ADC1);
	// 等待校准完成
	while (ADC_GetCalibrationStatus(ADC1));
	// 由于没有采用外部触发，所以使用软件触发 ADC 转换
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);
}


/**
 * @brief ADC中断服务函数
 * @param None
 * @retval None
 */
void ADC1_2_IRQHandler(void)
{
	if (ADC_GetITStatus(ADC1,ADC_IT_EOC)==SET) 
	{
		// 读取 ADC 的转换值
		adc_dat.raw = ADC_GetConversionValue(ADC1);
		adc_dat.vol = 11.09f*(3.3f*(float)(adc_dat.raw)/(float)0x0fff);
	}
	ADC_ClearITPendingBit(ADC1,ADC_IT_EOC);
}




