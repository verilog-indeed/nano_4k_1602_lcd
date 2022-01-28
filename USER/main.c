/*
 * Example code for showing the LCD library in action
 * Prints a counter of how many days there have been without school, if days last 300ms that is.
 *
 */

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
	LCD_CreateCustomChar(0, smileyGlyph);	//send custom character data to LCD to make a smiley at index 0
	LCD_WriteString("No School Day: ");
	LCD_WriteChar(0);	//Write the aforementioned smiley character
	int counter = 0;
	while (true) {
		LCD_LineSelect(1);	//Cursor back to beginning of second line
		snprintf(message, 16, "%s #%d", "  ", counter);	//print empty space followed by count number and the hash sign
		LCD_WriteString(message);
		for (int i = 0; i < 40; i++)	{ //shift entire display to the right until it wraps back around where it started
			LCD_DisplayShift(true);
			LCD_DelayMS(1);
		}
		LCD_DelayMS(300);
		counter++;
	}
}


