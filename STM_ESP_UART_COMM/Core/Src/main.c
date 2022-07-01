#include "main.h"
#include "BML_DRIVER.h"
#include "st7783.h"
#include "touch.h"
#include "math.h"
#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <stdio.h>

uint8_t button1_flag = 0;
uint8_t button1ON_flag = 0;

uint8_t button1_pressed = 0;
uint8_t button1_anichange = 0;
uint8_t button1_color1_changed = 0;
uint8_t button1_color2_changed = 0;
uint8_t button1_drawn = 0;

volatile uint32_t tiktik = 0;
volatile uint32_t one_sec = 0;

UART_HandleTypeDef huart2;
UART_HandleTypeDef huart3;

/* USER CODE BEGIN PV */
#define Rx_data_len  20
uint8_t Rx_data[Rx_data_len];  //  creating a buffer of 10 bytes
uint8_t temp_data[5];  //  creating a buffer of 10 bytes
uint8_t pressure_data[5];  //  creating a buffer of 10 bytes
uint8_t humidity_data[5];  //  creating a buffer of 10 bytes
uint8_t wind_data[5];  //  creating a buffer of 10 bytes

uint16_t hrs = 0;
uint16_t min = 0;
uint16_t time_buff[10];
uint16_t delay_checker = 0;
uint16_t sec_checker = 0;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t h;
	uint16_t w;
	uint16_t r;

	uint16_t ts_x1;
	uint16_t ts_y1;

	uint16_t ts_x2;
	uint16_t ts_y2;

	uint16_t ts_x3;
	uint16_t ts_y3;

	uint16_t ts_x4;
	uint16_t ts_y4;
} button_len;

uint16_t x = 0, y = 0;

void print_touch() {
	for (int a = 0; a < 2; a++) {
		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
	}
//	print("Pos: %d, %d,\n\r", x, y);

	char buf[20];
	sprintf(buf, "-> %d, %d      ", x, y);
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
	LCD_SetCursor(3, 310);
	LCD_Printf(buf);
}

void check_button1_pressed(uint16_t ts_x1, uint16_t ts_y1, uint16_t ts_x2,
		uint16_t ts_y2, uint16_t ts_x3, uint16_t ts_y3, uint16_t ts_x4,
		uint16_t ts_y4) {
	if ((x > ts_x1 && y > ts_y1) && (x < ts_x2 && y < ts_y2)
			|| (x > ts_x3 && y > ts_y3) && (x < ts_x4 && y < ts_y4)) {
		button1_pressed = 1;
	} else {
		button1_pressed = 0;
	}
}

void change_button1_animation() {
	if (button1_pressed) {
		if (button1_anichange == 0) {
			button1_anichange = 1;
		} else if (button1_anichange == 1) {
			button1_anichange = 0;
		}
		if (button1_color1_changed == 1) {
			button1_color1_changed = 0;
		} else if (button1_color2_changed == 1) {
			button1_color2_changed = 0;
		}
	}
}

void button_animation1(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t r) {
	LCD_DrawButton1(x, y, w, h, r, EMERALD, BLUE, 1);
	LCD_SetCursor(x + 10, y + 17);
	LCD_SetTextSize(2);
	LCD_SetTextColor(WHITE, EMERALD);
	LCD_Printf("Weather");
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
}
void button_animation2(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t r) {
	LCD_DrawButton1(x, y, w, h, r, NAVY, BLUE, 1);
	LCD_SetCursor(x + 24, y + 17);
	LCD_SetTextSize(2);
	LCD_SetTextColor(WHITE, NAVY);
	LCD_Printf("Time");
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
}

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_USART3_UART_Init(void);
/* USER CODE BEGIN PFP */

void store_data() {
	for (uint8_t i = 0; i < 5; i++) {
		temp_data[i] = Rx_data[i];
		pressure_data[i] = Rx_data[i + 6];
	}
	pressure_data[4] = ' ';
	humidity_data[0] = Rx_data[12];
	humidity_data[1] = Rx_data[13];
	humidity_data[2] = ' ';
	humidity_data[3] = ' ';
	humidity_data[4] = ' ';
}

void display_data() {
	store_data();
	LCD_SetTextSize(2);

	LCD_SetCursor(20, 130);
	LCD_SetTextColor(RED, BLACK);
	LCD_Printf("Temperature:");
	LCD_SetTextColor(BLUE3, BLACK);
	LCD_Printf(temp_data);

	LCD_SetCursor(20, 160);
	LCD_SetTextColor(RED, BLACK);
	LCD_Printf("Pressure:");
	LCD_SetTextColor(BLUE3, BLACK);
	LCD_Printf(pressure_data);

	LCD_SetCursor(20, 190);
	LCD_SetTextColor(RED, BLACK);
	LCD_Printf("Humidity:");
	LCD_SetTextColor(BLUE3, BLACK);
	LCD_Printf(humidity_data);

	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
}

void display_time() {
	LCD_SetTextSize(3);
	LCD_SetTextColor(YELLOW, BLACK);
	LCD_SetCursor(30, 150);
	sprintf(time_buff, " %d:%d:%d PM  ", hrs, min, sec_checker);
	LCD_Printf(time_buff);
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart) {
	HAL_UART_Receive_IT(&huart3, Rx_data, Rx_data_len);
//	store_data(Rx_data);
//	display_temp(Rx_data);

}

int main(void) {
	HAL_Init();

	SystemClock_Config();
	ticks_timer(48);
	uart_print_config(9600, 48);
	adc_Init();

	button_len Button1;
	Button1.x = 130;
	Button1.y = 10;
	Button1.w = 100;
	Button1.h = 50;
	Button1.r = 7;

	Button1.ts_x1 = 650;
	Button1.ts_y1 = 800;

	Button1.ts_x2 = 900;
	Button1.ts_y2 = 1200;

	Button1.ts_x3 = 500;
	Button1.ts_y3 = 700;

	Button1.ts_x4 = 800;
	Button1.ts_y4 = 1000;

	print("Running\r\n");

	hrs = 3;
	min = 23;

	LCD_Begin();
	LCD_SetRotation(0);
	LCD_FillScreen(BLACK);
	Touch_Begin();

	LCD_SetTextColor(WHITE, BLACK);
	LCD_SetTextSize(1);

	MX_GPIO_Init();
	MX_USART2_UART_Init();
	MX_USART3_UART_Init();
	/* USER CODE BEGIN 2 */
	memset(Rx_data, 0, Rx_data_len);
	HAL_UART_Receive_IT(&huart3, Rx_data, Rx_data_len);
	HAL_UART_Transmit(&huart2, "Working\n\r", 10, 10);

	while (1) {

		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
		print("Pos: %d, %d\n\r", x, y);

		delay_checker++;
		if (delay_checker > 1) {
			sec_checker++;
			delay_checker = 0;
		}

		if (sec_checker > 59) {
			if (min > 59) {
				min = 0;
				hrs++;
			} else
				min++;

			if (hrs > 24)
				hrs = 0;
			sec_checker = 0;
		}

//		LCD_SetCursor(0, 0);
//		print_touch();


		//===============================================================
		check_button1_pressed(Button1.ts_x1, Button1.ts_y1, Button1.ts_x2,
				Button1.ts_y2, Button1.ts_x3, Button1.ts_y3, Button1.ts_x4,
				Button1.ts_y4);
		//===============================================================
		//===============================================================
		change_button1_animation(Button1.x, Button1.y, Button1.w, Button1.h,
				Button1.r);
		//===============================================================
		//===============================================================
		if (button1_anichange == 0) {
			if (button1_color1_changed == 0) {
				button_animation2(Button1.x, Button1.y, Button1.w, Button1.h,
						Button1.r);
				button1_color1_changed = 1;
				LCD_FillRect(10, 100, 230, 150, BLACK);
			}
			display_time();
		} else if (button1_anichange == 1) {
			if (button1_color2_changed == 0) {
				button_animation1(Button1.x, Button1.y, Button1.w, Button1.h,
						Button1.r);
				button1_color2_changed = 1;
				LCD_FillRect(10, 100, 230, 150, BLACK);
			}
			display_data();
		}
		//===============================================================

	}
	/* USER CODE END 3 */
}

void SystemClock_Config(void) {
	RCC_OscInitTypeDef RCC_OscInitStruct = { 0 };
	RCC_ClkInitTypeDef RCC_ClkInitStruct = { 0 };

	/** Initializes the RCC Oscillators according to the specified parameters
	 * in the RCC_OscInitTypeDef structure.
	 */
	RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
	RCC_OscInitStruct.HSIState = RCC_HSI_ON;
	RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
	RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
	RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
	RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
	RCC_OscInitStruct.PLL.PREDIV = RCC_PREDIV_DIV1;
	if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK) {
		Error_Handler();
	}
	/** Initializes the CPU, AHB and APB buses clocks
	 */
	RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK
			| RCC_CLOCKTYPE_PCLK1;
	RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
	RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
	RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

	if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK) {
		Error_Handler();
	}
}

/**
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART2_UART_Init(void) {

	/* USER CODE BEGIN USART2_Init 0 */

	/* USER CODE END USART2_Init 0 */

	/* USER CODE BEGIN USART2_Init 1 */

	/* USER CODE END USART2_Init 1 */
	huart2.Instance = USART2;
	huart2.Init.BaudRate = 9600;
	huart2.Init.WordLength = UART_WORDLENGTH_8B;
	huart2.Init.StopBits = UART_STOPBITS_1;
	huart2.Init.Parity = UART_PARITY_NONE;
	huart2.Init.Mode = UART_MODE_TX_RX;
	huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart2.Init.OverSampling = UART_OVERSAMPLING_16;
	huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart2) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART2_Init 2 */

	/* USER CODE END USART2_Init 2 */

}

/**
 * @brief USART3 Initialization Function
 * @param None
 * @retval None
 */
static void MX_USART3_UART_Init(void) {

	/* USER CODE BEGIN USART3_Init 0 */

	/* USER CODE END USART3_Init 0 */

	/* USER CODE BEGIN USART3_Init 1 */

	/* USER CODE END USART3_Init 1 */
	huart3.Instance = USART3;
	huart3.Init.BaudRate = 115200;
	huart3.Init.WordLength = UART_WORDLENGTH_8B;
	huart3.Init.StopBits = UART_STOPBITS_1;
	huart3.Init.Parity = UART_PARITY_NONE;
	huart3.Init.Mode = UART_MODE_TX_RX;
	huart3.Init.HwFlowCtl = UART_HWCONTROL_NONE;
	huart3.Init.OverSampling = UART_OVERSAMPLING_16;
	huart3.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
	huart3.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;
	if (HAL_UART_Init(&huart3) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN USART3_Init 2 */

	/* USER CODE END USART3_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };

	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOC_CLK_ENABLE();
	__HAL_RCC_GPIOF_CLK_ENABLE();
	__HAL_RCC_GPIOA_CLK_ENABLE();

	/*Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

	/*Configure GPIO pin : B1_Pin */
	GPIO_InitStruct.Pin = B1_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_IT_FALLING;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(B1_GPIO_Port, &GPIO_InitStruct);

	/*Configure GPIO pin : LD2_Pin */
	GPIO_InitStruct.Pin = LD2_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LD2_GPIO_Port, &GPIO_InitStruct);

}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
 * @brief  This function is executed in case of error occurrence.
 * @retval None
 */
void Error_Handler(void) {
	/* USER CODE BEGIN Error_Handler_Debug */
	/* User can add his own implementation to report the HAL error return state */
	__disable_irq();
	while (1) {
	}
	/* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
