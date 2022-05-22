#ifndef _MPUEXTI_H
#define _MPUEXTI_H

#include "system.h" 
#include "mpu6050.h"
#include "inv_mpu.h"

/**
 * @brief 
 * @param 
 * @retval 
 */
typedef struct 
{
	float pitch; 	//俯仰角
	float roll;		//横滚角
	float yaw;		//偏航角
	short gyrox; 	//x角速度
	short gyroy;	//y角速度
	short gyroz;	//z角速度
	short accx;		//x角加速度
	short accy;		//y角加速度
	short accz;		//z角加速度
}MPU6050_T;


extern MPU6050_T mpudata;

void MPU6050_EXTI_Init(void);


#endif //_MPUEXTI_H







