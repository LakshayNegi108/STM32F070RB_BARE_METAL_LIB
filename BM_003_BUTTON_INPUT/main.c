#include "main.h"
#include "BML_GPIO.h"

#define my_led_port 	GPIOA
#define my_led_pin		5

#define my_button_port	GPIOC
#define my_button_pin	13

int main(void) {

	uint32_t i = 0;
	config_gpio(my_led_port, my_led_pin, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
	config_gpio(my_button_port, my_button_pin, INPUT_MODE, LOW_SPEED, EN_PU);
	gpio_write(my_led_port, my_led_pin, LOW);

	while (1) {
		uint8_t flag = gpio_read(my_button_port, my_button_pin);
		for(i = 0; i < 100000; i++);
		if (!flag) {
			gpio_toggle(my_led_port, my_led_pin);
		}
	}
}
