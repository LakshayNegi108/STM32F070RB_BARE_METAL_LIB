#include <BML_DRIVER.h>
#include "main.h"



int main(void) {

	uart_print_config();
	// Peripheral clock/Desired clk = PSC x ARR = Value

//	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;			// Enable clock for timer 6
//	gpio_config(PORTA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
//
//	TIM6->ARR = 500;		//fill auto-reload register with value 500
//	TIM6->PSC = 12000;		// fill prescale value register with value 12000
//	TIM6->CR1 |= TIM_CR1_CEN;	// Enable counter to count the value

	timer_config(TIM6, 12000, 500);
	timer_EN(TIM6);
	gpio_config(PORTA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
	print("Working\n\r");

	while (1) {

		if (timer_cnt_val(TIM6) == 250) {
			APP_DEBUG("Timer value: %d\n\r", timer_cnt_val(TIM6));
//			TIM6->EGR |= 1;
			timer_EVENT(TIM6);
			gpio_toggle(PORTA, 5);
		}

	}
}
