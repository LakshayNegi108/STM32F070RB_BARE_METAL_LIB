#include "main.h"
#include "BML_DRIVER.h"

#include "stdio.h"
#include "fonts.h"
#include "ssd1306.h"
#include "test.h"
#include "bitmap.h"
#include "horse_anim.h"

char c[100];
uint8_t data[7];

#define num(z)		itoa(z, c, 10)

#define SLAVE_ADDR 0x68    /* 1101 000.    DS3231 */
#define SCL_PORT	PORTB
#define SCL_PIN		8

#define SDA_PORT	PORTB
#define SDA_PIN		9

int bcdToDec(uint8_t val) {
	return (int) (((val / 16) * 10) + (val % 16));
}

void clock_config() {

	if ((RCC->CFGR & RCC_CFGR_SWS) == RCC_CFGR_SWS_PLL) /* (1) */
	{
		RCC->CFGR &= (uint32_t) (~RCC_CFGR_SW); /* (2) */
		while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_HSI) /* (3) */
		{
			/* For robust implementation, add here time-out management */
		}
	}
	RCC->CR &= (uint32_t) (~RCC_CR_PLLON);/* (4) */
	while ((RCC->CR & RCC_CR_PLLRDY) != 0) /* (5) */
	{
		/* For robust implementation, add here time-out management */
	}
	RCC->CFGR = (RCC->CFGR & (~RCC_CFGR_PLLMUL)) | (RCC_CFGR_PLLMUL11); /* (6) */
	RCC->CR |= RCC_CR_PLLON; /* (7) */
	while ((RCC->CR & RCC_CR_PLLRDY) == 0) /* (8) */
	{
		/* For robust implementation, add here time-out management */
	}
	RCC->CFGR |= (uint32_t) (RCC_CFGR_SW_PLL); /* (9) */
	while ((RCC->CFGR & RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL) /* (10) */
	{
		/* For robust implementation, add here time-out management */
	}

}

void reverse(char s[], int length) {
	uint8_t i, j;
	uint8_t c;

	for (i = 0, j = length - 1; i < j; i++, j--) {
		c = s[i];
		s[i] = s[j];
		s[j] = c;
	}
}

// Implementation of itoa()
char* itoa(int num, char *str, int base) {
	int i = 0;
	uint8_t isNegative = 0;

	/* Handle 0 explicitly, otherwise empty string is printed for 0 */
	if (num == 0) {
		str[i++] = '0';
		str[i] = '\0';
		return str;
	}

	// In standard itoa(), negative numbers are handled only with
	// base 10. Otherwise numbers are considered unsigned.
	if (num < 0 && base == 10) {
		isNegative = 1;
		num = -num;
	}

	// Process individual digits
	while (num != 0) {
		int rem = num % base;
		str[i++] = (rem > 9) ? (rem - 10) + 'a' : rem + '0';
		num = num / base;
	}

	// If number is negative, append '-'
	if (isNegative)
		str[i++] = '-';

	str[i] = '\0'; // Append string terminator

	// Reverse the string
	reverse(str, i);
	if (str[1] == '\0') {
		str[1] = str[0];
		str[0] = '0';
		str[3] = '\0';
	}

	return str;
}

int main(void) {

	clock_config();

	SSD1306_Init();  // initialise
	uart_print_config();

	gpio_config(SCL_PORT, SCL_PIN, ALT_MODE, HIGH_SPEED, EN_PU, OD);
	gpio_config(SDA_PORT, SDA_PIN, ALT_MODE, HIGH_SPEED, EN_PU, OD);

	gpio_altfn(SCL_PORT, SCL_PIN, I2C1_SCL_PB8);
	gpio_altfn(SDA_PORT, SDA_PIN, I2C1_SDA_PB9);

	I2C_CONFIG i2c1;
	i2c1.i2c = I2C1;
	i2c1.TIMING = 0x10420F13;

	I2C_INIT(i2c1.i2c, i2c1.TIMING);

	/*                          00    01    02    03    04    05    06 */
	uint8_t timeDateToSet[15] = { 0x45, 0x46, 0x11, 0x05, 0x24, 0x03, 0x22, 0 };
	/* 2017 September 26, Tuesday, 10:58:55 */
//       I2C_MultiWrite(I2C1, SLAVE_ADDR, 0, 7, timeDateToSet);
	delay_ms(2000);
	SSD1306_Clear();
	uint16_t z = 0;
	SSD1306_DrawFilledRectangle(0, 0, 128, 14, 1);
	SSD1306_DrawRectangle(0, 14, 128, 64, 1);
	while (1) {
		I2C_MultiRead(i2c1.i2c, SLAVE_ADDR, 0x00, 7, data);
		SSD1306_GotoXY(1, 5);
		SSD1306_Puts(num(bcdToDec(data[2])), &Font_7x10, 0);
		SSD1306_Putc(':', &Font_7x10, 0);
		SSD1306_Puts(num(bcdToDec(data[1])), &Font_7x10, 0);
		SSD1306_Putc(':', &Font_7x10, 0);
		SSD1306_Puts(num(bcdToDec(data[0])), &Font_7x10, 0);

		SSD1306_GotoXY(30, 5);
		SSD1306_Puts("566", &Font_11x18, 1);
		SSD1306_DrawLine(10, 14, 10, 54, 1);
		SSD1306_UpdateScreen();

		delay_ms(1000);
	}
}
