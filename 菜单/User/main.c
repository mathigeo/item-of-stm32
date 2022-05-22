#include "system.h"  
#include "systick.h"
#include "oled.h"
#include "menu.h"
#include "key.h"



int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	OLED_Init();
	key_init();
	while(1)
	{
		main_menu();
		key_scan();
	} 
}

