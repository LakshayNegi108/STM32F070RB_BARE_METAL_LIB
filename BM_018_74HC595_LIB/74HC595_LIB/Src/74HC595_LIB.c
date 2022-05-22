/*
 * 74HC595_LIB.c
 *
 *  Created on: Mar 31, 2022
 *      Author: hp
 */
#include "74HC595_LIB.h"

/**
 * Setup the shift register pins.
 */
void shift_register_setup() {
	gpio_config(DATA_PORT, DATA_PIN, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(LATCH_PORT, LATCH_PIN, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(CLOCK_PORT, CLOCK_PIN, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
}

/**
 * Sends a clock pulse to the shift register.
 */
void shift_register_clock() {
	gpio_write(CLOCK_PORT, CLOCK_PIN, HIGH);
	gpio_toggle(CLOCK_PORT, CLOCK_PIN);
}

/**
 * Get a single bit from a byte.
 */
unsigned int get_byte(char b, unsigned int pos) {
	return (b & (1 << pos));
}

/**
 * Puts the desired bit into a pin. It's used to get the bits in a char
 * to send to the LCD.
 */
void bit_to_pin(char c, unsigned int pos, GPIO_TypeDef *port, uint32_t pinNumber) {
	if (get_byte(c, pos)) {
		gpio_write(port, pinNumber, HIGH);
		for(uint8_t i = 0; i < 50; i++);
	} else {
		gpio_write(port, pinNumber, LOW);
		for(uint8_t i = 0; i < 50; i++);
	}
}

uint8_t reverse(uint8_t b) {
   b = (b & 0xF0) >> 4 | (b & 0x0F) << 4;
   b = (b & 0xCC) >> 2 | (b & 0x33) << 2;
   b = (b & 0xAA) >> 1 | (b & 0x55) << 1;
   return b;
}

/**
 * Shifts out a value to the shift register.
 */
void shift_out(unsigned char value, uint8_t MSBF_LSBF) {

	if(MSBF_LSBF == 0){
		value = reverse(value);
	}

	shift_register_setup();
	shift_register_clock();
	// Latch LOW to start shifting data.
	gpio_write(LATCH_PORT, LATCH_PIN, LOW);
	for(uint8_t i = 0; i < 50; i++);

	for (unsigned int i = 0; i < 8; i++) {
		// Shift every bit.
		bit_to_pin(value, i, DATA_PORT, DATA_PIN);
		shift_register_clock();
		for(uint8_t i = 0; i < 50; i++);
	}

	// Latch the data.
	gpio_write(LATCH_PORT, LATCH_PIN, HIGH);
	for(uint8_t i = 0; i < 50; i++);
	gpio_write(LATCH_PORT, LATCH_PIN, LOW);
	for(uint8_t i = 0; i < 50; i++);
}


