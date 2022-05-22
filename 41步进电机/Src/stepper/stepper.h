#ifndef __STEPPER_H 
#define __STEPPER_H

#include "stm32f10x.h"

void stepper_init(uint16_t psc,uint16_t arr);
void stepper_pulse(int32_t n);

#endif //__STEPPER_H




