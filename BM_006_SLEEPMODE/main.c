#include "main.h"
#include "BML_GPIO.h"

void gotoSleep(){
	RCC->APB1ENR |= RCC_APB1ENR_PWREN;

	SCB->SCR |= SCB_SCR_SLEEPDEEP_Msk;

	PWR->CR |= PWR_CR_PDDS;

	PWR->CR |= PWR_CR_CWUF;

	PWR->CSR |= (PWR_CSR_EWUP1);

	__WFI();
}

int main(void) {

	uart_print_config();
	if((PWR->CSR)&(PWR_CSR_SBF)){
		PWR->CR |= PWR_CR_CWUF;
		PWR->CR |= PWR_CR_CSBF;

		print("Awaken from standby\n\r");
	}
	else{
		print("Awaken from power cycle");
	}

	while (1) {
		print("--Going to sleep--");
		gotoSleep();
		print("fail");
	}
}
