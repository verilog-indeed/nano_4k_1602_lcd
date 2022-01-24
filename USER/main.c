/*
 * *****************************************************************************************
 *
 * 		Copyright (C) 2014-2021 Gowin Semiconductor Technology Co.,Ltd.
 * 		
 * @file			main.c
 * @author		Embedded Development Team
 * @version		V1.x.x
 * @date			2021-01-01 09:00:00
 * @brief			Main program body.
 ******************************************************************************************
 */

// RS E D4-D7
// O4 O5 O0-O3
/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdbool.h>
#include "lcd_hd44780.h"


/* Declarations ------------------------------------------------------------------*/

/* Functions ------------------------------------------------------------------*/
int main(void) {
	SystemInit();	//Initializes system
	LCD_Init();		//Initializes LCD
	while (true) {
		delay_ms(100);
		LCD_WriteChar('Y');
		delay_ms(100);
		LCD_WriteChar('u');
		delay_ms(100);
		LCD_WriteChar('m');
		delay_ms(100);
		LCD_WriteChar('i');
		delay_ms(100);
		delay_ms(1000);

		LCD_LineSelect(1);
		LCD_WriteChar('D');
		LCD_WriteChar('i');
		LCD_WriteChar('h');
		LCD_WriteChar('i');
		LCD_WriteChar('a');
		delay_ms(600);


		for	(int i = 0; i < 16; i++)	{
			LCD_DisplayShift(true);
			delay_ms(40);
		}

		delay_ms(1000);
		for	(int i = 0; i < 25; i++)	{
			LCD_DisplayShift(false);
			delay_ms(40);
		}
		LCD_Clear();
	}
}



