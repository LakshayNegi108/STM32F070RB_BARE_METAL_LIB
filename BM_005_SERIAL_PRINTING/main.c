#include "main.h"
#include "BML_GPIO.h"


int main(void) {

	uart_print_config();
	uint32_t i = 0;

	while (1) {
		print("Hello testing\n\r");

//	USART2->TDR = "sdfr\n";
		for (i = 0; i < 100000; i++)
			;
	}
}
