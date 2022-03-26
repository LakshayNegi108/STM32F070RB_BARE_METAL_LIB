#include <BML_DRIVER.h>
#include "main.h"

#define ADC0_PORT	GPIOA
#define ADC0_PIN	0
#define ADC1_PORT	GPIOA
#define ADC1_PIN	1
#define ADC4_PORT	GPIOA
#define ADC4_PIN	4

/*****************************************************
*Function name: kalman_filter
 *Function function: ADC_filter
 *Entry parameter: ADC_Value
 *Export parameters: kalman_adc
*****************************************************/
unsigned long kalman_filter(unsigned long ADC_Value)
{
    float x_k1_k1,x_k_k1;
    static float ADC_OLD_Value;
    float Z_k;
    static float P_k1_k1;

    static float Q = 0.0001;//Q: Regulation noise, Q increases, dynamic response becomes faster, and convergence stability becomes worse
    static float R = 0.005; //R: Test noise, R increases, dynamic response becomes slower, convergence stability becomes better
    static float Kg = 0;
    static float P_k_k1 = 1;

    float kalman_adc;
    static float kalman_adc_old=0;
    Z_k = ADC_Value;
    x_k1_k1 = kalman_adc_old;

    x_k_k1 = x_k1_k1;
    P_k_k1 = P_k1_k1 + Q;

    Kg = P_k_k1/(P_k_k1 + R);

    kalman_adc = x_k_k1 + Kg * (Z_k - kalman_adc_old);
    P_k1_k1 = (1 - Kg)*P_k_k1;
    P_k_k1 = P_k1_k1;

    ADC_OLD_Value = ADC_Value;
    kalman_adc_old = kalman_adc;

    return kalman_adc;
}

int main(void) {
	uart_print_config();
	ticks_timer();
	adc_en();
	APP_DEBUG("Running\n\r");

	gpio_config(ADC0_PORT, ADC0_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD);
	gpio_config(ADC1_PORT, ADC1_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD);
	gpio_config(ADC4_PORT, ADC4_PIN, ANALOG_MODE, LOW_SPEED, DI_PUPD);
//	ADC1->IER |= ADC_IER_EOCIE;
//	NVIC_EnableIRQ(ADC1_IRQn);
	adc_config(sample_time_7, CONT_off, SCANDIR_off, AUTOFF_off, WAIT_off, DISCEN_off, OVRMOD_off);
	uint16_t ADC_result[3];

	while (1) {
		adc_read(&ADC_result[0], 3);
		if (ticks_val() > 50) {
//			APP_DEBUG("ADC value: %d", ADC_result[0]);
			APP_DEBUG("%d", kalman_filter(ADC_result[1]));
			APP_DEBUG(" ,%d\n\r", ADC_result[1]);
//			APP_DEBUG(" ,%d\n\r", ADC_result[2]);
			ticks_reset();
		}
	}
}

