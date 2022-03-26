/* p11_4.c Variable duty cycle PWM to control LED on duration
 *
 * This program is the same as p11_3.c except the frequency is much
 * slower so that the change of the duration when the LED is on
 * can be observed by naked eyes.
 * This program was tested with Keil uVision v5.23 with DFP v2.0.0.
 */

#include "stm32f0xx.h"

void delayMs(int n);

int main(void) {
    RCC->AHBENR |=  0x00040000;     /* enable GPIOB clock */
    GPIOB->AFR[0] |= 0x02000000;    /* PB6 pin for TIM16 channel N1 */
    GPIOB->MODER &= ~0x00003000;
    GPIOB->MODER |=  0x00002000;

    /* setup TIM16 */
    RCC->APB2ENR |= 0x00020000;     /* enable TIM16 clock */
    TIM16->PSC = 8000 - 1;          /* divided by 8000 */
    TIM16->ARR = 1000 - 1;          /* divided by 1000 */
    TIM16->CNT = 0;
    TIM16->CCMR1 = 0x0060;          /* PWM mode */
    TIM16->CCER = 4;                /* enable PWM ChN1 */
    TIM16->BDTR = 0x8000;           /* enable main output enable */
    TIM16->CCR1 = 10;               /* pulse width 1/3 of the period */
    TIM16->CR1 = 1;                 /* enable timer */

    while(1) {
        TIM16->CCR1 = TIM16->CCR1 * 110 / 100;
        if (TIM16->CCR1 > 1000)
            TIM16->CCR1 = 10;
        delayMs(400);
    }
}
/* 8 MHz SYSCLK */
void delayMs(int n) {
    int i;
    for (; n > 0; n--)
        for (i = 0; i < 1142; i++) ;
}
