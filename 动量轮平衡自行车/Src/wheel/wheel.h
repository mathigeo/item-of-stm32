#ifndef __WHEEL_H 
#define __WHEEL_H

#include "stm32f10x.h"

void wheel_load(int v);
void wheel_driver_init(void);
void wheel_pwm_init(u16 psc,u16 arr);

#endif //__WHEEL_H




