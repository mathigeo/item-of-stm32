#include "menu.h"

//声明
extern key_table_t table[];


/**
 * @brief 菜单
 * @param None
 * @retval None
 */
void main_menu(void)
{
	static uint8_t index = 0;
	
	//确认
	if(key[0] == 1)
	{
		index = table[index].enter;
		key[0] = 0;
	}
	//下一个
	if(key[1] == 1)
	{
		index = table[index].down;
		key[1] = 0;		
	}
	
	if(table[index].operation != NULL)
	{
		table[index].operation();
	}
}


/**
 * @brief 欢迎界面
 * @param None
 * @retval None
 */
void start_gui(void)
{
	OLED_ShowString(1,1,"user help:      ",0);
	OLED_ShowString(2,1,"key1 -> down    ",0);
	OLED_ShowString(3,1,"key0 -> ensure  ",0);
	OLED_ShowString(4,1,"continue...     ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a(void)
{
	OLED_ShowString(1,1,"weater          ",1);
	OLED_ShowString(2,1,"music           ",0);
	OLED_ShowString(3,1,"device          ",0);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b(void)
{
	OLED_ShowString(1,1,"weater          ",0);
	OLED_ShowString(2,1,"music           ",1);
	OLED_ShowString(3,1,"device          ",0);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c(void)
{
	OLED_ShowString(1,1,"weater          ",0);
	OLED_ShowString(2,1,"music           ",0);
	OLED_ShowString(3,1,"device          ",1);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_d(void)
{
	OLED_ShowString(1,1,"weater          ",0);
	OLED_ShowString(2,1,"music           ",0);
	OLED_ShowString(3,1,"device          ",0);
	OLED_ShowString(4,1,"return          ",1);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_a(void)
{
	OLED_ShowString(1,1,"HangZhou        ",1);
	OLED_ShowString(2,1,"BeiJing         ",0);
	OLED_ShowString(3,1,"ShangHai        ",0);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_b(void)
{
	OLED_ShowString(1,1,"HangZhou        ",0);
	OLED_ShowString(2,1,"BeiJing         ",1);
	OLED_ShowString(3,1,"ShangHai        ",0);
	OLED_ShowString(4,1,"return          ",0);
}




/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_c(void)
{
	OLED_ShowString(1,1,"HangZhou        ",0);
	OLED_ShowString(2,1,"BeiJing         ",0);
	OLED_ShowString(3,1,"ShangHai        ",1);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_d(void)
{
	OLED_ShowString(1,1,"HangZhou        ",0);
	OLED_ShowString(2,1,"BeiJing         ",0);
	OLED_ShowString(3,1,"ShangHai        ",0);
	OLED_ShowString(4,1,"return          ",1);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_a(void)
{
	OLED_ShowString(1,1,"WindyHill       ",1);
	OLED_ShowString(2,1,"New Boy         ",0);
	OLED_ShowString(3,1,"Kiss The Rain   ",0);
	OLED_ShowString(4,1,"return          ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_b(void)
{
	OLED_ShowString(1,1,"WindyHill       ",0);
	OLED_ShowString(2,1,"New Boy         ",1);
	OLED_ShowString(3,1,"Kiss The Rain   ",0);
	OLED_ShowString(4,1,"return          ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_c(void)
{
	OLED_ShowString(1,1,"WindyHill       ",0);
	OLED_ShowString(2,1,"New Boy         ",0);
	OLED_ShowString(3,1,"Kiss The Rain   ",1);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_d(void)
{
	OLED_ShowString(1,1,"WindyHill       ",0);
	OLED_ShowString(2,1,"New Boy         ",0);
	OLED_ShowString(3,1,"Kiss The Rain   ",0);
	OLED_ShowString(4,1,"return          ",1);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_a(void)
{
	OLED_ShowString(1,1,"WiFi            ",1);
	OLED_ShowString(2,1,"Sound           ",0);
	OLED_ShowString(3,1,"Version         ",0);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_b(void)
{
	OLED_ShowString(1,1,"WiFi            ",0);
	OLED_ShowString(2,1,"Sound           ",1);
	OLED_ShowString(3,1,"Version         ",0);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_c(void)
{
	OLED_ShowString(1,1,"WiFi            ",0);
	OLED_ShowString(2,1,"Sound           ",0);
	OLED_ShowString(3,1,"Version         ",1);
	OLED_ShowString(4,1,"return          ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_d(void)
{
	OLED_ShowString(1,1,"WiFi            ",0);
	OLED_ShowString(2,1,"Sound           ",0);
	OLED_ShowString(3,1,"Version         ",0);
	OLED_ShowString(4,1,"return          ",1);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_a_(void)
{
	OLED_ShowString(1,1,"HangZhou        ",0);
	OLED_ShowString(2,1,"winding         ",0);
	OLED_ShowString(3,1,"2020.5.5        ",0);
	OLED_ShowString(4,1,"25C             ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_b_(void)
{
	OLED_ShowString(1,1,"BeiJing         ",0);
	OLED_ShowString(2,1,"rain            ",0);
	OLED_ShowString(3,1,"2020.5.5        ",0);
	OLED_ShowString(4,1,"25C             ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_a_c_(void)
{
	OLED_ShowString(1,1,"ShangHai        ",0);
	OLED_ShowString(2,1,"snowing         ",0);
	OLED_ShowString(3,1,"2020.5.5        ",0);
	OLED_ShowString(4,1,"25C             ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_a_(void)
{
	OLED_ShowString(1,1,"play WindyHill  ",0);
	OLED_ShowString(2,1,"                ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_b_(void)
{
	OLED_ShowString(1,1,"play New Boy    ",0);
	OLED_ShowString(2,1,"                ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_b_c_(void)
{
	OLED_ShowString(1,1,"play Kiss The Ra",0);
	OLED_ShowString(2,1,"in              ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_a_(void)
{
	OLED_ShowString(1,1,"WiFi imformation",0);
	OLED_ShowString(2,1,"                ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}


/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_b_(void)
{
	OLED_ShowString(1,1,"Sound:%40       ",0);
	OLED_ShowString(2,1,"                ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}



/**
 * @brief 项
 * @param None
 * @retval None
 */
void gui_c_c_(void)
{
	OLED_ShowString(1,1,"Version 1.3     ",0);
	OLED_ShowString(2,1,"                ",0);
	OLED_ShowString(3,1,"                ",0);
	OLED_ShowString(4,1,"                ",0);
}


/**
 * @brief 菜单列表
 */
key_table_t table[]=
{
	//第0层
	{0,1,1,start_gui},
	
	
	//第一层
	{1,2,5,gui_a},
	{2,3,9,gui_b},
	{3,4,13,gui_c},
	{4,1,0,gui_d},
	
	
	//第二层
	{5,6,17,gui_a_a},
	{6,7,18,gui_a_b},
	{7,8,19,gui_a_c},
	{8,5,1,gui_a_d},
	
	{9,10,20,gui_b_a},
	{10,11,21,gui_b_b},
	{11,12,22,gui_b_c},
	{12,9,2,gui_b_d},

	{13,14,23,gui_c_a},
	{14,15,24,gui_c_b},
	{15,16,25,gui_c_c},
	{16,13,3,gui_c_d},
	
	
	//第三层
	{17,17,5,gui_a_a_},
	{18,18,6,gui_a_b_},
	{19,19,7,gui_a_c_},

	{20,20,9,gui_b_a_},
	{21,21,10,gui_b_b_},
	{22,22,11,gui_b_c_},

	{23,23,13,gui_c_a_},
	{24,24,14,gui_c_b_},
	{25,25,15,gui_c_c_},
};


