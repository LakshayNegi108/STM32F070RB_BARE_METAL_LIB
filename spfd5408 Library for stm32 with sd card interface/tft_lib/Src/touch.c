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

void GPIO_SetAnalog(GPIO_TypeDef *GPIOx, uint16_t pin) {

	gpio_clk_en(GPIOx);
	gpio_moder(GPIOx, pin, ANALOG_MODE);

	if ((GPIOx == GPIOA) && (pin == 1)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
	} else if ((GPIOx == GPIOA) && (pin == 4)) {
		ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
	}

}

uint16_t Touch_GetX(void) {
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);
//	GPIO_SetAnalog(A5_PORT, A5_PIN);
//	gpio_config(TS_PORT_YP, TS_PIN_YP, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 1);

	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 1);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 0);

	delay_ms(100);

//	uint32_t x = ADC_Measure(TS_ADCCH_YP);
//	uint16_t x_arr[2];
	uint16_t x = 0;
	adc_read(&x, 1);
	adc_stop();
//	x = x_arr[1];

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return x;
}

/**
 * \brief Gets the y-Coordinate raw value
 *
 * \param	none
 *
 * \return uint16_t		raw adc value
 */
uint16_t Touch_GetY(void) {
	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 1);
	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);
	GPIO_SetAnalog(A5_PORT, A5_PIN);
//	gpio_config(TS_PORT_XM, TS_PIN_XM, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);

	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 0);
	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 1);

	delay_ms(100);

//	uint16_t y = ADC_Measure(TS_ADCCH_XM);
	uint16_t y_arr[2];
	uint16_t y = 0;
	adc_read(&y_arr, 2);
	y = y_arr[1];

	GPIO_SetOutput(TS_PORT_YP, TS_PIN_YP, 0);
	GPIO_SetOutput(TS_PORT_XM, TS_PIN_XM, 0);

	return y;
}

void Touch_Get(uint16_t *arr) {
	GPIO_SetAnalog(TS_PORT_YP, TS_PIN_YP);
	GPIO_SetAnalog(TS_PORT_XM, TS_PIN_XM);
//	gpio_config(TS_PORT_XM, TS_PIN_XM, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);

	GPIO_SetOutput(TS_PORT_YM, TS_PIN_YM, 1);
	GPIO_SetOutput(TS_PORT_XP, TS_PIN_XP, 1);

	delay_ms(100);

//	uint16_t y = ADC_Measure(TS_ADCCH_XM);
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
	uint16_t x = 0, y = 0;
	if (c == 'x' || c == 'X') {
//		x = adc_arr_val[0] ;
		x = map(adc_arr_val[0], TS_Xmin, TS_Xmax, 0, 1023);
		return x;
	} else if (c == 'y' || c == 'Y') {
//		y = adc_arr_val[1];
		y = map(adc_arr_val[1], TS_Ymin, TS_Ymax, 0, 1023);
		return y;
	}
}
