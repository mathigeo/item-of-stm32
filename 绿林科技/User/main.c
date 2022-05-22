#include "system.h"  
#include "systick.h"
#include "oled.h"


int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	while(1)
	{
		oledPrint(1,1,"hello world");
	} 
}

