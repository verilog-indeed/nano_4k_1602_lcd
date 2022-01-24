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

/**
 * Performs the LCD function set
 * is8BitMode: 0 for 4-bit bus, 1 for 8-bit bus
 * is2LineMode: 0 for single line LCD, 1 for two line LCD
 * is510DotFont: 0 for 5x8 dot character font, 1 for 5x10 dot character font
 * */
void LCD_FunctionSet(bool is8BitMode, bool is2LineMode, bool is510DotFont) {
	LCD_SetInstructionMode(); //RS to instruction mode
	int instructionVector = 0b00100000 | (is8BitMode << 4) | (is2LineMode << 3) | (is510DotFont << 2);
	LCD_WriteByteToNibbleBus(instructionVector);
}

//TODO explain what displayShiftON is doing?
/**
 * Set cursor move direction whenever receiving new characters
 * and set display shift (??)
 * isIncrement: 0 means cursor position is decremented and thus goes right-to-left
 * 				1 means cursor position is incremented and thus goes left-to-right
 *
 * */
void LCD_EntryModeSet(bool isIncrement, bool displayShiftON) {
	LCD_SetInstructionMode();
	int instructionVector = 0b00000100 | (isIncrement << 1) | (displayShiftON);
	LCD_WriteByteToNibbleBus(instructionVector);
}

/**
 * Initializes GPIO pins used by the LCD in Output mode
 * */
void LCD_GPIOInit()	{
	GPIO_InitTypeDef GPIO_InitType;

	GPIO_InitType.GPIO_Pin = LCD_6BIT_VECTOR;
	GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

	GPIO_Init(GPIO0, &GPIO_InitType);

	GPIO_ResetBit(GPIO0, LCD_6BIT_VECTOR);
}

/**
 * Manually resets the LCD regardless of current state/internal reset failure
 * see fig. 24, page 46 of the HD44780 manual
 * This reset should be followed by the rest of the init procedure (function set, entry mode etc)
 * */
void LCD_Reset()	{
	delay_ms(100); //wait for LCD power on if cold boot
	LCD_SetInstructionMode();

	int instructionVector = 0b0011;
	writeVector(LCD_4BIT_DATA, instructionVector);
	LCD_NibbleTransaction();
	delay_ms(1);

	//reread same data (0011) as per procedure described in manual
	LCD_NibbleTransaction();
	delay_ms(1);
	LCD_NibbleTransaction();

	instructionVector = 0b0010;
	writeVector(LCD_4BIT_DATA, instructionVector);
	LCD_NibbleTransaction();
}

/**
 * Clears display, resets address counter to 0
 * */
void LCD_Clear() {
	LCD_SetInstructionMode();
	int instructionVector = 0b00000001;
	LCD_WriteByteToNibbleBus(instructionVector);
}


/**
 * Shifts cursor without modifying text
 * rightShift: if 0, shift to the left, if 1 shift to the right
 * */
void LCD_CursorShift(bool rightShift)	{
	LCD_SetInstructionMode();
	int instructionVector = 0b00010000 | (rightShift << 2);
	LCD_WriteByteToNibbleBus(instructionVector);
}

/**
 * Shift entire display without modifying text
 * rightShift: if 0, shift to the left, if 1 shift to the right
 * */
void LCD_DisplayShift(bool rightShift)	{
	LCD_SetInstructionMode();
	int instructionVector = 0b00011000 | (rightShift << 2);
	LCD_WriteByteToNibbleBus(instructionVector);
}


void LCD_SetDataMode()	{
	writeBit(LCD_REGISTER_SEL, true);
}

void LCD_SetInstructionMode()	{
	writeBit(LCD_REGISTER_SEL, false);
}

void LCD_NibbleTransaction()	{
	writeBit(LCD_ENABLE, true); //Enable LCD and start receiving nibble
	delay_ms(5);
	writeBit(LCD_ENABLE, false); //Disable LCD
}

void LCD_SetDisplayRAMAddress(int address)	{
	LCD_SetInstructionMode();
	int instructionVector = 0b10000000 | (address & 0x7F);
	LCD_WriteByteToNibbleBus(instructionVector);
}

void LCD_LineSelect(int line)	{
	LCD_SetDisplayRAMAddress(line == 0? 0x0: 0x40);
}

void LCD_DisplayEnable(bool displayON, bool cursorON, bool cursorBlinks) {
	LCD_SetInstructionMode();
	int instructionVector = 0b00001000 | (displayON << 2) | (cursorON << 1) | (cursorBlinks);
	LCD_WriteByteToNibbleBus(instructionVector);
}

void LCD_Init() {
	//Cycle one instruction/data transfer to avoid confusing the nibbles later on
	LCD_NibbleTransaction();

	LCD_GPIOInit();
	LCD_Reset();
	LCD_FunctionSet(false, true, false);
	LCD_Clear();
	LCD_DisplayEnable(true, true, true);
	LCD_EntryModeSet(true, false);
}


void LCD_WriteChar(char c) {
	LCD_SetDataMode();
	int dataVector = c;
	LCD_WriteByteToNibbleBus(dataVector);
}

/**
 * Writes byte long instruction/data into two separate 4-bit writes
 * */
void LCD_WriteByteToNibbleBus(int byte)	{
	writeVector(LCD_4BIT_DATA, ((byte & 0xF0) >> 4));
	//TODO: delay microseconds routine??
	LCD_NibbleTransaction(); //send B7-B4 through D7-D4

	writeVector(LCD_4BIT_DATA, (byte & 0x0F));
	LCD_NibbleTransaction(); //send B3-B0 through D7-D4
}

//delay ms
void delay_ms(__IO uint32_t delay_ms) {
	for (delay_ms = (SystemCoreClock >> 13) * delay_ms; delay_ms != 0;
			delay_ms--)
		;
}

