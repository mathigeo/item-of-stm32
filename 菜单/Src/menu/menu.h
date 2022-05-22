#ifndef __MENU_H 
#define __MENU_H

#include "oled.h"
#include "key.h"

#ifndef NULL
#define NULL ((void *)0)
#endif


/**
 * @brief �����ṹ��
 */
typedef struct 
{
	uint8_t current;			//��ǰ��������
	uint8_t down;				//�·�������
	uint8_t enter;				//ȷ��������
	void (*operation)(void);	//����
}key_table_t;


void main_menu(void);


#endif //__MENU_H




