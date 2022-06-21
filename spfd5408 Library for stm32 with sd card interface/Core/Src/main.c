#include "main.h"
#include "BML_DRIVER.h"
#include "st7783.h"
#include "touch.h"
#include "SDCard.h"
#include <stdbool.h>

SPI_HandleTypeDef hspi1;

void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_SPI1_Init(void);

//const unsigned int back_icon_40x40[];

#define BUFFPIXEL 20

void getBMPImageData(char *file) {
	uint16_t result16;
	uint32_t result32;
	int offset = 0;
//	char file[] = "miniwoof.bmp";
	sd_openFile(file);
	result16 = sd_read16bits(file, offset);
	print("Identifier: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Size: %x\n", result32);
	offset += 4;
	result16 = sd_read16bits(file, offset);
	print("reserverd: %x\n", result16);
	offset += 2;
	result16 = sd_read16bits(file, offset);
	print("reserved: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Offset: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Header Size: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Width_px: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Height_px: %x\n", result32);
	offset += 4;
	result16 = sd_read16bits(file, offset);
	print("No. of Color Planes: %x\n", result16);
	offset += 2;
	result16 = sd_read16bits(file, offset);
	print("Bits per pixel: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Compression: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Image size(bytes): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("X resolution(PPM): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Y resolution(PPM): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("No. of colors: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Important colors: %x\n", result32);
	offset += 4;
	sd_closeFile();
}

//void displayPic(char *c) {
//	sd_openFile(c);
//	uint32_t row, col, picWidth, picHeight;
//	uint8_t offsetPointer = sd_read8(c, 10);
//	uint32_t result, offsetVal = 0;
//	uint8_t r1, r2, r3;
//	uint8_t color_buf[60];
//	uint16_t pixel_buf[20];
//	uint16_t color_buf_val = 0;
//	uint16_t pixel_count = 0;
//
//	offsetVal = 0;
//	picWidth = sd_read32(c, 18);
//	picHeight = sd_read32(c, 22);
//
//	f_lseek(c, offsetPointer);
//	LCD_SetCursor(0, 0);
//	for (row = 0; row < picWidth; row++) {
//		for (col = 0; col < picHeight; col++) {
//			f_gets(color_buf, 60, &fil);
//
//			r1 = color_buf[++color_buf_val];
//			r2 = color_buf[++color_buf_val];
//			r3 = color_buf[++color_buf_val];
//
//			pixel_buf[pixel_count] = LCD_Color565(r1, r2, r3);
//			pixel_count++;
//			if(pixel_count >= 20)
//			{
////				LCD_SetCursor(row, col);
//				LCD_pushColors(pixel_buf, 20, true);
//				pixel_count = 0;;
//			}
//
//			offsetVal += 60;
//			f_lseek(c, offsetPointer + offsetVal);
//			col += 19;
//		}
//	}
//	sd_closeFile();
//}

#define B	BLACK
#define W	PURPLE

uint16_t leftArrow[] = {
  /*Pixel format: Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
		        B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,W,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,W,W,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,B,B,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,W,
				B,B,B,B,B,B,B,B,B,B,W,W,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,W,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,W,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,W,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,W,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,W,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
				B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,B,
};


int main(void) {
//	HAL_Init();

	SystemClock_Config();

	uart_print_config(9600, 48);
	MX_GPIO_Init();
	MX_SPI1_Init();
	MX_FATFS_Init();
	ticks_timer(48);

	print("\n\r==========Running==========\r\n");

	delay_ms(1000); //a short delay is important to let the SD card settle

	sd_mount();
	sd_space();

	sd_readFile("test.txt");

	print("%X\n", sd_read32("arrow.txt", 0));
	print("%X\n", sd_read32("arrow.txt", 72));
	print("%X\n", sd_read32("arrow.txt", 76));
	print("%X\n", sd_read32("arrow.txt", 80));
	print("%X\n", sd_read32("arrow.txt", 77));
	print("%X\n", sd_read32("arrow.txt", 79));
	print("%X\n", sd_read32("arrow.txt", 84));
	print("%X\n", sd_read32("arrow.txt", 88));
	print("%X\n", sd_read32("arrow.txt", 92));
	print("%X\n", sd_read32("arrow.txt", 96));

	LCD_Begin();
	LCD_SetRotation(0);
	LCD_FillScreen(BLACK);
	LCD_DrawPixel(104, 156, RED);
	Display_Picture2(65, 37);

	sd_deMount();

	while (1) {
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
