#ifndef __ADC_H 
#define __ADC_H

#include "stm32f10x.h"

/**
 * @brief ADCÊý¾Ý
 */
typedef struct 
{
	uint16_t raw;
	float vol;
}ADC_dat_t;


extern ADC_dat_t adc_dat;


void adcx_init(void);


#endif /*__ADC_H*/




