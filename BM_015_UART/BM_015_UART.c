#include <BML_DRIVER.h>
#include "main.h"

uint8_t flag = 0;

#define data_len 20

char data[data_len];

int main(void) {
	RCC_CONFIG_48MHZ();
	USART_INIT(USART2, 48, PORTA, PORTA, 2, 3, 9600);

	char c;
	uint8_t idx = 0;
	memset(data, 0, data_len);

	while (1) {
		c = USART_READ(USART2);
		USART_WRITE(USART2, c, 1);
		if (c == '\n') {
			USART_WRITE(USART2, data, data_len);
			uint8_t idx = 0;
			memset(data, 0, data_len);
		} else {
			if (idx < data_len - 1) {
				data[idx] = c;
				idx++;
			}
		}
	}
}

//#include <BML_DRIVER.h>
//#include "main.h"
//
//uint8_t flag = 0;
//char data[500];
///*----------------------------------------------------------------------------
// MAIN function
// *----------------------------------------------------------------------------*/
//int main(void) {
//	RCC_CONFIG_48MHZ();
//	USART_INIT(USART2, 48, PORTA, PORTA, 2, 3, 9600);
////====== IT =============//
////	USART_IT_EN(USART2);
////=======================//
//	uint8_t i = 0;
//	while (1) {
////======================== 1. Pooling ================================//
////		char ch[] = "Hello from USART2\n\r";
////		char ch2[8];
//
////		char ch3;
////		sprintf(ch2, "%d", 99);
////		USART_WRITE(USART2, ch, strlen(ch));
////		USART_WRITE(USART2, ch2, strlen(ch2));
////		ch3 = USART_READ(USART2);
////		if (flag == 1) {
////			USART_WRITE(USART2, ch3, 1);
////			flag = 0;
////		}
////		i++;
////		delay_ms(999);
////==================================================================//
//	}
//}
//
////====== 2. IT ========================================================//
////void USART2_IRQHandler(){
////	char data_ch;
////	uint8_t i = 0;
////	if((USART2->ISR & USART_ISR_TXE) == USART_ISR_TXE){
//////		USART_WRITE(USART2, "Hello\n\r", 9);
////	}
////	if((USART2->ISR & USART_ISR_RXNE) == USART_ISR_RXNE){
////		data_ch = USART_READ(USART2);
////		USART_WRITE(USART2, data_ch, 1);
////	}
////}
////==================================================================//

