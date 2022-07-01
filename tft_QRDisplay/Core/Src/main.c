#include "main.h"
#include "BML_DRIVER.h"
#include "st7783.h"
#include "touch.h"
#include "SDCard.h"
#include <stdbool.h>
#include "fonts.h"
#include "graphics.h"

SPI_HandleTypeDef hspi1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

#define BUFFPIXEL 20

uint16_t x = 0, y = 0;

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

} button_len;

void print_touch() {
	LCD_SetRotation(3);
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
	for (int a = 0; a < 2; a++) {
		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
	}
	print("Pos: %d, %d,\n\r", x, y);

	char buf[20];
	sprintf(buf, "-> %d, %d   ", x, y);
	LCD_SetCursor(5, 230);
	LCD_Printf(buf);
}

uint8_t check_button1_pressed(uint16_t ts_x1, uint16_t ts_y1, uint16_t ts_x2,
		uint16_t ts_y2, uint16_t ts_x3, uint16_t ts_y3, uint16_t ts_x4,
		uint16_t ts_y4) {
	if ((x > ts_x1 && y > ts_y1) && (x < ts_x2 && y < ts_y2)
			|| (x > ts_x3 && y > ts_y3) && (x < ts_x4 && y < ts_y4)) {
		return 1;
	} else {
		return 0;
	}
}

uint8_t checkButtonPressed(uint16_t ts_x1, uint16_t ts_y1, uint16_t ts_x2,
		uint16_t ts_y2) {
	if ((x > ts_x1 && x < ts_x2) && (y > ts_y1 && y < ts_y2)) {
		return 1;
	} else {
		return 0;
	}
}

int main(void) {
//	HAL_Init();

	SystemClock_Config();

	uart_print_config(9600, 48);
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_FATFS_Init();
	ticks_timer(48);

	print("\n\r==========Running==========\r\n");

//	delay_ms(1000); //a short delay is important to let the SD card settle
	ticks_reset();
	while (ticks_val() < 1000)
		;

	sd_mount();
	sd_space();
	sd_readFile("test.txt");
	getBMPImageData("wifi.bmp");

	LCD_Begin();
	LCD_SetRotation(0);
	LCD_FillScreen(BLACK);

//	displayPicGen("QRCodeH.bmp", 100, 60);
//	displayPicGen("wifis.bmp", 100, 60);
	dispWifi(50, 50);

	Touch_Begin();
	LCD_DrawPixel(0, 0, BLACK);
	button_len Button1;
	Button1.x = 130;
	Button1.y = 10;
	Button1.w = 100;
	Button1.h = 50;
	Button1.r = 7;

	Button1.ts_x1 = 750;
	Button1.ts_x2 = 1000;

	Button1.ts_y1 = 350;
	Button1.ts_y2 = 500;

//	LCD_DrawButton1("Hello", 20, 20, 70, 50, 5, YELLOW, BLACK, 1);
	delay_ms(500);
	uint8_t flag = 0;
	sd_deMount();

//	LCD_SetTextSize(2);
//	LCD_SetCursor(50, 100);
//	LCD_SetTextColor(GREEN, BLACK);
//	LCD_Printf("LIGHT");
//	printnewtstr(100, 200, RED, BLACK, &mono12x7, 3, "1dfrf65gr4");
//	printnewtstr(113, 200, RED, BLACK, &mono12x7, 3, "2");
//	printnewtstr(126, 200, RED, BLACK, &mono12x7, 3, ":");
//	printnewtstr(139, 200, RED, BLACK, &mono12x7, 3, "0");
//	printnewtstr(152, 200, RED, BLACK, &mono12x7, 3, "3");

	while (1) {
//		print_touch();
		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
		print("Pos: %d, %d\n\r", x, y);
		if (checkButtonPressed(Button1.ts_x1, Button1.ts_y1, Button1.ts_x2,
				Button1.ts_y2)) {
//			LCD_FillRect(20, 20, 90, 90, PINK);
//			LCD_DrawButton1("Hello", 30, 30, 70, 50, 10, YELLOW, BLACK, 0);
			LCD_SetTextSize(2);
			LCD_SetCursor(50, 100);
			LCD_SetTextColor(YELLOW, BLACK);
			LCD_Printf("LIGHT");
			print("Pressed\n");
			flag = 1;
		} else if (flag == 1) {
//			LCD_FillRect(30, 30, 90, 90, PINK);
//			LCD_DrawButton1("Hello", 20, 20, 70, 50, 10, YELLOW, BLACK, 1);
			LCD_SetTextSize(2);
			LCD_SetCursor(50, 100);
			LCD_SetTextColor(GREEN, BLACK);
			LCD_Printf("LIGHT");
			flag = 0;
		}
	}
}

/**
 * @brief System Clock Configuration
 * @retval None
 */
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
 * @brief SPI1 Initialization Function
 * @param None
 * @retval None
 */
static void MX_SPI1_Init(void) {

	/* USER CODE BEGIN SPI1_Init 0 */

	/* USER CODE END SPI1_Init 0 */

	/* USER CODE BEGIN SPI1_Init 1 */

	/* USER CODE END SPI1_Init 1 */
	/* SPI1 parameter configuration*/
	hspi1.Instance = SPI1;
	hspi1.Init.Mode = SPI_MODE_MASTER;
	hspi1.Init.Direction = SPI_DIRECTION_2LINES;
	hspi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hspi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hspi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hspi1.Init.NSS = SPI_NSS_SOFT;
	hspi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_128;
	hspi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hspi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hspi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hspi1.Init.CRCPolynomial = 7;
	hspi1.Init.CRCLength = SPI_CRC_LENGTH_DATASIZE;
	hspi1.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
	if (HAL_SPI_Init(&hspi1) != HAL_OK) {
		Error_Handler();
	}
	/* USER CODE BEGIN SPI1_Init 2 */

	/* USER CODE END SPI1_Init 2 */

}

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */
static void MX_GPIO_Init(void) {

	/* GPIO Ports Clock Enable */
	gpio_clk_en(PORTA);
	gpio_clk_en(PORTB);
	gpio_clk_en(PORTF);
	gpio_clk_en(PORTC);

	gpio_write(SD_CS_GPIO_Port, SD_CS_Pin, LOW);
	gpio_config(SD_CS_GPIO_Port, SD_CS_Pin, OUTPUT_MODE, LOW_SPEED, DI_PUPD,
	PHPL);

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
