#include "HX711.h"
#include "systick.h"


u32 HX711_Buffer;
u32 Weight_Maopi;
s32 Weight_Shiwu;
u8 Flag_Error = 0;


/**
 * @brief 校准参数
 * @note 因为不同的传感器特性曲线不是很一致，
	因此，每一个传感器需要矫正这里这个参数才能使测量值很准确。
	当发现测试出来的重量偏大时，增加该数值。
	如果测试出来的重量偏小时，减小改数值。
	该值可以为小数
 */
#define GapValue 106.5


/**
 * @brief HX711引脚初始化
 * @param None
 * @retval None
 */
void Init_HX711pin(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
	
	//使能PF端口时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 

	
	
	//HX711_SCK
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 
	GPIO_Init(GPIOB, &GPIO_InitStructure);					
	
	
	
	//HX711_DOUT
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_Init(GPIOB, &GPIO_InitStructure);  
	
	
	
	GPIO_SetBits(GPIOB,GPIO_Pin_0);					
}




/**
 * @brief 读取HX711
 * @param None
 * @retval 返回的读数
 * @note 增益128
 */
u32 HX711_Read(void)	
{
	unsigned long count; 
	unsigned char i; 
  	HX711_DOUT=1; 
	delay_us(1);
  	HX711_SCK=0; 
  	count=0; 
  	while(HX711_DOUT); 
  	for(i=0;i<24;i++)
	{ 
	  	HX711_SCK=1; 
	  	count=count<<1; 
		delay_us(1);
		HX711_SCK=0; 
	  	if(HX711_DOUT)
			count++; 
		delay_us(1);
	} 
 	HX711_SCK=1; 
	//第25个脉冲下降沿来时，转换数据
    count=count^0x800000;
	delay_us(1);
	HX711_SCK=0;  
	return(count);
}


/**
 * @brief 获取毛皮重量
 * @param None
 * @retval None
 */
void Get_Maopi(void)
{
	Weight_Maopi = HX711_Read();	
} 



/**
 * @brief 称重
 * @param None
 * @retval None
 * @note 因为不同的传感器特性曲线不一样，
	因此，每一个传感器需要矫正这里的GapValue这个除数。
	当发现测试出来的重量偏大时，增加该数值。
	如果测试出来的重量偏小时，减小改数值。
 */
void Get_Weight(void)
{
	HX711_Buffer = HX711_Read();
	if(HX711_Buffer > Weight_Maopi)			
	{
		Weight_Shiwu = HX711_Buffer;
		//获取实物的AD采样数值。
		Weight_Shiwu = Weight_Shiwu - Weight_Maopi;				
		//计算实物的实际重量
		Weight_Shiwu = (s32)((float)Weight_Shiwu/GapValue); 	
	}	
}
