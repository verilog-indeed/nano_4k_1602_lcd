// RS E D4-D7
// O4 O5 O0-O3
/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "lcd_hd44780.h"


/* Declarations ------------------------------------------------------------------*/

char message[16]; //Buffer for string formatting before printing
int smileyGlyph[8] = {0b00000,
					  0b01010,
					  0b00000,
					  0b00000,
					  0b10001,
					  0b01110,
					  0b00000,
					  0b00000};

int sadGlyph[8] = {0b10001,
		  	  	   0b00000,
				   0b00100,
				   0b00000,
				   0b01110,
				   0b10001,
				   0b00000,
				   0b00000};

/* Functions ------------------------------------------------------------------*/
int main(void) {
	SystemInit();	//Initializes system
	LCD_Init();		//Initializes LCD
	LCD_CreateCustomChar(0, smileyGlyph);
	LCD_WriteString("No School Day: ");
	LCD_WriteChar(0);
	int counter = 0xA0;
	while (true) {
		LCD_LineSelect(1);
		snprintf(message, 16, "%s #%d", "  ", counter);
		LCD_WriteString(message);
		for (int i = 0; i < 40; i++)	{
			LCD_DisplayShift(true);
			delay_ms(1);
		}
		delay_ms(300);
		counter++;
	}
}


