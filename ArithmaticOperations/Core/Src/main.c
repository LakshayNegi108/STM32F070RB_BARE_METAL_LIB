#include "main.h"
#include "BML_DRIVER.h"

uint64_t a, b, c;
uint32_t a1, b1, c1;
uint16_t a2, b2, c2;
uint8_t a3, b3, c3;
uint16_t timEnd = 0, timStart = 0;
double timLap;

void print64bitu(uint64_t x) {
	uint8_t temp = 0;
	uint8_t str[20] = { 0 };
	uint8_t i = 0;
	while (x) {
		temp = x % 10;
		str[i] = temp;
		x /= 10;
		i++;
	}
	for (int j = i - 1; j >= 0; j--) {
		print("%d", str[j]);
	}
}

void print64bits(int64_t x) {
	int8_t temp = 0;
	int8_t str[20] = { 0 };
	uint8_t i = 0;
	while (x) {
		temp = x % 10;
		str[i] = abs(temp);
		x /= 10;
		i++;
	}
	print("-");
	for (int j = i - 1; j >= 0; j--) {
		print("%d", str[j]);
	}
}

uint32_t Ticks = 0;
uint8_t strVal[50] = { 0 };
void timer7_config(uint16_t auto_reload_val, uint16_t prescaler_val) {
	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;

	TIM7->ARR = auto_reload_val; // fill auto-reload register with value: auto_reload_val
	TIM7->PSC = prescaler_val; // fill prescale value register with value: prescaler_val.
}

void Ticks7_timer() {			// similar to millis

	timer7_config(0xFFFF - 1, 0);
	TIM7->CR1 |= TIM_CR1_CEN;
}

void Ticks_reset() {
	Ticks = 0;
}
uint32_t Ticks_Val() {
//	return (Ticks * 2);
	return (Ticks);
}
uint32_t Timer7_cnt_val() {
	uint32_t val = TIM7->CNT;		// counter register value
	return val;
}

void tim64bit() {
	USART_WRITE(USART2, "//===| 64-bit Num |===//\n\r", 26);
	a = 0, b = 0, c = 0;

	a = 0xFFFFFFFFFF;
	b = 0xFFFFFFFFFF;
	timStart = TIM7->CNT;
	c = a + b;
	timEnd = TIM7->CNT;
//	print64bitu(c);
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(ADD): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a = 0xFFFFFFFFFF;
	b = 0xFFFFFFFFFE;
	timStart = TIM7->CNT;
	c = a - b;
	timEnd = TIM7->CNT;
//	print64bitu(c);
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(SUB): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a = 0xFFFFFF;
	b = 0xFFFFFF;
	timStart = TIM7->CNT;
	c = a * b;
	timEnd = TIM7->CNT;
//	print64bitu(c);
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(MUL): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a = 0xFFFFFFFF;
	b = 0xFFFFFFFF;
	timStart = TIM7->CNT;
	c = a / b;
	timEnd = TIM7->CNT;
//	print64bitu(c);
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(DIV): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));
}

void tim32bit() {
	USART_WRITE(USART2, "//===| 32-bit Num |===//\n\r", 26);
	a1 = 0, b1 = 0, c1 = 0;

	a1 = 0xFFFFFF;
	b1 = 0xFFFFFF;
	timStart = TIM7->CNT;
	c1 = a1 + b1;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(ADD): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a1 = 0xFFFFFF;
	b1 = 0xFFFFFF;
	timStart = TIM7->CNT;
	c1 = a1 - b1;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(SUB): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a1 = 0xFFFF;
	b1 = 0xFFFF;
	timStart = TIM7->CNT;
	c1 = a1 * b1;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(MUL): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a1 = 0xFFFFFF;
	b1 = 0xFFFFFF;
	timStart = TIM7->CNT;
	c1 = a1 / b1;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(DIV): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));
}

void tim16bit() {
	USART_WRITE(USART2, "//===| 16-bit Num |===//\n\r", 26);
	a2 = 0, b2 = 0, c2 = 0;

	a2 = 0xFFF;
	b2 = 0xFFF;
	timStart = TIM7->CNT;
	c2 = a2 + b2;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(ADD): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a2 = 0xFFFF;
	b2 = 0xFFFF;
	timStart = TIM7->CNT;
	c2 = a2 - b2;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(SUB): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a2 = 0xFF;
	b2 = 0xFF;
	timStart = TIM7->CNT;
	c2 = a2 * b2;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(MUL): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a2 = 0xFFFF;
	b2 = 0xFFFF;
	timStart = TIM7->CNT;
	c2 = a2 / b2;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(DIV): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));
}

void tim8bit() {
	USART_WRITE(USART2, "//===| 8-bit Num |===//\n\r", 26);
	a3 = 0, b3 = 0, c3 = 0;

	a3 = 0x0F;
	b3 = 0x0F;
	timStart = TIM7->CNT;
	c3 = a3 + b3;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(ADD): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a3 = 0xFF;
	b3 = 0xFF;
	timStart = TIM7->CNT;
	c3 = a3 - b3;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(SUB): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a3 = 0x0F;
	b3 = 0x0F;
	timStart = TIM7->CNT;
	c3 = a3 * b3;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(MUL): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));


	a3 = 0xFF;
	b3 = 0xFF;
	timStart = TIM7->CNT;
	c3 = a3 / b3;
	timEnd = TIM7->CNT;
	timLap = ((float)(timEnd - timStart)) / 48;
	sprintf(strVal, "Time Lapsed(DIV): %0.5fus\n", timLap);
	USART_WRITE(USART2, strVal, strlen(strVal));
}

int main() {
	RCC_CONFIG_48MHZ();
	USART_INIT(USART2, PORTA, PORTA, 2, 3, 9600);
	USART_WRITE(USART2, "\r\nRunning\n\r", 9);
	sprintf(strVal, "\n\rSystem Clk Val: %d\n", SystemCoreClock);
	USART_WRITE(USART2, strVal, strlen(strVal));

	gpio_config(PORTA, 5, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	Ticks7_timer();

	tim64bit();
	tim32bit();
	tim16bit();
	tim8bit();

	while (1) {
//		float az = ((float)453/48);
//		print("%f\n", az);
//		HAL_Delay(500);
	}
	return 0;
}

//==============================================================================================================================//

//#include "main.h"
//#include "BML_DRIVER.h"
//
//void print64bitu(uint64_t x) {
//	uint8_t temp = 0;
//	uint8_t str[20] = { 0 };
//	uint8_t i = 0;
//	while (x) {
//		temp = x % 10;
//		str[i] = temp;
//		x /= 10;
//		i++;
//	}
//	for (int j = i - 1; j >= 0; j--) {
//		print("%d", str[j]);
//	}
//}
//
//void print64bits(int64_t x) {
//	int8_t temp = 0;
//	int8_t str[20] = { 0 };
//	uint8_t i = 0;
//	while (x) {
//		temp = x % 10;
//		str[i] = abs(temp);
//		x /= 10;
//		i++;
//	}
//	print("-");
//	for (int j = i - 1; j >= 0; j--) {
//		print("%d", str[j]);
//	}
//}
//
//uint32_t Ticks = 0;
//uint8_t strVal[50] = { 0 };
//void timer7_config(uint16_t auto_reload_val, uint16_t prescaler_val) {
//	RCC->APB1ENR |= RCC_APB1ENR_TIM7EN;
//
//	TIM7->ARR = auto_reload_val; // fill auto-reload register with value: auto_reload_val
//	TIM7->PSC = prescaler_val; // fill prescale value register with value: prescaler_val.
//
////	sprintf(strVal, "\r\nARR Val: %d\n\r", auto_reload_val);
////	USART_WRITE(USART2, strVal, strlen(strVal));
//
//}
//
//void Ticks7_timer() {			// similar to millis
//
//	timer7_config((SystemCoreClock / 1000000) - 1, 0);
////	timer7_config(48 - 1, 0);
//	TIM7->DIER |= TIM_DIER_UIE;		//IT EN
//	NVIC_EnableIRQ(TIM7_IRQn);
//	TIM7->CR1 |= TIM_CR1_CEN;
//}
//
//void Ticks_reset() {
//	Ticks = 0;
//}
//uint32_t Ticks_Val() {
////	return (Ticks * 2);
//	return (Ticks);
//}
//
//void bit64_AdditionTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint64_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0xFFFFFFFFFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0xFFFFFFFFFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a + b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("64-bit unsigned Num: ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nAdding: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//void bit64_MultiplicationTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint64_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0xFFFFFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0xFFFFFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a * b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("64-bit unsigned Num: ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nMultiply: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//void bit32_AdditionTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint32_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0x1FFFFFFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0x1FFFFFFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a + b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("32-bit unsigned Num : ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nAdding: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//void bit32_MultiplicationTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint32_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0xFFFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0xFFFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a * b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("32-bit unsigned Num: ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nMultiply: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//void bit16_AdditionTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint16_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0x1FFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0x1FFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a + b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("16-bit unsigned Num: ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nAdding: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//void bit16_MultiplicationTime() {
//	uint32_t val1, val2, val3, val4, val5;
//	uint16_t a = 0, b = 0, c = 0;
//
//	Ticks_reset();
//	a = 0xFF;
//	val1 = Ticks_Val();
//	Ticks_reset();
//	b = 0xFF;
//	val2 = Ticks_Val();
//
//	Ticks_reset();
//	c = a * b;
//	val3 = Ticks_Val();
//
//	Ticks_reset();
//	print("64-bit unsigned Num: ");
//	print64bitu(c);
//	val4 = Ticks_Val();
//
//	print(
//			"\r\nLoading A: 		%dus\
//				\r\nLoading B: 		%dus\
//				\r\nMultiply: 		%dus\
//				\r\nPrint: 			%dus\n\r"\
//,
//			val1, val2, val3, val4);
//}
//
//int main() {
//	RCC_CONFIG_48MHZ();
//	USART_INIT(USART2, PORTA, PORTA, 2, 3, 9600);
//	USART_WRITE(USART2, "\r\nRunning\n\r", 9);
//	sprintf(strVal, "\n\rSystem Clk Val: %d\n", SystemCoreClock);
//	USART_WRITE(USART2, strVal, strlen(strVal));
//
//	gpio_config(PORTA, 5, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
//	Ticks7_timer();
//
//	USART_WRITE(USART2, "//====| 64-bit Addition |====//\n\r", 33);
//	bit64_AdditionTime();
//	USART_WRITE(USART2, "//====| 64-bit Mulitplication |====//\n\r", 39);
//	bit64_MultiplicationTime();
//
//	USART_WRITE(USART2, "//====| 32-bit Addition |====//\n\r", 33);
//	bit32_AdditionTime();
//	USART_WRITE(USART2, "//====| 32-bit Mulitplication |====//\n\r", 39);
//	bit32_MultiplicationTime();
//
//	USART_WRITE(USART2, "//====| 16-bit Addition |====//\n\r", 33);
//	bit16_AdditionTime();
//	USART_WRITE(USART2, "//====| 16-bit Mulitplication |====//\n\r", 39);
//	bit16_MultiplicationTime();
//
//	while (1) {
////		if (Ticks_Val() >= 1000000) {
////			USART_WRITE(USART2, "1\n", 2);
//////			sprintf(strVal, "%d\n\r", Ticks);
//////			USART_WRITE(USART2, strVal, strlen(strVal));
//////			gpio_toggle(PORTA, 5);
////			Ticks_reset();
////		}
//	}
//	return 0;
//}
//
//void TIM7_IRQHandler(void) {		// Timer Interrupt helping in delay
//	Ticks++;
//	TIM7->SR &= ~TIM_SR_UIF;
//}
