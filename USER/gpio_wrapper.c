/*
 * gpio_wrapper.c
 *
 *  Created on: 21 Jan 2022
 *      Author: Dhia Zerrari
 */

/* Includes ------------------------------------------------------------------*/
#include "gw1ns4c.h"
#include <stdbool.h>

/**
 * "pins" is a group of GPIO_Pin_X constants OR'd together
 * to obtain the appropriate pin vector, writes same value to all pins
*/
void writeBit(uint32_t pins, bool value) {
	if (value)	{
		GPIO_ResetBit(GPIO0, pins);
	} else {
		GPIO_SetBit(GPIO0, pins);
	}
}

/**
 * "pins" is a group of GPIO_Pin_X constants OR'd together to
 * obtain the appropriate pin vector, assumes little endianness
*/
void writeVector(uint32_t pins, uint32_t value) {
	for (int i = value; i < 16; i++)	{
		int bitmask = (0x1 << i) & pins;
		if (bitmask == 0x0) continue; //pin at this position doesn't need to be written
		writeBit(bitmask, (bool) (bitmask & value));
	}
}

