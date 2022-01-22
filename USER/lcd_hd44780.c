/*
 * lcd_hd44780.c
 *
 *  Created on: 21 Jan 2022
 *      Author: Dhia Zerrari
 */

// RS E D4-D7
// O4 O5 O0-O3
/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include "lcd_hd44780.h"
#include "gpio_wrapper.h"

void LCD_SetDataMode()	{
	writeBit(LCD_REGISTER_SEL, true);
}

void LCD_SetInstructionMode()	{
	writeBit(LCD_REGISTER_SEL, false);
}


void LCD_NibbleTransaction()	{
	writeBit(LCD_ENABLE, true); //Enable LCD and start receiving nibble
	delay_ms(1);
	writeBit(LCD_ENABLE, false); //Disable LCD
}

void LCD_WriteChar(char c) {
	LCD_SetDataMode();

	int dataVector = (c & 0xF0) >> 4; //isolate upper nibble
	writeVector(LCD_4BIT_DATA, dataVector); //write upper nibble on data bus (D7-D4)
	LCD_NibbleTransaction();

	dataVector = c & 0x0F; //isolate lower nibble
	writeVector(LCD_4BIT_DATA, dataVector); //write lower nibble on data bus (D3-D0)
	LCD_NibbleTransaction();
}

//delay ms
void delay_ms(__IO uint32_t delay_ms) {
	for (delay_ms = (SystemCoreClock >> 13) * delay_ms; delay_ms != 0;
			delay_ms--)
		;
}

