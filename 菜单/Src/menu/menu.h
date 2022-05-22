#ifndef __MENU_H 
#define __MENU_H

#include "oled.h"
#include "key.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


/**
 * @brief 按键结构体
 */
typedef struct 
{
	uint8_t current;			//当前组索引号
	uint8_t down;				//下翻索引号
	uint8_t enter;				//确认索引号
	void (*operation)(void);	//动作
}key_table_t;


void main_menu(void);


#endif //__MENU_H




