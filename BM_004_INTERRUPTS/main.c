#include "main.h"
#include "BML_GPIO.h"

#define my_led_port 	GPIOA
#define my_led_pin		5

#define my_button_port	GPIOC
#define my_button_pin	13

uint8_t flag = 0;

int main(void) {

	uint32_t i = 0;
	gpio_config(GPIOA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
	gpio_IT_config(GPIOC, 13, RISING_EDGE);
	gpio_IT_EN(13, EXTI4_15_IRQn);

	while (1) {
		if (flag == 0) {
			gpio_toggle(GPIOA, 5);
			for (i = 0; i < 500000; i++)
				;
		} else if (flag == 1) {
			gpio_toggle(GPIOA, 5);
			for (i = 0; i < 1000000; i++)
				;
		} else if (flag == 2) {
			gpio_toggle(GPIOA, 5);
			for (i = 0; i < 2000000; i++)
				;
		}
	}
}

void EXTI4_15_IRQHandler(void) {

	if(flag == 2)	flag = 0;
	else			flag++;

	gpio_IT_CLR(13);
}
