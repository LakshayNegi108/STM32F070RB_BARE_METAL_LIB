#include <BML_DRIVER.h>
#include "main.h"

uint16_t ticks = 0;

void delay_ms(uint16_t ms){
	timer_EN(TIM6);
	ticks = 0;
	while(ticks < ms);
	timer_DI(TIM6);
}

int main(void) {

	uart_print_config();

	timer_config(TIM6, 0, 7499);

	timer_IT_EN(TIM6);
//	timer6_7_CR1(TIM6, 0, 0, 1, 0);
	NVIC_EnableIRQ(TIM6_IRQn);
	gpio_config(PORTA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD);
	APP_DEBUG("Working\n\r");
	timer_EN(TIM6);

	while (1) {

		if(ticks%200 == 0){
		APP_DEBUG("Timer value: %d\n\r", ticks);
		}
		if(ticks%1000 == 0){
			APP_DEBUG("1 sec has passed\n\r");
			gpio_toggle(PORTA, 5);
			ticks = 0;
		}

//		delay_ms(1000);

	}
}

void TIM6_IRQHandler(void){
	ticks++;
	TIM6->SR &= ~TIM_SR_UIF;
}
