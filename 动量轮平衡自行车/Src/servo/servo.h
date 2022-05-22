#ifndef __SERVO_H
#define __SERVO_H

#include "stm32f10x.h"

void servo_angle(uint16_t angle);
void servo_init(uint16_t psc,uint16_t arr);


#endif //__SERVO_H




