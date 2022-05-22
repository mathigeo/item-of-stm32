#ifndef __N20_H 
#define __N20_H

#include "stm32f10x.h"

#define n20_ahead()		(GPIO_SetBits(GPIOA,GPIO_Pin_5),\
						GPIO_ResetBits(GPIOA,GPIO_Pin_6)) 
	
#define n20_back()		(GPIO_ResetBits(GPIOA,GPIO_Pin_5),\
						GPIO_SetBits(GPIOA,GPIO_Pin_6)) 
						
#define n20_stop()		(GPIO_ResetBits(GPIOA,GPIO_Pin_5),\
						GPIO_ResetBits(GPIOA,GPIO_Pin_6))

#define n20_setPWM(x)		TIM_SetCompare3(TIM3,x)	

void n20_driver_init(void);
void n20_pwm_init(void);

#endif //__N20_H


