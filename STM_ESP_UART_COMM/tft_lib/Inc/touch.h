/*
 * touch.h
 *
 *  Created on: 29-May-2022
 *      Author: hp
 */

#ifndef INC_TOUCH_H_
#define INC_TOUCH_H_

#include "main.h"
#include "BML_DRIVER.h"
#include "st7783.h"

#define TS_PIN_XP	10
#define TS_PIN_XM	4
#define TS_PIN_YP	1
#define TS_PIN_YM	8

#define TS_PORT_XP	GPIOB
#define TS_PORT_XM	GPIOA
#define TS_PORT_YP	GPIOA
#define TS_PORT_YM	GPIOA

#define A5_PORT		GPIOC
#define A5_PIN		0

#define TS_ADCCH_XM	GPIOA
#define TS_ADCCH_YP	GPIOA
#define TS_ADC_PORT GPIOA

#define TS_Xmin		0
#define TS_Xmax		1600
#define TS_Ymin		1300
#define TS_Ymax		1900

uint16_t arr_X[12];
uint16_t arr_Y[12];
uint16_t adc_arr_val[2];

void insert_sort(int array[], uint8_t size);
void adc_Init(void);
void Touch_Begin(void);
void GPIO_SetOutput(GPIO_TypeDef *GPIOx, uint16_t pin, int val);
void GPIO_SetAnalog(GPIO_TypeDef *GPIOx, uint16_t pin);
uint16_t Touch_GetX(void);
uint16_t Touch_GetY(void);
void Touch_Get(uint16_t *arr);
#endif /* INC_TOUCH_H_ */
