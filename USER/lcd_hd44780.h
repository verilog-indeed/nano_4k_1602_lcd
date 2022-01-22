/*
 * lcd_hd44780.h
 *
 *  Created on: 22 Jan 2022
 *      Author: trashcan
 */

#ifndef __LCD_HD44780_H_
#define __LCD_HD44780_H_

#include "gw1ns4c.h"

//----Change these three lines depending on which GPIO you actually connected to your LCD
//D7-D4 which serves both D7-D4 then D3-D0 alternately in 4-bit mode
#define LCD_4BIT_DATA  (GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_1 | GPIO_Pin_0)
#define LCD_ENABLE  GPIO_Pin_5
#define LCD_REGISTER_SEL  GPIO_Pin_4
//--------------------------------------------------------------------------------


// E RS D7-D4
// O5 O4 O3-O0
#define LCD_6BIT_VECTOR  (LCD_ENABLE | LCD_REGISTER_SEL | LCD_4BIT_DATA)

/**
 * Set register select high to tap into the LCD Data Register (DR)
 */
void LCD_SetDataMode();

/**
 * Set register select low to tap into the LCD Instruction Register (IR)
 */
void LCD_SetInstructionMode();

/**
 * Momentarily blinks the Enable to high to let data flow into LCD, then disables it right afterwards
 * */
void LCD_NibbleTransaction();
void LCD_WriteChar(char c);
void delay_ms(__IO uint32_t delay_ms);


#endif /* __LCD_HD44780_H_ */
