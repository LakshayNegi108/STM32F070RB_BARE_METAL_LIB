/*
 * BML_GPIO.c
 *
 *  Created on: Feb 18, 2022
 *      Author: hp
 */

#include "BML_GPIO.h"
#include <stdint.h>

uint32_t PINPOS_2B[16] = { //PIN POSITION MAPPER ARRAY FOR SETTING MODDER REGISTER
		(0x00),				// PIN0
				(0x02),		//
				(0x04), 	//
				(0x06), 	//
				(0x08), 	//
				(0x0A), 	//
				(0x0C), 	//
				(0x0E),		// PIN7
				(0x10),				// PIN8
				(0x12), 	//
				(0x14), 	//
				(0x16), 	//
				(0x18), 	//
				(0x1A), 	//
				(0x1C), 	//
				(0x1E), 	// PIN15

		};

/**********************Enable clock Function*************************************/
void gpio_clk_en(GPIO_TypeDef *port) {
	if (port == GPIOA) {
		GPIOA_CLK_EN;
	} else if (port == GPIOB) {
		GPIOB_CLK_EN;
	} else if (port == GPIOC) {
		GPIOC_CLK_EN;
	} else if (port == GPIOD) {
		GPIOD_CLK_EN;
	} else {
		GPIOF_CLK_EN;
	}

}
/**********************************************************************************/

/********************GPIO Configuration Functions**********************************/
void config_gpio(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode,
		uint32_t pinSpeed, uint32_t pinPUPD) {

	gpio_clk_en(port);
	gpio_moder(port, pinNumber, pinMode);
	gpio_speed(port, pinNumber, pinSpeed);
	gpio_PUPD(port, pinNumber, pinPUPD);
}

void config_gpio_input(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode, uint32_t pinPUPD) {
	gpio_clk_en(port);
	gpio_moder(port, pinNumber, pinMode);
	gpio_PUPD(port, pinNumber, pinPUPD);
}

void gpio_moder(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode) {			// Config the mode
	port->MODER |= (pinMode << PINPOS_2B[pinNumber]);								// IN/OP/Alternate/ANALOG
}

void gpio_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed) {		// Config the speed
	port->OSPEEDR |= (pinSpeed << PINPOS_2B[pinNumber]);							// LOW/MED/HIGH
}

void gpio_PUPD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinPUPD) {			// ENABLE/DISABLE
	port->PUPDR |= (pinPUPD << PINPOS_2B[pinNumber]);								// PULL-UP/PULL-DOWN
}

/************************************************************************************/

/************************GPIO OPERATION FUNCTION*************************************/
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state) {
	if (state) {
		port->BSRR = (1 << pinNumber);
	} else {
		port->BSRR = (1 << (pinNumber + 16));
	}
}

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber) {
	port->ODR ^= (1 << pinNumber);
}

uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber){
//	uint32_t flag;
//	if((port->IDR & (1 << pinNumber)) != (uint32_t)0x00){
//		flag = 0x01;
//	}
//	else{
//		flag = 0x00;
//	}
	uint8_t flag;
	flag = (uint8_t)((port->IDR >> pinNumber) & 0x00000001);
	return flag;
}
/**************************************************************************************/

/*******************************INTERRUPT CONFIGURATION*********************************/
