#ifndef __KEY_H
#define __KEY_H

#include "stm32f10x.h"

extern uint8_t key[2];

void key_init(void);
void key_scan(void);

#endif //__KEY_H






