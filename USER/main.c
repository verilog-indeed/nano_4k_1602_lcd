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

/* Declarations ------------------------------------------------------------------*/
void LCDInit(void);
void delay_ms(__IO uint32_t delay_ms);
void GPIOInit(void);
void LCD_PrintTest();

/* Functions ------------------------------------------------------------------*/
int main(void) {
	SystemInit();	//Initializes system
	GPIOInit();		//Initializes GPIO
	LCDInit();		//Initializes LCD
	LCD_PrintTest();
	while (1) {
	}
}

void LCD_Reset()	{
	delay_ms(70);
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 1
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //IR5 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(6);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble
	delay_ms(1);

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(2);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0 for 4-bit mode
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //IR5 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(2);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble
}

/**
 * Performs the LCD function set
 * 4-bit mode, 5x8 font size, 2 Lines
 * */
void LCD_FunctionSet() {
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0 for 4-bit mode
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //IR5 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	//TODO: delay microseconds routine??
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	//IR0, IR1 are Don't Cares
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR2 is 0
	GPIO_SetBit(GPIO0, GPIO_Pin_3); //IR3 is 1

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD
}

void LCD_Clear() {
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR5 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_SetBit(GPIO0, GPIO_Pin_0); //IR0 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR1 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR2 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR3 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD
}

void LCD_DisplayOn() {
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR5 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_SetBit(GPIO0, GPIO_Pin_0); //IR0 is 1 for blinking cursor
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //IR1 is 1 to make cursor visible
	GPIO_SetBit(GPIO0, GPIO_Pin_2); //IR2 is 1 to turn on display
	GPIO_SetBit(GPIO0, GPIO_Pin_3); //IR3 is 1

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD
}

void LCD_EntryModeSet() {
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR5 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR0 is 0 for no shifting (??)
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //IR1 is 1 for increment cursor mode (Left to Right mode)
	GPIO_SetBit(GPIO0, GPIO_Pin_2); //IR2 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR3 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD
}

void LCDInit(void) {
	LCD_Reset();
	LCD_FunctionSet();
	LCD_Clear();
	LCD_DisplayOn();
	LCD_EntryModeSet();
}

void LCD_SetDDRAM_Address() {
	//test: address 000 0000
	GPIO_ResetBit(GPIO0, GPIO_Pin_4); //RS to instruction mode

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR4 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR5 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR6 is 0
	GPIO_SetBit(GPIO0, GPIO_Pin_3); //IR7 is 1

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_ResetBit(GPIO0, GPIO_Pin_0); //IR0 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //IR1 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //IR2 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //IR3 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD
}

void LCD_Write() {
	//Test: character 'S' ASCII = 0101 0011
	GPIO_SetBit(GPIO0, GPIO_Pin_4); //RS to data mode

	GPIO_SetBit(GPIO0, GPIO_Pin_0); //D4 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_1); //D5 is 0
	GPIO_SetBit(GPIO0, GPIO_Pin_2); //D6 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //D7 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading high order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD to prepare next nibble

	GPIO_SetBit(GPIO0, GPIO_Pin_0); //D0 is 1
	GPIO_SetBit(GPIO0, GPIO_Pin_1); //D1 is 1
	GPIO_ResetBit(GPIO0, GPIO_Pin_2); //D2 is 0
	GPIO_ResetBit(GPIO0, GPIO_Pin_3); //D3 is 0

	GPIO_SetBit(GPIO0, GPIO_Pin_5); //Enable LCD and start reading low order nibble
	delay_ms(1);
	GPIO_ResetBit(GPIO0, GPIO_Pin_5); //Disable LCD

}

void LCD_PrintTest() {
	LCD_SetDDRAM_Address();
	delay_ms(1);
	LCD_Write();
}


//Initializes GPIO
void GPIOInit(void) {
	for (uint32_t pin = GPIO_Pin_0; pin <= GPIO_Pin_5; pin = pin << 1) {
		GPIO_InitTypeDef GPIO_InitType;

		GPIO_InitType.GPIO_Pin = pin;
		GPIO_InitType.GPIO_Mode = GPIO_Mode_OUT;
		GPIO_InitType.GPIO_Int = GPIO_Int_Disable;

		GPIO_Init(GPIO0, &GPIO_InitType);

		GPIO_ResetBit(GPIO0, pin);
	}
}

//delay ms
void delay_ms(__IO uint32_t delay_ms) {
	for (delay_ms = (SystemCoreClock >> 13) * delay_ms; delay_ms != 0;
			delay_ms--)
		;
}
