/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file           : main.c
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.
 *
 * This software is licensed under terms that can be found in the LICENSE file
 * in the root directory of this software component.
 * If no LICENSE file comes with this software, it is provided AS-IS.
 *
 ******************************************************************************
 */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "cmsis_os.h"
#include "fatfs.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "BML_DRIVER.h"
#include "st7783.h"
//#include "SDCard.h"
#include <stdbool.h>
#include "fonts.h"
#include "graphics.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
SPI_HandleTypeDef hspi1;

//UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;
osMessageQId myQueue01Handle;
/* USER CODE BEGIN PV */
uint16_t x = 0, y = 0;
uint8_t flag_1 = 0;

uint8_t chArray[20] = { 0 };
uint16_t idx = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_GPIO_Init(void);
static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
void StartDefaultTask(void const *argument);
void StartTask02(void const *argument);
void StartTask03(void const *argument);
void StartTask04(void const *argument);
void StartTask05(void const *argument);

/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
 * @brief  The application entry point.
 * @retval int
 */
int main(void) {
	/* USER CODE BEGIN 1 */

	/* USER CODE END 1 */

	/* MCU Configuration--------------------------------------------------------*/

	/* Reset of all peripherals, Initializes the Flash interface and the Systick. */
	HAL_Init();

	/* USER CODE BEGIN Init */

	/* USER CODE END Init */

	/* Configure the system clock */
	RCC_CONFIG_48MHZ();
//  SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_USART2_UART_Init();
	MX_SPI1_Init();
	MX_FATFS_Init();
	/* USER CODE BEGIN 2 */

//	MX_GPIO_Init();
//  MX_USART2_UART_Init();
//	USART_INIT(USART2, 48, PORTA, PORTA, 2, 3, 9600);
//	gpio_config(PORTA, 5, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
//=================== SD Card Select Pin ==================================//
	gpio_config(PORTB, 6, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_write(PORTB, 6, LOW);
//=========================================================================//
	USART_INIT(USART2, 48, PORTA, PORTA, 2, 3, 9600);
	USART_IT_EN(USART2, 0, 1, 0);

//	gpio_config(port, pinNumber, pinMode, pinSpeed, pinPUPD, PHPL_OD);


	LCD_Begin();
	LCD_SetRotation(1);
	LCD_FillScreen(BLACK);
	Touch_Begin();

	//=================== || CMD BOX || ==============//
	LCD_DrawRoundRect(10, 10, 180, 35, 2, LIGHTGRAY);
	LCD_DrawButton1("COMMAND:ERROR", 105, 50, 85, 17, 2, LIGHTGRAY, RED, 0, 5, 5, 1);
	//=================================================//

	//=================== || Connect/DisConnect Button || ====================//
	LCD_DrawButton1("Connect", 18, 80, 160, 40, 2, GREEN, WHITE, 1, 35, 11, 2);
	//========================================================================//

	//=================== || PINK BOX || ==============//
	LCD_FillRoundRect(200, 10, 120, 115, 3, PINK);
	//=================================================//

	//=================== ||PINK WHITE BOX || ==============//
	LCD_FillRoundRect(210, 20, 100, 90, 1, WHITE);
	//======================================================//

	//=====================Pink White Box Data ====================//

	LCD_SetTextSize(2);
	LCD_SetCursor(220, 30);
	LCD_SetTextColor(BLACK, WHITE);
	LCD_Printf("Prophyr");

	LCD_SetCursor(220, 60);
	LCD_SetTextColor(BLACK, WHITE);
	LCD_Printf("Prop");

	//=============================================================//

	//=================== || Yellow BOX || ==============================////
	LCD_FillRoundRect(0, 130, 320, 110, 1, YELLOW);

	LCD_DrawHBorder(0, 130, 320, BROWN1, 5);
	LCD_DrawHBorder(0, 234, 320, BROWN1, 5);

	LCD_DrawVBorder(0, 130, 110, BROWN1, 5);
	LCD_DrawVBorder(225, 130, 110, BROWN1, 5);

	//=================== || Yellow Side Data box || =================//
	LCD_SetCursor(240, 139);
	LCD_SetTextSize(2);
	LCD_SetTextColor(BLACK, YELLOW);
	LCD_Printf("X-AXIS");

	//	LCD_DrawFastHLine(230, 125, 70, BLACK);
	LCD_FillRect(235, 157, 80, 25, WHITE);

	LCD_SetCursor(240, 188);
	//	LCD_SetTextSize(2);
	LCD_SetTextColor(BLACK, YELLOW);
	LCD_Printf("Y-AXIS");
	LCD_FillRect(235, 207, 80, 25, WHITE);

	LCD_SetCursor(240, 162);
	LCD_SetTextColor(BLACK, WHITE);
	LCD_Printf("Value1");
	LCD_SetCursor(240, 212);
	LCD_SetTextColor(BLACK, WHITE);
	LCD_Printf("Value2");
	//=============================================================//

	//=================== || Graphs || =================//
	LCD_DrawRect(20, 150, 190, 20, BLACK);
	LCD_DrawRect(20, 190, 190, 20, BLACK);

	LCD_DrawFastVLine(190, 150, 20, RED);
	LCD_DrawFastVLine(190, 190, 20, RED);

	LCD_DrawFastVLine(150, 150, 20, ORANGE);

	LCD_DrawFastVLine(150, 190, 20, ORANGE);

	//	LCD_DrawFastVLine(116, 150, 20, PINK);
	//	LCD_DrawFastVLine(116, 190, 20, PINK);

	LCD_DrawFastVLine(115, 150, 20, BLACK);
	LCD_DrawFastVLine(115, 190, 20, BLACK);
	LCD_DrawFastVLine(116, 150, 20, BLACK);
	LCD_DrawFastVLine(116, 190, 20, BLACK);

	//	LCD_DrawFastVLine(114, 150, 20, GREEN);
	//	LCD_DrawFastVLine(114, 190, 20, GREEN);

	LCD_DrawFastVLine(80, 150, 20, CYAN);
	LCD_DrawFastVLine(80, 190, 20, CYAN);

	LCD_DrawFastVLine(40, 150, 20, NAVY);
	LCD_DrawFastVLine(40, 190, 20, NAVY);

	//===================================================//
	//===================================================////

	HAL_Delay(1000);

	sd_mount();
	sd_space();

//	displayPicGen("QRCodeH.bmp", 60, 20);
	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* USER CODE BEGIN RTOS_SEMAPHORES */
	/* add semaphores, ... */
	/* USER CODE END RTOS_SEMAPHORES */

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	/* USER CODE END RTOS_TIMERS */

	/* Create the queue(s) */
	/* definition and creation of myQueue01 */
	osMessageQDef(myQueue01, 16, uint16_t);
	myQueue01Handle = osMessageCreate(osMessageQ(myQueue01), NULL);

	/* USER CODE BEGIN RTOS_QUEUES */
	/* add queues, ... */
	/* USER CODE END RTOS_QUEUES */

	/* Create the thread(s) */
	/* definition and creation of defaultTask */
	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	/* definition and creation of myTask02 */
	osThreadDef(myTask02, StartTask02, osPriorityIdle, 0, 128);
	myTask02Handle = osThreadCreate(osThread(myTask02), NULL);

	/* definition and creation of myTask03 */
	osThreadDef(myTask03, StartTask03, osPriorityIdle, 0, 128);
	myTask03Handle = osThreadCreate(osThread(myTask03), NULL);

	/* definition and creation of myTask04 */
	osThreadDef(myTask04, StartTask04, osPriorityIdle, 0, 128);
	myTask04Handle = osThreadCreate(osThread(myTask04), NULL);

	/* definition and creation of myTask05 */
	osThreadDef(myTask05, StartTask05, osPriorityIdle, 0, 128);
	myTask05Handle = osThreadCreate(osThread(myTask05), NULL);

	/* USER CODE BEGIN RTOS_THREADS */
	/* add threads, ... */
	/* USER CODE END RTOS_THREADS */

	/* Start scheduler */
	osKernelStart();

	/* We should never get here as control is now taken by the scheduler */
	/* Infinite loop */
	/* USER CODE BEGIN WHILE */

	while (1) {
		/* USER CODE END WHILE */

		/* USER CODE BEGIN 3 */
//		displayPicGen("QRCodeH.bmp", 60, 20);
//	  USART_WRITE(USART2, "Running\n", 8);
	}
	/* USER CODE END 3 */
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
 * @brief USART2 Initialization Function
 * @param None
 * @retval None
 */

/**
 * @brief GPIO Initialization Function
 * @param None
 * @retval None
 */

/* USER CODE BEGIN 4 */

void USART2_IRQHandler() {
	uint8_t chr;
//	USART_WRITE(USART2, "Hello\n", 6);
	if (USART2->ISR & USART_ISR_RXNE) {
		chr = USART2->RDR;
		if (chr == '\n' || idx > 19) {
			USART_WRITE(USART2, chArray, idx);
			USART_WRITE(USART2, '\n', 1);
//			LCD_SetCursor(20, 20);
//			LCD_Printf(chArray);
			idx = 0;
			memset(chArray, 0, 20);
		} else {
			chArray[idx] = chr;
			idx++;
		}
	}
}

/* USER CODE END 4 */

/* USER CODE BEGIN Header_StartDefaultTask */
/**
 * @brief  Function implementing the defaultTask thread.
 * @param  argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const *argument) {
	/* USER CODE BEGIN 5 */
	/* Infinite loop */

	for (;;) {
		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
//		print("%d, %d\n", TOUCH_VAL('x'), TOUCH_VAL('y'));
		osDelay(10);
	}

	/* USER CODE END 5 */
}

/* USER CODE BEGIN Header_StartTask02 */
/**
 * @brief Function implementing the myTask02 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask02 */
void StartTask02(void const *argument) {
	/* USER CODE BEGIN StartTask02 */
	/* Infinite loop */
//	displayPicGen("moon.bmp", 60, 160);
	uint16_t x = 0;
	LCD_SetCursor(20, 20);
	LCD_SetTextSize(2);
	LCD_SetTextColor(GREEN, BLACK);
	LCD_Printf("..$          ");
	for (;;) {

		LCD_SetCursor(20, 20);
		LCD_SetTextSize(2);
		LCD_SetTextColor(GREEN, BLACK);
		LCD_Printf("..$%d", x);
		x++;
		osDelay(500);
	}
	/* USER CODE END StartTask02 */
}

/* USER CODE BEGIN Header_StartTask03 */
/**
 * @brief Function implementing the myTask03 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask03 */
void StartTask03(void const *argument) {
	/* USER CODE BEGIN StartTask03 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartTask03 */
}

/* USER CODE BEGIN Header_StartTask04 */
/**
 * @brief Function implementing the myTask04 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask04 */
void StartTask04(void const *argument) {
	/* USER CODE BEGIN StartTask04 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartTask04 */
}

/* USER CODE BEGIN Header_StartTask05 */
/**
 * @brief Function implementing the myTask05 thread.
 * @param argument: Not used
 * @retval None
 */
/* USER CODE END Header_StartTask05 */
void StartTask05(void const *argument) {
	/* USER CODE BEGIN StartTask05 */
	/* Infinite loop */
	for (;;) {
		osDelay(1);
	}
	/* USER CODE END StartTask05 */
}

/**
 * @brief  Period elapsed callback in non blocking mode
 * @note   This function is called  when TIM7 interrupt took place, inside
 * HAL_TIM_IRQHandler(). It makes a direct call to HAL_IncTick() to increment
 * a global variable "uwTick" used as application time base.
 * @param  htim : TIM handle
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
	/* USER CODE BEGIN Callback 0 */

	/* USER CODE END Callback 0 */
	if (htim->Instance == TIM7) {
		HAL_IncTick();
	}
	/* USER CODE BEGIN Callback 1 */

	/* USER CODE END Callback 1 */
}

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
