#include <BML_DRIVER.h>
#include "main.h"

int main(void) {

	uart_print_config();
	ticks_timer();			//Initialize timer with configuration to 1 milli second
	gpio_config(PORTA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
	APP_DEBUG("Working\n\r");

	while (1) {
		APP_DEBUG("Timer value: %d\n\r", ticks_val());
		if(ticks_val()%200 == 0){
			APP_DEBUG("200ms Passed\n\r")
		}
		if(ticks_val() > 900){
			APP_DEBUG("1 sec has passed\n\r");
			gpio_toggle(PORTA, 5);
			ticks_reset();

//================ General Delay function used here =============================//
//		gpio_toggle(PORTA, 5);
//		APP_DEBUG("1 sec has passed\n\r");
//		delay_ms(1000);
//===============================================================================//
	}
}
}


