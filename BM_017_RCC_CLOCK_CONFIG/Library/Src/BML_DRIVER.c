/*
 * BML_GPIO.c
 *
 *  Created on: Feb 18, 2022
 *      Author: hp
 */

#include "BML_DRIVER.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>

uint32_t PINPOS_2B[16] = { //PIN POSITION MAPPER ARRAY FOR SETTING MODDER REGISTER
		(0x00),				// PIN0
				(0x02),		//
				(0x04), 	//
				(0x06), 	//
				(0x08), 	//
				(0x0A), 	//
				(0x0C), 	//
				(0x0E),		// PIN7
				(0x10),				// PIN8
				(0x12), 	//
				(0x14), 	//
				(0x16), 	//
				(0x18), 	//
				(0x1A), 	//
				(0x1C), 	//
				(0x1E), 	// PIN15

		};

uint32_t AF[8] = { (0x00), (0x01), (0x02), (0x03), (0x04), (0x05), (0x06),
		(0x07) };

uint16_t ticks = 0;

/**********************Enable clock Function*************************************/
void gpio_clk_en(GPIO_TypeDef *port) {
	if (port == GPIOA) {
		GPIOA_CLK_EN;
	} else if (port == GPIOB) {
		GPIOB_CLK_EN;
	} else if (port == GPIOC) {
		GPIOC_CLK_EN;
	} else if (port == GPIOD) {
		GPIOD_CLK_EN;
	} else {
		GPIOF_CLK_EN;
	}
}
/**********************************************************************************/

/********************GPIO Configuration Functions**********************************/
void gpio_config(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode,
		uint32_t pinSpeed, uint32_t pinPUPD, uint32_t PHPL_OD) {

	if (pinMode == OUTPUT_MODE) {
		gpio_clk_en(port);
		gpio_moder(port, pinNumber, pinMode);
		gpio_speed(port, pinNumber, pinSpeed);
		gpio_PUPD(port, pinNumber, pinPUPD);
		gpio_PHPL_OD(port, pinNumber, PHPL_OD);
	} else if (pinMode == INPUT_MODE) {
		gpio_clk_en(port);
		gpio_moder(port, pinNumber, pinMode);
		gpio_PUPD(port, pinNumber, pinPUPD);
	} else if (pinMode == ALT_MODE) {
		gpio_clk_en(port);
		gpio_moder(port, pinNumber, pinMode);
		gpio_PUPD(port, pinNumber, pinPUPD);
		gpio_PHPL_OD(port, pinNumber, PHPL_OD);
	} else if (pinMode == ANALOG_MODE) {
		gpio_clk_en(port);
		gpio_moder(port, pinNumber, pinMode);
		adc_chsel(pinNumber);
	}
}

void gpio_moder(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode) {	// Config the mode
	port->MODER |= (pinMode << PINPOS_2B[pinNumber]);// IN/OP/Alternate/ANALOG
}

void gpio_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinSpeed) {// Config the speed
	port->OSPEEDR |= (pinSpeed << PINPOS_2B[pinNumber]);		// LOW/MED/HIGH
}

void gpio_PUPD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinPUPD) {// ENABLE/DISABLE
	port->PUPDR |= (pinPUPD << PINPOS_2B[pinNumber]);		// PULL-UP/PULL-DOWN
}
void gpio_PHPL_OD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t PHPL_OD) {// ENABLE/DISABLE
	port->OTYPER |= (PHPL_OD << pinNumber);	// PUSH-PULL/OPEN DRAIN
}

void gpio_altfn(GPIO_TypeDef *port, uint32_t pinNumber,
		uint32_t alternate_function) {
	if (pinNumber < 8) {
		port->AFR[0] |= (alternate_function << (4 * pinNumber));
	} else {
		port->AFR[1] |= (alternate_function << (4 * (pinNumber - 8)));
	}
}

/************************************************************************************/

/************************GPIO OPERATION FUNCTION*************************************/
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state) {
	if (state) {
		port->BSRR = (1 << pinNumber);
	} else {
		port->BSRR = (1 << (pinNumber + 16));
	}
}

void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber) {
	port->ODR ^= (1 << pinNumber);
}

uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber) {
//	uint32_t flag;
//	if((port->IDR & (1 << pinNumber)) != (uint32_t)0x00){
//		flag = 0x01;
//	}
//	else{
//		flag = 0x00;
//	}
	uint8_t flag;
	flag = (uint8_t) ((port->IDR >> pinNumber) & 0x00000001);
	return flag;
}
/**************************************************************************************/

/*******************************INTERRUPT CONFIGURATION*********************************/
void gpio_IT_config(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t edge) {
	SYSCFG_CLK_EN;
	if (port == GPIOA) {
		switch (pinNumber) {
		case 0:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PA;
			break;
		case 1:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PA;
			break;
		case 2:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PA;
			break;
		case 3:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PA;
			break;
		case 4:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PA;
			break;
		case 5:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PA;
			break;
		case 6:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PA;
			break;
		case 7:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PA;
			break;
		case 8:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PA;
			break;
		case 9:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PA;
			break;
		case 10:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PA;
			break;
		case 11:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PA;
			break;
		case 12:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PA;
			break;
		case 13:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PA;
			break;
		case 14:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PA;
			break;
		case 15:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PA;
			break;
		}	// end of Port A
	} else if (port == GPIOB) {
		switch (pinNumber) {
		case 0:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PB;
			break;
		case 1:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PB;
			break;
		case 2:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PB;
			break;
		case 3:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PB;
			break;
		case 4:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PB;
			break;
		case 5:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PB;
			break;
		case 6:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PB;
			break;
		case 7:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PB;
			break;
		case 8:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PB;
			break;
		case 9:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PB;
			break;
		case 10:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PB;
			break;
		case 11:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PB;
			break;
		case 12:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PB;
			break;
		case 13:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PB;
			break;
		case 14:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PB;
			break;
		case 15:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PB;
			break;
		}	// end of Port B
	} else if (port == GPIOC) {
		switch (pinNumber) {
		case 0:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PC;
			break;
		case 1:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PC;
			break;
		case 2:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PC;
			break;
		case 3:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PC;
			break;
		case 4:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PC;
			break;
		case 5:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PC;
			break;
		case 6:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PC;
			break;
		case 7:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PC;
			break;
		case 8:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PC;
			break;
		case 9:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PC;
			break;
		case 10:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PC;
			break;
		case 11:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PC;
			break;
		case 12:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PC;
			break;
		case 13:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PC;
			break;
		case 14:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PC;
			break;
		case 15:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PC;
			break;
		}	// end of Port C
	} else if (port == GPIOD) {
		switch (pinNumber) {
		case 0:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI0_PD;
			break;
		case 1:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI1_PD;
			break;
		case 2:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI2_PD;
			break;
		case 3:
			SYSCFG->EXTICR[0] = SYSCFG_EXTICR1_EXTI3_PD;
			break;
		case 4:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI4_PD;
			break;
		case 5:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI5_PD;
			break;
		case 6:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI6_PD;
			break;
		case 7:
			SYSCFG->EXTICR[1] = SYSCFG_EXTICR2_EXTI7_PD;
			break;
		case 8:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI8_PD;
			break;
		case 9:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI9_PD;
			break;
		case 10:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI10_PD;
			break;
		case 11:
			SYSCFG->EXTICR[2] = SYSCFG_EXTICR3_EXTI11_PD;
			break;
		case 12:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI12_PD;
			break;
		case 13:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI13_PD;
			break;
		case 14:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI14_PD;
			break;
		case 15:
			SYSCFG->EXTICR[3] = SYSCFG_EXTICR4_EXTI15_PD;
			break;
		}	// end of Port D
	}

	if (edge == RISING_EDGE) {
		EXTI->RTSR |= 1 << pinNumber;
	} else if (edge == FALLING_EDGE) {
		EXTI->FTSR |= 1 << pinNumber;
	} else if (edge == RISING_FALLING_EDGE) {
		EXTI->RTSR |= 1 << pinNumber;
		EXTI->FTSR |= 1 << pinNumber;
	}
}

void gpio_IT_EN(uint32_t pinNumber, IRQn_Type irqNumber) {//Interrupt Enable Function
	EXTI->IMR |= 1 << pinNumber;	//enable interrupt in EXTI
	NVIC_EnableIRQ(irqNumber);		//enable interrupt in NVIC
}

void gpio_IT_DI(uint32_t pinNumber, IRQn_Type irqNumber) {//Interrupt Disable Function
	EXTI->IMR &= ~(1 << pinNumber);	//disable interrupt in EXTI
	NVIC_DisableIRQ(irqNumber);
}

void gpio_IT_SW(uint32_t pinNumber) {			//Interrupt Software generate
	EXTI->SWIER |= 1 << pinNumber;				//need work
}

void gpio_IT_CLR(uint32_t pinNumber) {				//Interrupt clear function
	EXTI->PR |= 1 << pinNumber;		//clear pending register
}

// Also make a GPIO Interrupt Handler function e.g - EXTI4_15_IRQHandler

//*******************************************************************************************//

//************************** UART SERIAL PRINTING *******************************************//

void print(char *msg, ...) {
	char buff[100];
	va_list args;
	va_start(args, msg);
	vsprintf(buff, msg, args);

	for (uint8_t i = 0; i < strlen(msg); i++) {
		USART2->TDR = msg[i];
		while (!(USART2->ISR & USART_ISR_TXE))
			;
	}

}

void uart_print_config(uint32_t baudRate, uint8_t clkSpeed) {

	RCC->APB1ENR |= RCC_APB1ENR_USART2EN;
	gpio_config(GPIOA, 2, ALT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(GPIOA, 3, ALT_MODE, HIGH_SPEED, DI_PUPD, PHPL);

	gpio_altfn(GPIOA, 2, USART2_TX_PA2);
	gpio_altfn(GPIOA, 3, USART2_RX_PA3);

//clkPer / (baudR x 16) = 48MHz / (9600 x 16) = 312.5 = 1388

	if(clkSpeed == 8){
		if(baudRate == 9600)			USART2->BRR = 0x341;

	}else if(clkSpeed == 48){
		if(baudRate == 4800)				USART2->BRR = 0x1388;
		else if(baudRate == 9600)			USART2->BRR = 0x9c4;
	}

	USART2->CR1 |= USART_CR1_RE | USART_CR1_TE | USART_CR1_UE;
}
//*******************************************************************************************//

//************************** TIMER FUNCTIONS ************************************************//

//************************** Basic TIMER FUNCTIONS *******************************//
void timer_config(TIMER_TYPE *tim, uint32_t prescaler_val,
		uint32_t auto_reload_val) {

	if (tim == TIM1) {						// ENable clock for particular timer
		RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	} else if (tim == TIM3) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	} else if (tim == TIM6) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	} else if (tim == TIM7) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
	} else if (tim == TIM14) {
		RCC->APB1ENR |= RCC_APB1ENR_TIM14EN;
	} else if (tim == TIM15) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM15EN;
	} else if (tim == TIM16) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM16EN;
	} else if (tim == TIM17) {
		RCC->APB2ENR |= RCC_APB2ENR_TIM17EN;
	}

	// Peripheral clock/Desired clk = PSC x ARR = Value

	tim->ARR = auto_reload_val;	// fill auto-reload register with value: auto_reload_val
	tim->PSC = prescaler_val;// fill prescale value register with value: prescaler_val

}

void timer_EN(TIMER_TYPE *tim) {
	tim->CR1 |= TIM_CR1_CEN;		// Enable counter to count the value
}

void timer_DI(TIMER_TYPE *tim) {
	tim->CR1 &= ~TIM_CR1_CEN;		// Disable counter to count the value
}

void timer6_7_CR1(TIMER_TYPE *tim, uint8_t AUTO_RELOAD_PREL_EN,	// Function to configure the rest of the timer functions
		uint8_t ONE_PULSE_MODE, uint8_t UPDATE_REQ_SRC, uint8_t UPDATE_DIS) {
	if (AUTO_RELOAD_PREL_EN == 1) {
		tim->CR1 |= TIM_CR1_ARPE;
	}
	if (ONE_PULSE_MODE == 1) {
		tim->CR1 |= TIM_CR1_OPM;
	}
	if (UPDATE_REQ_SRC == 1) {
		tim->CR1 |= TIM_CR1_URS;
	}
	if (UPDATE_DIS == 1) {
		tim->CR1 |= TIM_CR1_UDIS;
	}
}

void timer_EVENT(TIMER_TYPE *tim) {
	tim->EGR |= TIM_EGR_UG;	// Generate software event to reset counter timer
}

uint16_t timer_cnt_val(TIMER_TYPE *tim) {
	uint16_t val = tim->CNT;		// counter register value
	return val;
}

void timer_IT_EN(TIMER_TYPE *tim) {
	tim->DIER |= TIM_DIER_UIE;
}

void ticks_timer(uint8_t clkSpeed) {			// similar to millis
	if(clkSpeed == 8){
	timer_config(TIM6, 0, 7499);//Initialize timer with configuration to 1 milli second
	}
	else if(clkSpeed == 48){
		timer_config(TIM6, 0, 16500);//Initialize timer with configuration to 1 milli second
	}
	timer_IT_EN(TIM6);
	NVIC_EnableIRQ(TIM6_IRQn);
	timer_EN(TIM6);
}
uint16_t ticks_val() {
	return ticks;
}
void ticks_reset() {
	ticks = 0;
}
void TIM6_IRQHandler(void) {		// Timer Interrupt helping in delay
	ticks++;
	TIM6->SR &= ~TIM_SR_UIF;
}

void delay_ms(uint16_t ms) {		// blocking mode delay function
	timer_config(TIM6, 0, 7499);
	timer_IT_EN(TIM6);
	NVIC_EnableIRQ(TIM6_IRQn);

	timer_EN(TIM6);	// good for turning timer off when not in need to save power
	ticks = 0;
	while (ticks < ms)
		;
	timer_DI(TIM6);
}
//*******************************************************************************//

//************************** General Purpose TIMER FUNCTIONS ********************//

//*******************************************************************************//

//********************************| ADC FUNCTIONS |******************************//
void adc_calib() {
	// Calibrate ADC
	if ((ADC1->CR & ADC_CR_ADEN) != 0) /* (1) */
	{
		ADC1->CR |= ADC_CR_ADDIS; /* (2) */
	}
	while ((ADC1->CR & ADC_CR_ADEN) != 0) {
		/* For robust implementation, add here time-out management */
	}
	ADC1->CFGR1 &= ~ADC_CFGR1_DMAEN; /* (3) */
	ADC1->CR |= ADC_CR_ADCAL; /* (4) */
	while ((ADC1->CR & ADC_CR_ADCAL) != 0) /* (5) */
	{
	}
}
void adc_ready() {
	// ADC ENABLE
	if ((ADC1->ISR & ADC_ISR_ADRDY) != 0) /* (1) */
	{
		ADC1->ISR |= ADC_ISR_ADRDY; /* (2) */
	}
	ADC1->CR |= ADC_CR_ADEN; /* (3) */
	ticks_reset();
	while (ticks_val() < 50)
		;
	while ((ADC1->ISR & ADC_ISR_ADRDY) == 0) /* (4) */
	{
		/* For robust implementation, add here time-out management */
	}
}
void adc_clk_config() {
	RCC->APB2ENR |= RCC_APB2ENR_ADC1EN; /* (1) */
	RCC->CR2 |= RCC_CR2_HSI14ON; /* (2) */
	while ((RCC->CR2 & RCC_CR2_HSI14RDY) == 0) /* (3) */
	{
		/* For robust implementation, add here time-out management */
	}
}
void adc_sample_time(uint8_t sample_time) {
	ADC1->SMPR |= sample_time;
}
void adc_en() {
	adc_clk_config();
	adc_calib();
	adc_ready();
}
void adc_read(uint16_t *arr, uint8_t arr_len) {
	ADC1->CR |= ADC_CR_ADSTART;

	for (int i = 0; i < arr_len; i++) {
		while ((ADC1->ISR & ADC_ISR_EOC) == 0)
			;
		*(arr + i) = ADC1->DR;
	}
}

void adc_start() {
	ADC1->CR |= ADC_CR_ADSTART;
}
void adc_stop() {
	ADC1->CR |= ADC_CR_ADSTP;
}
void adc_disable() {
	ADC1->CR |= ADC_CR_ADSTP; /* (1) */
	while ((ADC1->CR & ADC_CR_ADSTP) != 0) /* (2) */
	{
		/* For robust implementation, add here time-out management */
	}
	ADC1->CR |= ADC_CR_ADDIS; /* (3) */
	while ((ADC1->CR & ADC_CR_ADEN) != 0) /* (4) */
	{
		/* For robust implementation, add here time-out management */
	}
}
void adc_chsel(uint32_t pin) {
	switch (pin) {
	case 0:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL0;
		break;
	case 1:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL1;
		break;
	case 2:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL2;
		break;
	case 3:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL3;
		break;
	case 4:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL4;
		break;
	case 5:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL5;
		break;
	case 6:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL6;
		break;
	case 7:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL7;
		break;
	case 8:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL8;
		break;
	case 9:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL9;
		break;
	case 10:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL10;
		break;
	case 11:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL11;
		break;
	case 12:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL12;
		break;
	case 13:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL13;
		break;
	case 14:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL14;
		break;
	case 15:
		ADC1->CHSELR |= ADC_CHSELR_CHSEL15;
		break;
	}
}
void adc_config(uint8_t sample_time, uint8_t CONT, uint8_t SCANDIR,
		uint8_t AUTOFF, uint8_t WAIT, uint8_t DISCEN, uint8_t OVRMOD) {
	adc_sample_time(sample_time);
	if (DISCEN) {
		ADC1->CFGR1 |= ADC_CFGR1_DISCEN;
	}
	if (AUTOFF) {
		ADC1->CFGR1 |= ADC_CFGR1_AUTOFF;
	}
	if (WAIT) {
		ADC1->CFGR1 |= ADC_CFGR1_WAIT;
	}
	if (CONT) {
		ADC1->CFGR1 |= ADC_CFGR1_CONT;
	}
	if (OVRMOD) {
		ADC1->CFGR1 |= ADC_CFGR1_OVRMOD;
	}
	if (SCANDIR) {
		ADC1->CFGR1 |= ADC_CFGR1_SCANDIR;
	}
}
void adc_IT_config(uint8_t flag_type) {
	if (flag_type == analog_watchdog_flag) {
		ADC1->IER |= ADC_IER_AWDIE;
	} else if (flag_type == ADC_overrun_flag) {
		ADC1->IER |= ADC_IER_OVRIE;
	} else if (flag_type == end_of_seq_flag) {
		ADC1->IER |= ADC_IER_EOSIE;
	} else if (flag_type == end_of_conv_flag) {
		ADC1->IER |= ADC_IER_EOCIE;
	} else if (flag_type == end_of_samp_flag) {
		ADC1->IER |= ADC_IER_EOSMPIE;
	}
	NVIC_EnableIRQ(ADC1_IRQn);
}

// Call the ADC1_IRQHandler when configuring interrupts
//*******************************************************************************//

//********************************| I2C FUNCTIONS |******************************//

void I2C_INIT(I2C_TypeDef *i2c, uint32_t timing) {
	if (i2c == I2C1) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;
	} else if (i2c == I2C2) {
		RCC->APB1ENR |= RCC_APB1ENR_I2C2EN;
	}
	i2c->CR1 = 0; /* software reset I2C1 */
	i2c->TIMINGR = timing; /* 100 KHz, peripheral clock is 8 MHz */
	i2c->CR1 = 0x00000001; /* enable I2C1 module */
}

void I2C_byteWrite(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint8_t data) {
	while (i2c->ISR & 0x8000)
		; /* wait until bus not busy */

	i2c->CR2 = 0x02002000 | (2 << 16) /* generate start, autoend, byte count 2 */
	| (saddr << 1); /* and send slave address */

	while (!(i2c->ISR & 0x02))
		; /* wait until TXIS is set */
	i2c->TXDR = maddr; /* send register address */

	while (!(i2c->ISR & 0x02))
		; /* wait until TXIS is set */
	i2c->TXDR = data; /* send data */

	while (!(i2c->ISR & 0x20))
		; /* wait until stop flag is set */

	i2c->ICR = 0x20; /* clear stop flag */
	i2c->CR2 = 0x02000000; /* clear configuration register 2 */
}

void I2C_byteRead(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint8_t *data) {
	while (i2c->ISR & 0x8000)
		; /* wait until bus not busy */

	i2c->CR2 = 0x00012000 | (saddr << 1); /* generate start and send slave address */
	while (!(i2c->ISR & 0x2))
		; /* wait until start flag is set */

	i2c->TXDR = maddr; /* send memory address */
	while (!(i2c->ISR & 0x40))
		; /* wait until transfer complete */

	/* generate restart, send slave address, read 1 byte, set for auto end */
	i2c->CR2 = 0x02002400 | (1 << 16) | (saddr << 1);

	while (!(i2c->ISR & 0x4))
		; /* Wait until RXNE flag is set */
	*data = i2c->RXDR; /* Read data from DR */

	while (!(i2c->ISR & 0x20))
		; /* wait until stop flag is set */

	i2c->ICR = 0x20; /* clear stop flag */
	i2c->CR2 = 0x02000000; /* clear configuration register 2 */
}

void I2C_MultiWrite(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint32_t n,
		uint8_t *data) {
	int i;

	while (i2c->ISR & 0x8000)
		; /* wait until bus not busy */

	i2c->CR2 = 0x02002000 | /* generate start, set byte count, */
	((n + 1) << 16) | (saddr << 1); /* set auto end, and send slave address */

	while (!(i2c->ISR & 0x02))
		; /* wait until TXIS is set */
	i2c->TXDR = maddr; /* send memory address */

	for (i = 0; i < n; i++) /* send n bytes of data */
	{
		while (!(i2c->ISR & 0x02))
			; /* wait until TXIS is set */
		i2c->TXDR = *data++; /* send a byte of data */
	}

	while (!(i2c->ISR & 0x20))
		; /* wait until stop flag is set */

	i2c->ICR = 0x20; /* clear stop flag */
	i2c->CR2 = 0x02000000; /* clear configuration register 2 */
}

void I2C_MultiRead(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint32_t n,
		uint8_t *data) {
	while (i2c->ISR & 0x8000)
		; /* wait until bus not busy */

	i2c->CR2 = 0x00012000 | (saddr << 1); /* generate start and send slave address */
	while (!(i2c->ISR & 0x02))
		; /* wait until transmitter is ready */
	i2c->TXDR = maddr; /* send memory address */
	while (!(i2c->ISR & 0x40))
		; /* wait until transfer complete */

	/* generate restart, send slave address, repeat read n bytes, set for auto end */
	i2c->CR2 = 0x02002400 | ((n & 0xFF) << 16) | (saddr << 1);

	for (; n > 0; n--) {
		while (!(i2c->ISR & 0x04))
			; /* Wait until RXNE flag is set */
		*data++ = i2c->RXDR; /* Read data from DR */
	}

	while (!(i2c->ISR & 0x20))
		; /* wait until stop flag is set */

	i2c->ICR = 0x20; /* clear stop flag */
	i2c->CR2 = 0x02000000; /* clear configuration register 2 */
}
//*******************************************************************************//
//*****************************| RCC CLOCK FUNCTION |****************************//
void RCC_CONFIG_48MHZ(){
	if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL) /* (1) */
	{
	 RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW); /* (2) */
	 while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) /* (3) */
	 {
	 /* For robust implementation, add here time-out management */
	 }
	}
	RCC->CR &= (uint32_t)(~RCC_CR_PLLON);/* (4) */
	while((RCC->CR & RCC_CR_PLLRDY) != 0) /* (5) */
	{
	 /* For robust implementation, add here time-out management */
	}
	RCC->CFGR = (RCC->CFGR & (~RCC_CFGR_PLLMUL)) | (RCC_CFGR_PLLMUL6); /* (6) */
//	RCC->CFGR = RCC_CFGR_PPRE_DIV1;
	RCC->CR |= RCC_CR_PLLON; /* (7) */
	while((RCC->CR & RCC_CR_PLLRDY) == 0) /* (8) */
	{
	 /* For robust implementation, add here time-out management */
	}
	RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL); /* (9) */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) /* (10) */
	{
	 /* For robust implementation, add here time-out management */
	}

	SystemCoreClockUpdate();
//	SysTick_Config(SystemCoreClock/1000);
}

//*******************************************************************************//
//*******************************************************************************************//
