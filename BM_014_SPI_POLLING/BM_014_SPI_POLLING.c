/* p8_1.c: Using SPI1 to send A to Z characters
 *
 * SPI1 is configured as master with software slave select.
 * Clock rate is set to 1 MHz. Polarity/Phase are 0, 0
 *
 * PA7  MOSI
 * PA5  SCK
 * PA4  SS
 *
 * This program was tested with Keil uVision v5.23 with DFP v2.0.0.
 */


#include <BML_DRIVER.h>
#include "main.h"

void delayMs(int n);
void SPI1_init(void);
void SPI1_write(unsigned char data);

int main(void) {
//	RCC_CONFIG_8MHZ();
	uart_print_config(9600, 8);

	APP_DEBUG("Running\n\r");

	char c;

	SPI1_init();
	uint8_t chr;
	while (1) {
		for (c = 'A'; c <= 'Z'; c++) {
			SPI1_write(c); /* write the letter through SPI1 */

			chr = SPI1->DR;
			APP_DEBUG("%d\n\r",chr);
			delayMs(10);
		}
	}
}

/* enable SPI1 and associated GPIO pins */
void SPI1_init(void)
{
//	RCC->AHBENR |=  0x00020000;     /* enable GPIOA clock */
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;     /* enable SPI1 clock */

	/* PORTA 5, 7 for SPI1 MOSI and SCLK */
	gpio_config(PORTA, 5, ALT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 6, ALT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 7, ALT_MODE, HIGH_SPEED, DI_PUPD, PHPL);

	gpio_altfn(PORTA, 5, SPI1_SCK_PA5);
	gpio_altfn(PORTA, 6, SPI1_MISO_PA6);
	gpio_altfn(PORTA, 7, SPI1_MOSI_PA7);

	/* PORTA4 as GPIO output for SPI slave select */
	gpio_config(PORTA, 4, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);

	SPI1->CR1 = 0x0314;             /* set the Baud rate (1MHz Clock), 8-bit data frame */
	SPI1->CR2 = 0x0700;
	SPI1->CR1 |= 0x40;              /* enable SPI1 module */
}

/* This function enables slave select, writes one byte to SPI1,
   wait for transmission complete and deassert slave select. */
void SPI1_write(uint8_t data)
{
	while (!(SPI1->SR & SPI_SR_TXE)) {}      /* wait until Transfer buffer Empty */
//	GPIOA->BSRR = 0x00100000;       /* assert slave select */
	gpio_write(PORTA, 4, LOW);
	SPI1->DR = data;   /* write data */
	while (SPI1->SR & SPI_SR_BSY) {}      /* wait for transmission done */
//	GPIOA->BSRR = 0x00000010;       /* deassert slave select */
	gpio_write(PORTA, 4, HIGH);
}

/* 8 MHz SYSCLK */
void delayMs(int n)
{
	int i;

	for (; n > 0; n--)
		for (i = 0; i < 1142; i++);
}

