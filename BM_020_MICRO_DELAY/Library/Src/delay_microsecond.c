/*
 * delay_microsecond.c
 *
 *  Created on: May 19, 2022
 *      Author: hp
 */

#include "delay_microsecond.h"

uint32_t del_counter = 0;

void micro_delay(uint32_t us){
	tim_config();
	while(del_counter < us);
	i = 0;
}

void milli_delay(uint32_t ms){
	micro_delay(ms * 100);
}

void tim_config(){
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->PSC = 9;
	TIM7->ARR = 23;
	TIM7->CR1 |= TIM_CR1_CEN;

	TIM7->DIER |= TIM_DIER_UIE;
	NVIC_EnableIRQ(TIM7_IRQn);
}

void TIM7_IRQHandler(void) {		// Timer Interrupt helping in delay
	del_counter++;
	TIM7->SR &= ~TIM_SR_UIF;
}
