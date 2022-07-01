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

#define TS_PIN_XP	8
#define TS_PIN_XM	4
#define TS_PIN_YP	0
#define TS_PIN_YM	7

#define TS_PORT_XP	GPIOA	//P8 - PA8
#define TS_PORT_XM	GPIOA	//A2 - PA4
#define TS_PORT_YP	GPIOB	//A3 - PB0
#define TS_PORT_YM	GPIOC	//P9 - PC7

//=============== Rotation - 0 ================//
// 150, 650			600,650			 900, 500 //
//										      //
// 200, 800							 1000, 500//
//											  //
// 250, 700			650, 550		 1000, 450//
//											  //
// 200, 400							1000, 300 //
//											  //
// 340, 320			600, 200		1000, 150 //
//============================================//
#define TS_ADCCH_XM	GPIOA
#define TS_ADCCH_YP	GPIOA
#define TS_ADC_PORT GPIOA

#define TS_Xmin		0
#define TS_Xmax		1300
#define TS_Ymin		3000
#define TS_Ymax		4095

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
uint16_t Touch_Val(char c);
uint16_t Touch_Pressure(void);
#endif /* INC_TOUCH_H_ */

