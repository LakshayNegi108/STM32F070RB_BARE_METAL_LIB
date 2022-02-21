#include "main.h"
#include "BML_GPIO.h"

#define my_led_port 	GPIOA
#define my_led_pin		5

int main(void) {
//	GPIO_TYPE LED_ON_STM;		// make struct type variable for gpio to configure different modes
//
//	LED_ON_STM.port = GPIOA;	// *port -> (*(addr_of_GPIOA))
//	LED_ON_STM.pin = 5;			// pin -> pinNumber
//
//	config_gpio(LED_ON_STM.port, LED_ON_STM.pin, OUTPUT_MODE, High_SPEED, DI_PUPD);	// config the port
//	gpio_toggle(LED_ON_STM.port, LED_ON_STM.pin);			// toggle function
	uint32_t i = 0;

	config_gpio(my_led_port, my_led_pin, OUTPUT_MODE, LOW_SPEED, DI_PUPD);

	while (1) {
		//	gpio_toggle(my_led_port, my_led_pin);
		gpio_write(my_led_port, my_led_pin, LOW);
		for (i = 0; i < 100000; i++);
		gpio_write(my_led_port, my_led_pin, HIGH);
		for (i = 0; i < 1000000; i++);

	}
}
