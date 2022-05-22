#ifndef __ENCODER_H 
#define __ENCODER_H 

#include "stm32f10x.h"

extern int wheel_speed;

void encoder_TIM4_Init(void);
int read_encoder(void);

#endif 



