#include <BML_DRIVER.h>
#include "74HC595_LIB.h"
#include "main.h"

int main(void) {
	RCC_CONFIG_48MHZ();
	uart_print_config(9600, 48);
	shift_register_setup();
	APP_DEBUG("Running\n\r");

	unsigned char lst_1 = 0b01010101;
	unsigned char lst_2 = 0b10101010;

	while (1) {
//		for(uint8_t i = 0; i < 255; i++){
//			shift_out(i, MSBFIRST);
//			delay_ms(500);
//		}

		shift_out(lst_2, MSBFIRST);
		delay_ms(500);
		shift_out(lst_1, MSBFIRST);
		delay_ms(500);

	}
}

void sys_delayMs(int n) {
    int i;
    /* Configure SysTick */
    SysTick->LOAD = 16600;  /* reload with number of clocks per millisecond */
    SysTick->VAL = 0;       /* clear current value register */
    SysTick->CTRL = 0x5;    /* Enable the timer */
//    SysTick_Config(SystemCoreClock/1000);

    for(i = 0; i < n; i++) {
        while((SysTick->CTRL & 0x10000) == 0) /* wait until the COUNTFLAG is set */
            { }
    }
    SysTick->CTRL = 0;      /* Stop the timer (Enable = 0) */
}

