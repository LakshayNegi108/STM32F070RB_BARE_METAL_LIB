#include <BML_DRIVER.h>
#include "main.h"

#define ADC0_PORT	GPIOA
#define ADC0_PIN	0
#define ADC1_PORT	GPIOA
#define ADC1_PIN	1
#define ADC4_PORT	GPIOC
#define ADC4_PIN	14

uint16_t ADC_result[3];
uint8_t i = 0;

void adc_save_val(uint16_t *arr, uint8_t len) {
	if (i > (len - 1)) {
		i = 0;
		*(arr + i) = ADC1->DR;
	} else {
		*(arr + i) = ADC1->DR;
	}
	i++;
}

int main(void) {
	RCC_CONFIG_48MHZ();
	uart_print_config(9600, 48);
	ticks_timer(48);
	adc_en();
	APP_DEBUG("Running\n\r");

	adc_IT_config(end_of_conv_flag);

	gpio_config(ADC0_PORT, ADC0_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(ADC1_PORT, ADC1_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(ADC4_PORT, ADC4_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);

	adc_config(sample_time_7, CONT_on, SCANDIR_off, AUTOFF_off, WAIT_off,
	DISCEN_off, OVRMOD_off);

	adc_start();
	while (1) {
		if (ticks_val() > 1000) {
			APP_DEBUG("ADC value: %d", ADC_result[0]);
			APP_DEBUG(" ,%d", ADC_result[1]);
			APP_DEBUG(" ,%d\n\r", ADC_result[2]);
//			sys_delayMs(1000);
			ticks_reset();
		}
	}
}

void ADC1_IRQHandler() {
	if (ADC_EOC_FLAG) {
		adc_save_val(ADC_result, 3);
	}
}

void sys_delayMs(int n) {
    int i;
    /* Configure SysTick */
    SysTick->LOAD = 16600;  /* reload with number of clocks per millisecond */
    SysTick->VAL = 0;       /* clear current value register */
    SysTick->CTRL = 0x5;    /* Enable the timer */
//    SysTick_Config(SystemCoreClock/1000);

    for(i = 0; i < n; i++) {
        while((SysTick->CTRL & 0x10000) == 0) /* wait until the COUNTFLAG is set */
            { }
    }
    SysTick->CTRL = 0;      /* Stop the timer (Enable = 0) */
}

