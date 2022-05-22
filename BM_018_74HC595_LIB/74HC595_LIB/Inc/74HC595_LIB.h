/*
 * 74HC595_LIB.h
 *
 *  Created on: Mar 31, 2022
 *      Author: hp
 */
#include "BML_DRIVER.h"

#ifndef INC_74HC595_LIB_H_
#define INC_74HC595_LIB_H_

#define DATA_PORT	PORTC
#define LATCH_PORT	PORTC
#define CLOCK_PORT	PORTC

#define DATA_PIN	8
#define LATCH_PIN	6
#define	CLOCK_PIN	5

#define	MSBFIRST	1
#define	LSBFIRST	0


void shift_register_setup();
void shift_register_clock();
unsigned int get_byte(char b, unsigned int pos);
void bit_to_pin(char c, unsigned int pos, GPIO_TypeDef *port, uint32_t pinNumber);
uint8_t reverse(uint8_t b);
void shift_out(unsigned char value, uint8_t MSBF_LSBF);

#endif /* INC_74HC595_LIB_H_ */
