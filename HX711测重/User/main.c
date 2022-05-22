#include "stm32f10x.h"
#include "systick.h"
#include "HX711.h"
#include "usart.h"



int main(void)
{			
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	USART_Config(9600);	 //串口初始化为9600
	printf("%s--%d\r\n",__FILE__,__LINE__);
	Init_HX711pin();
	printf("%s--%d\r\n",__FILE__,__LINE__);
	Get_Maopi();				//称毛皮重量
	printf("%s--%d\r\n",__FILE__,__LINE__);
	delay_ms(1000);
	printf("%s--%d\r\n",__FILE__,__LINE__);
	delay_ms(1000);
	printf("%s--%d\r\n",__FILE__,__LINE__);
	Get_Maopi();				//重新获取毛皮重量
	printf("%s--%d\r\n",__FILE__,__LINE__);
	while(1)
	{
		Get_Weight();
		printf("净重量 = %d g\r\n",Weight_Shiwu); //打印 
	}
}






