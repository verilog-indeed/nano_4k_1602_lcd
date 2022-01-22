/*
 * gpio_wrapper.h
 *
 *  Created on: 22 Jan 2022
 *      Author: trashcan
 */

#include <stdbool.h>

#ifndef __GPIO_WRAPPER_H_
#define __GPIO_WRAPPER_H_

void writeBit(uint32_t pins, bool value);

void writeVector(uint32_t pins, uint32_t value);


#endif /* __GPIO_WRAPPER_H_ */
