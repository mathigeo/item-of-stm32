#ifndef __CONTROL_H
#define __CONTROL_H

#include "stm32f10x.h"
#include "encoder.h"
#include "mpu_exti.h"
#include "wheel.h"

void main_ctrl(void);
float vertical(float target,float value,float dvalue);
float velocity(float target,float value);
void lowpass(float *p);

#endif //__CONTROL_H




