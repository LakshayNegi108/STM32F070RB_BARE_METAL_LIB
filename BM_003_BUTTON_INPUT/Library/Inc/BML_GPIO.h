/*
 * BML_GPIO.h
 *
 *  Created on: Feb 18, 2022
 *      Author: hp
 */

#ifndef INC_BML_GPIO_H_
#define INC_BML_GPIO_H_

#include "stm32f070xb.h"

#define LOW			0
#define HIGH		1

#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD
#define PORTE		GPIOE
#define PORTF		GPIOF

// PIN FUNCTION MODES
#define INPUT_MODE					((uint32_t)0x00U)
#define OUTPUT_MODE					((uint32_t)0x01U)
#define ALT_MODE					((uint32_t)0x02U)
#define ANALOG_MODE					((uint32_t)0x03U)

// PIN SPEED MODES
#define LOW_SPEED					((uint32_t)0x00U)
#define MEDIUM_SPEED				((uint32_t)0x01U)
#define HIGH_SPEED					((uint32_t)0x02U)

// ENABLE-DISABLE PULL-UP/PULL-DOWN
#define DI_PUPD						((uint32_t)0x00U)
#define EN_PU						((uint32_t)0x01U)
#define EN_PD						((uint32_t)0x02U)

// ENABLE CLOCK FOR DIFFERENT PORTS
#define GPIOA_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOAEN)
#define GPIOB_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOBEN)
#define GPIOC_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOCEN)
#define GPIOD_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIODEN)
//#define GPIOE_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOEEN)
#define GPIOF_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOFEN)

#define SYSCFG_CLK_EN				(RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN)

typedef struct{
	GPIO_TypeDef *port;
	uint32_t	pin;
	uint32_t	mode;
	uint32_t	pull;
	uint32_t	speed;
	uint32_t	alt_func;
} GPIO_TYPE;

void gpio_clk_en(GPIO_TypeDef *port);

void config_gpio(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode, uint32_t pinSpeed, uint32_t pinPUPD);

void config_gpio_input(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode, uint32_t pinPUPD);

void gpio_moder(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode);

void gpio_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode);

void gpio_PUPD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinPUPD);

void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state);

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);

uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber);

void gpio_IT_config(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t edge_sel);

#endif /* INC_BML_GPIO_H_ */
