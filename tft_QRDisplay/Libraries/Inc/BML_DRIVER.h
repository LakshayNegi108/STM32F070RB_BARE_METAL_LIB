/*
 * BML_GPIO.h
 *
 *  Created on: Feb 18, 2022
 *      Author: hp
 */

#ifndef INC_BML_DRIVER_H_
#define INC_BML_DRIVER_H_

#include "stm32f070xb.h"
#include "stm32f0xx_hal.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

#define DBG_BUF_LEN   100
static char DBG_BUFFER[DBG_BUF_LEN];
#define APP_DEBUG(FORMAT,...) {\
		memset(DBG_BUFFER, 0, DBG_BUF_LEN);\
		sprintf(DBG_BUFFER,FORMAT,##__VA_ARGS__);\
		for(uint8_t i = 0; i < DBG_BUF_LEN; i++) {\
			USART2->TDR = DBG_BUFFER[i];\
			while(!(USART2->ISR & USART_ISR_TXE));\
				}\
}

#define LOW			0
#define HIGH		1

#define PORTA		GPIOA
#define PORTB		GPIOB
#define PORTC		GPIOC
#define PORTD		GPIOD
#define PORTE		GPIOE
#define PORTF		GPIOF

// PIN FUNCTION MODES
#define INPUT_MODE					((uint32_t)0x00U)
#define OUTPUT_MODE					((uint32_t)0x01U)
#define ALT_MODE					((uint32_t)0x02U)
#define ANALOG_MODE					((uint32_t)0x03U)

// PIN SPEED MODES
#define LOW_SPEED					((uint32_t)0x00U)
#define MEDIUM_SPEED				((uint32_t)0x01U)
#define HIGH_SPEED					((uint32_t)0x02U)

// ENABLE-DISABLE PULL-UP/PULL-DOWN
#define DI_PUPD						((uint32_t)0x00U)
#define EN_PU						((uint32_t)0x01U)
#define EN_PD						((uint32_t)0x02U)

// ENABLE-DISABLE PUSH-PULL or OPEN-DRAIN
#define PHPL						((uint32_t)0x00U)
#define OD							((uint32_t)0x01U)

// ENABLE CLOCK FOR DIFFERENT PORTS
#define GPIOA_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOAEN)
#define GPIOB_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOBEN)
#define GPIOC_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOCEN)
#define GPIOD_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIODEN)
//#define GPIOE_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOEEN)
#define GPIOF_CLK_EN				(RCC->AHBENR |= RCC_AHBENR_GPIOFEN)

#define SYSCFG_CLK_EN				(RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN)

// NAMING FOR ALTERNATE FUNCTION ARRAY
#define ALT_FUN_0					0x00
#define ALT_FUN_1					0x01
#define ALT_FUN_2					0x02
#define ALT_FUN_3					0x03
#define ALT_FUN_4					0x04
#define ALT_FUN_5					0x05
#define ALT_FUN_6					0x06
#define ALT_FUN_7					0x07

//========================== ALTERNATE PERIPHERAL NAMES ==========================//
//============= ALTERNATE FUNCTION 0 ==================//
#define EVENTOUT_PA1					ALT_FUN_0	//PA1
#define TIM15_CH1_PA2					ALT_FUN_0	//PA2
#define TIM15_CH2_PA3					ALT_FUN_0	//PA3
#define SPI1_NSS_PA4					ALT_FUN_0	//PA4
#define SPI1_SCK_PA5					ALT_FUN_0	//PA5
#define SPI1_MISO_PA6					ALT_FUN_0	//PA6
#define SPI1_MOSI_PA7					ALT_FUN_0	//PA7
#define MCO_PA8							ALT_FUN_0	//PA8
#define TIM15_BKIN_PA9					ALT_FUN_0	//PA9
#define TIM17_BKIN_PA10					ALT_FUN_0	//PA10
#define EVENTOUT_PA11					ALT_FUN_0	//PA11
#define EVENTOUT_PA12					ALT_FUN_0	//PA12
#define SWDIO_PA13						ALT_FUN_0	//PA13
#define SWCLK_PA14						ALT_FUN_0	//PA14
#define SPI1_NSS_PA15					ALT_FUN_0	//PA15

#define EVENTOUT_PB0					ALT_FUN_0	//PB0
#define TIM14_CH1_PB1					ALT_FUN_0	//PB1
#define SPI1_SCK_PB3					ALT_FUN_0	//PB3
#define SPI1_MISO_PB4					ALT_FUN_0	//PB4
#define SPI1_MOSI_PB5					ALT_FUN_0	//PB5
#define USART1_TX_PB6					ALT_FUN_0	//PB6
#define USART1_RX_PB7					ALT_FUN_0	//PB7
#define IR_OUT_PB9						ALT_FUN_0	//PB9
#define EVENTOUT_PB11					ALT_FUN_0	//PB11
#define SPI2_NSS_PB12					ALT_FUN_0	//PB12
#define SPI2_SCK_PB13					ALT_FUN_0	//PB13
#define SPI2_MISO_PB14					ALT_FUN_0	//PB14
#define SPI2_MOSI_PB15					ALT_FUN_0	//PB15

#define EVENTOUT_PC0					ALT_FUN_0	//PC0
#define EVENTOUT_PC1					ALT_FUN_0	//PC1
#define EVENTOUT_PC3					ALT_FUN_0	//PC3
#define EVENTOUT_PC4					ALT_FUN_0	//PC4
#define TIM3_CH1_PC6					ALT_FUN_0	//PC6
#define TIM3_CH2_PC7					ALT_FUN_0	//PC7
#define TIM3_CH3_PC8					ALT_FUN_0	//PC8
#define TIM3_CH4_PC9					ALT_FUN_0	//PC9
#define USART4_TX_PC10					ALT_FUN_0	//PC10
#define USART4_RX_PC11					ALT_FUN_0	//PC11
#define USART4_CK_PC12					ALT_FUN_0	//PC12

//============= ALTERNATE FUNCTION 1 ==================//
#define USART2_CTS_PA0					ALT_FUN_1	//PA0
#define USART2_RTS_PA1					ALT_FUN_1	//PA1
#define USART2_TX_PA2					ALT_FUN_1	//PA2
#define USART2_RX_PA3					ALT_FUN_1	//PA3
#define USART2_CK_PA4					ALT_FUN_1	//PA4
#define TIM3_CH1_PA6					ALT_FUN_1	//PA6
#define TIM3_CH2_PA7					ALT_FUN_1	//PA7
#define USART1_CK_PA8					ALT_FUN_1	//PA8
#define USART1_TX_PA9					ALT_FUN_1	//PA9
#define USART1_RX_PA10					ALT_FUN_1	//PA10
#define USART1_CTS_PA11					ALT_FUN_1	//PA11
#define USART1_RTS_PA12					ALT_FUN_1	//PA12
#define IR_OUT_PA13						ALT_FUN_1	//PA13
#define USART2_TX_PA14					ALT_FUN_1	//PA14
#define USART2_RX_PA15					ALT_FUN_1	//PA15

#define TIM3_CH3_PB0					ALT_FUN_1	//PB0
#define TIM3_CH4_PB1					ALT_FUN_1	//PB1
#define EVENTOUT_PB3					ALT_FUN_1	//PB3
#define TIM3_CH1_PB4					ALT_FUN_1	//PB4
#define TIM3_CH2_PB5					ALT_FUN_1	//PB5
#define I2C1_SCL_PB6					ALT_FUN_1	//PB6
#define I2C1_SDA_PB7					ALT_FUN_1	//PB7
#define I2C1_SCL_PB8					ALT_FUN_1	//PB8
#define I2C1_SDA_PB9					ALT_FUN_1	//PB9
#define I2C2_SCL_PB10					ALT_FUN_1	//PB10
#define I2C2_SDA_PB11					ALT_FUN_1	//PB11
#define EVENTOUT_PB12					ALT_FUN_1	//PB12
#define TIM15_CH1_PB14					ALT_FUN_1	//PB14
#define TIM15_CH2_PB15					ALT_FUN_1	//PB15

#define SPI2_MISO_PC2					ALT_FUN_1	//PC2
#define SPI2_MOSI_PC3					ALT_FUN_1	//PC3
#define USART3_TX_PC4					ALT_FUN_1	//PC4
#define USART3_RX_PC5					ALT_FUN_1	//PC5
#define USART3_TX_PC10					ALT_FUN_1	//PC10
#define USART3_RX_PC11					ALT_FUN_1	//PC11
#define USART3_CK_PC12					ALT_FUN_1	//PC12

//============= ALTERNATE FUNCTION 2 ==================//
#define USB_NOE_PA4						ALT_FUN_2	//PA4
#define TIM1_BKIN_PA6					ALT_FUN_2	//PA6
#define TIM1_CH1N_PA7					ALT_FUN_2	//PA7
#define TIM1_CH1_PA8					ALT_FUN_2	//PA8
#define TIM1_CH2_PA9					ALT_FUN_2	//PA9
#define TIM1_CH3_PA10					ALT_FUN_2	//PA10
#define TIM1_CH4_PA11					ALT_FUN_2	//PA11
#define TIM1_ETR_PA12					ALT_FUN_2	//PA12
#define USB_NOE_PA13					ALT_FUN_2	//PA13

#define TIM1_CH2N_PB0					ALT_FUN_2	//PB0
#define TIM1_CH3N_PB1					ALT_FUN_2	//PB1
#define EVENTOUT_PB4					ALT_FUN_2	//PB4
#define TIM16_BKIN_PB5					ALT_FUN_2	//PB5
#define TIM16_CH1N_PB6					ALT_FUN_2	//PB6
#define TIM17_CH1N_PB7					ALT_FUN_2	//PB7
#define TIM16_CH1_PB8					ALT_FUN_2	//PB8
#define TIM17_CH1_PB9					ALT_FUN_2	//PB9
#define TIM1_BKIN_PB12					ALT_FUN_2	//PB12
#define TIM1_CH1N_PB13					ALT_FUN_2	//PB13
#define TIM1_CH2N_PB14					ALT_FUN_2	//PB14
#define TIM1_CH3N_PB15					ALT_FUN_2	//PB15

//============= ALTERNATE FUNCTION 3 =================//
#define EVENTOUT_PA8					ALT_FUN_3	//PA8
#define EVENTOUT_PA15					ALT_FUN_3	//PA15

#define I2C1_SMBA_PB5					ALT_FUN_3	//PB5
#define EVENTOUT_PB9					ALT_FUN_3	//PB9
#define TIM15_CH1N_PB15					ALT_FUN_3	//PB15

//============= ALTERNATE FUNCTION 4 ==================//
#define USART4_TX_PA0					ALT_FUN_4	//PA0
#define USART4_RX_PA1					ALT_FUN_4	//PA1
#define TIM14_CH1_PA4					ALT_FUN_4	//PA4
#define USART3_CTS_PA6					ALT_FUN_4	//PA6
#define TIM14_CH1_PA7					ALT_FUN_4	//PA7
#define I2C1_SCL_PA9					ALT_FUN_4	//PA9
#define I2C1_SDA_PA10					ALT_FUN_4	//PA10
#define USART4_RTS_PA15					ALT_FUN_4	//PA15

#define USART3_CK_PB0					ALT_FUN_4	//PB0
#define USART3_RTS_PB1					ALT_FUN_4	//PB1
#define USART4_CTS_PB7					ALT_FUN_4	//PB7
#define USART3_TX_PB10					ALT_FUN_4	//PB10
#define USART3_RX_PB11					ALT_FUN_4	//PB11
#define USART3_CK_PB12					ALT_FUN_4	//PB12
#define USART3_CTS_PB13					ALT_FUN_4	//PB13
#define USART3_RTS_PB14					ALT_FUN_4	//PB14

//============= ALTERNATE FUNCTION 5 ==================//
#define TIM15_CH1N_PA1					ALT_FUN_5	//PA1
#define TIM16_CH1_PA6					ALT_FUN_5	//PA6
#define TIM17_CH1_PA7					ALT_FUN_5	//PA7

#define TIM17_BKIN_PB4					ALT_FUN_5	//PB4
#define SPI2_NSS_PB9					ALT_FUN_5	//PB9
#define SPI2_SCK_PB10					ALT_FUN_5	//PB10
#define TIM15_BKIN_PB12					ALT_FUN_5	//PB12
#define I2C2_SCL_PB13					ALT_FUN_5	//PB13
#define I2C2_SDA_PB14					ALT_FUN_5	//PB14

//============= ALTERNATE FUNCTION 6 ==================//
#define EVENTOUT_PA6					ALT_FUN_6	//PA6
#define EVENTOUT_PA7					ALT_FUN_6	//PA7

//===========================================================================================//

//=============| Definitions for ADC| ================//

#define sample_time_0	(uint8_t)0x00
#define sample_time_1	(uint8_t)0x01
#define sample_time_2	(uint8_t)0x02
#define sample_time_3	(uint8_t)0x03
#define sample_time_4	(uint8_t)0x04
#define sample_time_5	(uint8_t)0x05
#define sample_time_6	(uint8_t)0x06
#define sample_time_7	(uint8_t)0x07

#define	DISCEN_off		(uint8_t)0x00
#define	AUTOFF_off		(uint8_t)0x00
#define	WAIT_off		(uint8_t)0x00
#define	CONT_off		(uint8_t)0x00
#define	OVRMOD_off		(uint8_t)0x00
#define SCANDIR_off		(uint8_t)0x00

#define	DISCEN_on		(uint8_t)0x01
#define	AUTOFF_on		(uint8_t)0x01
#define	WAIT_on			(uint8_t)0x01
#define	CONT_on			(uint8_t)0x01
#define	OVRMOD_on		(uint8_t)0x01
#define SCANDIR_on		(uint8_t)0x01

#define ADC_EOC_FLAG		(ADC1->ISR & ADC_ISR_EOC)
#define ADC_AWD_FLAG		(ADC1->ISR & ADC_ISR_AWD)
#define ADC_OVR_FLAG		(ADC1->ISR & ADC_ISR_OVR)
#define ADC_EOSEQ_FLAG		(ADC1->ISR & ADC_ISR_EOSEQ)
#define ADC_EOSMP_FLAG		(ADC1->ISR & ADC_ISR_EOSMP)
//====================================================//

//=============| Definitions for USART Specific Functions| ================//
#define USART1_CLK_EN	(RCC->APB1ENR |= RCC_APB2ENR_USART1EN)
#define USART2_CLK_EN	(RCC->APB1ENR |= RCC_APB1ENR_USART2EN)
#define USART3_CLK_EN	(RCC->APB1ENR |= RCC_APB1ENR_USART3EN)
#define USART4_CLK_EN	(RCC->APB1ENR |= RCC_APB1ENR_USART4EN)

#define USART_BDR_48_4800		(usart->BRR = 0x1388)
#define USART_BDR_48_9600		(usart->BRR = 0x9c4)
#define USART_BDR_48_19200		(usart->BRR = 0x4E2)
#define USART_BDR_48_38400		(usart->BRR = 0x341)
#define USART_BDR_48_57600		(usart->BRR = 0x1A1)
#define USART_BDR_48_115200		(usart->BRR = 0xD0)
#define USART_BDR_48_230400		(usart->BRR = 0x68)
#define USART_BDR_48_460800		(usart->BRR = 0x34)
//=========================================================================//

typedef struct {
	GPIO_TypeDef *port;
	uint32_t pin;
	uint32_t mode;
	uint32_t pull;
	uint32_t speed;
	uint32_t alt_func;
} GPIO_TYPE;

typedef enum {
	RISING_EDGE, FALLING_EDGE, RISING_FALLING_EDGE
} edge_select;

typedef enum{
	analog_watchdog_flag, ADC_overrun_flag, end_of_seq_flag, end_of_conv_flag, end_of_samp_flag
} flag_type;

typedef struct{
	I2C_TypeDef *i2c;
	uint32_t	TIMING;
}I2C_CONFIG;

uint16_t map(uint16_t x, uint16_t in_min, uint16_t in_max, uint16_t out_min, uint16_t out_max);

//===============================CLOCK FUNCTION=======================================//
void gpio_clk_en(GPIO_TypeDef *port);
//====================================================================================//

//===============================GPIO CONFIGURATION FUNCTION==========================//
void gpio_config(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode,
		uint32_t pinSpeed, uint32_t pinPUPD, uint32_t PHPL_OD);
//void gpio_input_config(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode, uint32_t pinPUPD);
void gpio_moder(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode);
void gpio_speed(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinMode);
void gpio_PUPD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t pinPUPD);
void gpio_PHPL_OD(GPIO_TypeDef *port, uint32_t pinNumber, uint32_t PHPL_OD);
void gpio_altfn(GPIO_TypeDef *port, uint32_t pinNumber,
		uint32_t alternate_function);
//====================================================================================//

//==============================GPIO OPERATION FUNCTION===============================//
void gpio_write(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t state);
void gpio_toggle(GPIO_TypeDef *port, uint32_t pinNumber);
uint8_t gpio_read(GPIO_TypeDef *port, uint32_t pinNumber);
//====================================================================================//

//=============================GPIO INTERRUPT FUNCTION================================//
void gpio_IT_config(GPIO_TypeDef *port, uint32_t pinNumber, uint8_t edge_sel);
void gpio_IT_EN(uint32_t pinNumber, IRQn_Type irqNumber);
void gpio_IT_DI(uint32_t pinNumber, IRQn_Type irqNumber);
void gpio_IT_SW(uint32_t pinNumber);
void gpio_IT_CLR(uint32_t pinNumber);
//====================================================================================//

//============================= SERIAL PRINTING FUNCTION==============================//
void uart_print_config(uint32_t baudRate, uint8_t clkSpeed);
void print(const char *fmt, ...);
//====================================================================================//

//============================= TIMER CONFIG FUNCTION=================================//
void timer_config(TIM_TypeDef *tim, uint16_t prescaler_val,
		uint16_t auto_reload_val);
void timer_EN(TIM_TypeDef *tim);
void timer_DI(TIM_TypeDef *tim);
void timer_EVENT(TIM_TypeDef *tim);
uint16_t timer_cnt_val(TIM_TypeDef *tim);
void timer_IT_EN(TIM_TypeDef *tim);
void ticks_timer(uint8_t clkSpeed);
uint16_t ticks_val();
void ticks_reset();
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);
//====================================================================================//

//=============================| ADC CONFIG FUNCTION |================================//
void adc_calib();
void adc_ready();
void adc_clk_config();
void adc_sample_time(uint8_t sample_time);
void adc_en();
void adc_read(uint16_t *arr, uint8_t arr_len);
void adc_start();
void adc_stop();
void adc_disable();
void adc_chsel(uint32_t pin);
void adc_config(uint8_t sample_time, uint8_t CONT, uint8_t SCANDIR,
		uint8_t AUTOFF, uint8_t WAIT, uint8_t DISCEN, uint8_t OVRMOD);
void adc_IT_config(uint8_t flag_type);
//====================================================================================//

//=============================| I2C CONFIG FUNCTION |================================//
void I2C_INIT(I2C_TypeDef *i2c, uint32_t timing);
void I2C_byteWrite(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint8_t data);
void I2C_byteRead(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint8_t* data);
void I2C_MultiWrite(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint32_t n, uint8_t* data);
void I2C_MultiRead(I2C_TypeDef *i2c, uint8_t saddr, uint8_t maddr, uint32_t n, uint8_t* data);
//====================================================================================//

//=============================| USART CONFIG FUNCTION |================================//
void USART_CLK_EN(USART_TypeDef *usart);
void USART_PIN_CONFIG(USART_TypeDef *usart, GPIO_TypeDef *tx_port,
		GPIO_TypeDef *rx_port, uint32_t tx_pinNumber, uint32_t rx_pinNumber);
void USART_BDR_SEL(USART_TypeDef *usart, uint8_t clk_speed, uint32_t bd_rate);
void USART_INIT(USART_TypeDef *usart, uint8_t clk_speed, GPIO_TypeDef *tx_port,
		GPIO_TypeDef *rx_port, uint32_t tx_pinNumber, uint32_t rx_pinNumber,
		uint32_t bd_rate);
void USART_IT_EN(USART_TypeDef *usart);
void USART_WRITE(USART_TypeDef *usart, uint8_t *ch, uint32_t len);
uint8_t USART_READ(USART_TypeDef *usart);
//====================================================================================//

//=============================| RCC CONFIG FUNCTION |================================//
void RCC_CONFIG_48MHZ();
//====================================================================================//

#endif /* INC_BML_DRIVER_H_ */
