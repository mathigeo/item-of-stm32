#include "system.h"  
#include "systick.h"
#include "stepper.h"

int main(void)
{		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	stepper_init(71,99);
	while(1)
	{
		stepper_pulse(3200);
		delay_ms(1000);
	} 
}

