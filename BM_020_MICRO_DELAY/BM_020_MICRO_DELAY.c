#include "BML_DRIVER.h"
#include "main.h"
#include "delay_microsecond.h"

//uint32_t i = 0;



int main() {

	RCC_CONFIG_48MHZ();
	uart_print_config(9600, 48);

	print("Working\n\r");

	while (1) {
//		if (i >= 100000) {
//			print("%d\n\r", TIM7->CNT);
//				TIM7->EGR |= TIM_EGR_UG;
//			i = 0;
//		}
		print("%d\n\r", TIM7->CNT);
		micro_delay(50000);
	}
	return 0;
}


