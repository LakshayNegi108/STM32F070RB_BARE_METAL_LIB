/*
 * touch.c
 *
 *  Created on: 29-May-2022
 *      Author: hp
 */

#include "touch.h"

void insert_sort(int array[], uint8_t size) {
	uint8_t j;
	int save;

	for (int i = 1; i < size; i++) {
		save = array[i];
		for (j = i; j >= 1 && save < array[j - 1]; j--)
			array[j] = array[j - 1];
		array[j] = save;
	}
}

void adc_Init(void) {
	adc_en();
	adc_config(sample_time_7, CONT_off, SCANDIR_off, AUTOFF_off, WAIT_off,
	DISCEN_off, OVRMOD_off);

}

void Touch_Begin(void) {
//	ADCx_MspInit();
	adc_Init();
}

void GPIO_SetOutput(GPIO_TypeDef *GPIOx, uint16_t pin, int val) {
	GPIOx->MODER &= ~(0x03 << (2 * pin));
	gpio_config(GPIOx, pin, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_write(GPIOx, pin, val);
}

void GPIO_SetInput(GPIO_TypeDef *GPIOx, uint16_t pin, int val) {
	GPIOx->MODER &= ~(0x03 << (2 * pin));
	gpio_config(GPIOx, pin, INPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_write(GPIOx, pin, val);
}

void GPIO_SetAnalog(GPIO_TypeDef *GPIOx, uint16_t pin) {

	GPIOx->MODER &= ~(0x03 << (2 * pin));
	gpio_clk_en(GPIOx);
	gpio_moder(GPIOx, pin, ANALOG_MODE);

	if ((GPIOx == GPIOA) && (pin == 1)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
	} else if ((GPIOx == GPIOA) && (pin == 4)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
	} else if ((GPIOx == GPIOB) && (pin == 0)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL8;
	} else if ((GPIOx == GPIOC) && (pin == 0)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL10;
	} else if ((GPIOx == GPIOC) && (pin == 1)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL11;
	}

}

uint16_t Touch_GetX(void) {
	GPIO_SetInput(TS_PORT_YM, TS_PIN_YM, 0);
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);

	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 1);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	uint16_t adcVal[5];
	uint16_t x = 0;

	for (int i = 0; i < 5; i++) {
		adc_read(&x, 1);
		adcVal[i] = x;
		adc_stop();
	}

	insert_sort(adcVal, 5);
	for (int i = 0; i < 5; i++) {
		adc_read(&x, 1);
		if (adcVal[3] == x)
			adcVal[i] = x;
		else
			adcVal[i];
		adc_stop();
	}

	x = adcVal[3];

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return x;
}

uint16_t Touch_GetY(void) {

	GPIO_SetInput(TS_PORT_XP, TS_PIN_XP, 0);
	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 1);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 0);

	uint16_t adcVal[5];
	uint16_t y = 0;

	for (int i = 0; i < 5; i++) {
		adc_read(&y, 1);
		adcVal[i] = y;
		adc_stop();
	}
	insert_sort(adcVal, 5);
	for (int i = 0; i < 5; i++) {
		adc_read(&y, 1);
		if (adcVal[3] == y)
			adcVal[i] = y;
		else
			adcVal[i];
		adc_stop();
	}

	y = adcVal[3];

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return y;
}

uint16_t Touch_Pressure(void) {
	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 0);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 1);

	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);

	uint16_t z1[5];
	uint16_t z2[5];
	uint16_t pos[2];

	for (int i = 0; i < 5; i++) {
		adc_read(&pos, 2);
		z1[i] = pos[0];
		z2[i] = pos[1];
		adc_stop();
	}

	insert_sort(z1, 5);
	insert_sort(z2, 5);
//	for (int i = 0; i < 5; i++) {
//		adc_read(&x, 1);
//		if (adcVal[3] == x)
//			adcVal[i] = x;
//		else
//			adcVal[i];
//	}

	return (z2[3] - z1[3]);
}

void Touch_Get(uint16_t *arr) {
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);
	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);

	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 1);
	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 1);

//	delay_ms(100);

	uint16_t ADC_VAL[2];
	for (int i = 0; i < 12; i++) {
		adc_read(&ADC_VAL, 2);
		adc_stop();
		arr_X[i] = ADC_VAL[0];
		arr_Y[i] = ADC_VAL[1];
	}
	insert_sort(arr_X, 12);
	insert_sort(arr_Y, 12);

	*arr = arr_X[6];
	*(arr + 1) = arr_Y[6];

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);
}



uint16_t TOUCH_VAL(char c) {
	Touch_Get(&adc_arr_val[0]);
	uint16_t x = 0, y = 0, z = 0;
	if (c == 'x' || c == 'X') {
//		x = adc_arr_val[0] ;
		x = map(adc_arr_val[0], TS_Xmin, TS_Xmax, 0, 1023);
		return x;
	} else if (c == 'y' || c == 'Y') {
//		y = adc_arr_val[1];
		y = map(adc_arr_val[1], TS_Ymin, TS_Ymax, 0, 1023);
		return y;
	} else if (c == 'z' || c == 'Z') {
		z = adc_arr_val[1] - adc_arr_val[0];
		z = map(adc_arr_val[1] - adc_arr_val[0], 1700, 3500, 100, 1000);
		return z;
	}
}
