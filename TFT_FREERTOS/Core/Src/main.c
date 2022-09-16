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

UART_HandleTypeDef huart2;

osThreadId defaultTaskHandle;
osThreadId myTask02Handle;
osThreadId myTask03Handle;
osThreadId myTask04Handle;
osThreadId myTask05Handle;
osMessageQId myQueue01Handle;
osSemaphoreId myBinarySem01Handle;
/* USER CODE BEGIN PV */
uint16_t x = 0, y = 0;
bool button1Flag = false;
bool button2Flag = false;
bool button3Flag = false;
bool connectFlag = false;
bool connectbuttontoggleFlag = false;

uint8_t chArray[20] = { 0 };
uint8_t chArray2[20] = { 0 };
uint16_t idx = 0;

uint16_t xl = 0;
uint16_t adcData[4];

char *B1_dispStr[5] = { "Motor", "GPS", "Flight Mode", "Channel", "Position" };
char *B2_dispStr[3] = { "______", " CNTD  ", "DISCNTD" };
char *B3_dispStr[8] = { "PITCH", "ROLL", " THRTL", " YAWN", "F/BWD",
		"LEFT/RIGHT", "ACRTN", "DRCN" };
char *cmdStr[4] = { "AT+", "ID", "CF", "CH" };

uint8_t placeHolder[100] = { 0 };

bool cmdprintFlag = false;
bool cmdrecFlag = false;
bool cnfModeFlag = false;
uint8_t idVar = 0, cnfVar = 0, chVar = 0;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
//static void MX_GPIO_Init(void);
//static void MX_USART2_UART_Init(void);
static void MX_SPI1_Init(void);
void StartDefaultTask(void const *argument);
void StartTask02(void const *argument);
void StartTask03(void const *argument);
void StartTask04(void const *argument);
void StartTask05(void const *argument);

/* USER CODE BEGIN PFP */
void drawScale();
void drawCMDBox();
void drawPinkWhiteBox();
void drawYellowBox();
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
	SystemClock_Config();

	/* USER CODE BEGIN SysInit */

	/* USER CODE END SysInit */

	/* Initialize all configured peripherals */
//  MX_GPIO_Init();
//  MX_USART2_UART_Init();
	MX_SPI1_Init();
	MX_FATFS_Init();
	/* USER CODE BEGIN 2 */

//=================== SD Card Select Pin ==================================//
	gpio_config(PORTB, 6, OUTPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_write(PORTB, 6, LOW);
//=========================================================================//

//======================== USART Pin Config ===============================//
	USART_INIT(USART2, 48, PORTA, PORTA, 2, 3, 9600);
	USART_IT_EN(USART2, 0, 1, 0);
	USART_INIT(USART3, 48, PORTC, PORTC, 10, 11, 9600);
	USART_IT_EN(USART3, 0, 1, 0);
	USART_WRITE(USART2, "Working\n", 8);
	USART_WRITE(USART3, "Working\n", 8);
//=========================================================================//
	LCD_Begin();
	LCD_SetRotation(1);
//	uint16_t bgColor = LCD_Color565(172, 0, 255);
	LCD_FillScreen(BLACK);
	Touch_Begin();

//======================== Analog Pin Config ===============================//
	gpio_config(PORTC, 4, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTC, 5, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTC, 2, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTC, 3, ANALOG_MODE, LOW_SPEED, DI_PUPD, PHPL);
//=========================================================================//

//======================== GPIO IT Pin Config ===============================//
	gpio_config(PORTA, 11, INPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_IT_config(PORTA, 11, RISING_FALLING_EDGE);
	gpio_IT_EN(11, EXTI4_15_IRQn);
	gpio_config(PORTA, 12, INPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_IT_config(PORTA, 12, RISING_FALLING_EDGE);
	gpio_IT_EN(12, EXTI4_15_IRQn);
	gpio_config(PORTC, 8, INPUT_MODE, LOW_SPEED, DI_PUPD, PHPL);
	gpio_IT_config(PORTC, 8, RISING_EDGE);
	gpio_IT_EN(8, EXTI4_15_IRQn);
//===========================================================================//

//=================== || CMD BOX || ==============//
	drawCMDBox();
//=================================================//

//=================== || Connect/DisConnect Button || ====================//
//	LCD_DrawButton1("Connected", 18, 80, 160, 40, 2, GREEN, WHITE, 1, 25, 11,
//			2);
	//========================================================================//

	//===================== Pink White Box ====================//
	drawPinkWhiteBox();
	//=============================================================//

	//=================== || Yellow BOX || ==============================////
	drawYellowBox();
	//===================================================////

	HAL_Delay(1000);

//	sd_mount();
//	sd_space();
//	sd_deMount();

//	displayPicGen("QRCodeH.bmp", 60, 20);
//	displayPicGen("moon.bmp", 130, 20);
	/* USER CODE END 2 */

	/* USER CODE BEGIN RTOS_MUTEX */
	/* add mutexes, ... */
	/* USER CODE END RTOS_MUTEX */

	/* Create the semaphores(s) */
	/* definition and creation of myBinarySem01 */
	osSemaphoreDef(myBinarySem01);
	myBinarySem01Handle = osSemaphoreCreate(osSemaphore(myBinarySem01), 1);

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

/* USER CODE BEGIN 4 */

void USART2_IRQHandler() {
	uint8_t chr;
//	USART_WRITE(USART2, "Hello\n", 6);
	if (USART2->ISR & USART_ISR_RXNE) {
		chr = USART2->RDR;
		if (chr == '\n' || idx > 19) {
//			USART_WRITE(USART3, chArray, idx);
//			USART_WRITE(USART3, '\n', 1);
			strcpy(placeHolder, chArray);
			USART_WRITE(USART2, placeHolder, strlen(placeHolder));
			USART_WRITE(USART2, '\n', 1);
			cmdrecFlag = true;
			idx = 0;
			memset(chArray, 0, 20);
		} else {
			chArray[idx] = chr;
			idx++;
		}
	}
}

void USART3_4_IRQHandler() {
	uint8_t chr;
	if (USART3->ISR & USART_ISR_RXNE) {
		chr = USART3->RDR;
		if (chr == '\n' || idx > 19) {
			USART_WRITE(USART2, chArray2, idx);
			USART_WRITE(USART2, '\n', 1);
			idx = 0;
			memset(chArray2, 0, 20);
		} else {
			chArray2[idx] = chr;
			idx++;
		}
	}
}

void EXTI4_15_IRQHandler() {
	if (gpio_IT_CHK(8)) {
		button1Flag = true;
		gpio_IT_CLR(8);
	} else if (gpio_IT_CHK(11)) {
		button2Flag = true;
		gpio_IT_CLR(9);
	} else if (gpio_IT_CHK(12)) {
		button3Flag = true;
		gpio_IT_CLR(9);
	}
}

void drawScale() {
	uint16_t frontX, midX, backX;
	uint16_t posY1, posY2, lineSize1, lineSize2, lineSize3;
	frontX = 20;
	midX = 115;
	backX = 209;
	posY1 = 150;
	posY2 = 190;
	lineSize1 = 10;
	lineSize2 = 7;
	lineSize3 = 5;

	LCD_DrawFastVLine(frontX, posY1 - 11, lineSize1, BLACK);
	LCD_DrawFastVLine(frontX, posY2 - 11, lineSize1, BLACK);
	LCD_DrawFastVLine(midX, posY1 - 11, lineSize1, BLACK);
	LCD_DrawFastVLine(midX, posY2 - 11, lineSize1, BLACK);
	LCD_DrawFastVLine(backX, posY1 - 11, lineSize1, BLACK);
	LCD_DrawFastVLine(backX, posY2 - 11, lineSize1, BLACK);

	for (uint8_t i = 1; i < 3; i++) {
		LCD_DrawFastVLine(frontX + 31 * i, posY1 - 8, lineSize2, BLACK);
		LCD_DrawFastVLine(frontX + 31 * i, posY2 - 8, lineSize2, BLACK);
		LCD_DrawFastVLine(midX + 31 * i, posY1 - 8, lineSize2, BLACK);
		LCD_DrawFastVLine(midX + 31 * i, posY2 - 8, lineSize2, BLACK);
	}

	for (uint8_t i = 1; i < 5; i++) {
		LCD_DrawFastVLine(frontX + 6 * i, posY1 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(frontX + 31 + 6 * i, posY1 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(frontX + 61 + 6 * i, posY1 - 6, lineSize3, BLACK);

		LCD_DrawFastVLine(midX + 6 * i, posY1 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(midX + 31 + 6 * i, posY1 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(midX + 61 + 6 * i, posY1 - 6, lineSize3, BLACK);

		LCD_DrawFastVLine(frontX + 6 * i, posY2 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(frontX + 31 + 6 * i, posY2 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(frontX + 61 + 6 * i, posY2 - 6, lineSize3, BLACK);

		LCD_DrawFastVLine(midX + 6 * i, posY2 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(midX + 31 + 6 * i, posY2 - 6, lineSize3, BLACK);
		LCD_DrawFastVLine(midX + 61 + 6 * i, posY2 - 6, lineSize3, BLACK);
	}

	LCD_SetTextSize(1);
	LCD_SetTextColor(BLACK, YELLOW);
	LCD_SetCursor(midX - 15, posY1 + 23);
	LCD_Printf(B3_dispStr[0]);
	LCD_SetCursor(midX - 10, posY2 + 23);
	LCD_Printf(B3_dispStr[1]);
	LCD_SetCursor(frontX - 10, posY1 + 23);
	LCD_Printf("-100");
	LCD_SetCursor(backX - 15, posY1 + 23);
	LCD_Printf("+100");
	LCD_SetCursor(frontX - 10, posY2 + 23);
	LCD_Printf("-100");
	LCD_SetCursor(backX - 15, posY2 + 23);
	LCD_Printf("+100");

}

void drawCMDBox() {
	LCD_DrawRoundRect(10, 10, 180, 119, 2, LIGHTGRAY);
	LCD_DrawButton1("COMMAND", 135, 15, 50, 17, 2, LIGHTGRAY, BLACK, 0, 5, 5,
			1);
	LCD_DrawButton1("ERROR", 135, 35, 50, 17, 2, RED, BLACK, 0, 5, 5, 1);

	LCD_SetTextSize(1);
	LCD_SetTextColor(GREEN, BLACK);

	LCD_DrawFastHLine(10, 58, 180, LIGHTGRAY);
	for (uint8_t i = 0; i < 4; i++) {
		LCD_DrawFastHLine(10, 73 + i * 14, 180, LIGHTGRAY);
	}
	LCD_DrawFastVLine(90, 59, 70, LIGHTGRAY);

	LCD_SetTextColor(ORANGE, BLACK);
	for (uint8_t i = 0; i < 5; i++) {
		LCD_SetCursor(20, 63 + i * 14);
		LCD_Printf(B1_dispStr[i]);
	}

	LCD_SetTextColor(GREEN, BLACK);
	LCD_SetCursor(20, 20);
	LCD_Printf("                   ");
	LCD_SetCursor(20, 20);
	LCD_Printf("Device CNF MODE(DI)");
	LCD_SetCursor(20, 30);
	LCD_Printf("..$ ");
	LCD_SetCursor(20, 45);
	LCD_Printf("Battery:78 percent");
}

void drawPinkWhiteBox() {

	//=================== || PINK BOX || ==============//
	LCD_FillRoundRect(200, 10, 120, 115, 3, NAVY);
	//=================================================//

	//=================== ||PINK WHITE BOX || ==============//
	LCD_FillRoundRect(210, 20, 100, 90, 1, WHITE);
	//======================================================//

	LCD_SetTextSize(2);
	LCD_SetTextColor(BLACK, WHITE);

	LCD_SetCursor(220, 30);
	LCD_Printf("  ID: ");

	LCD_SetTextColor(BLUE3, WHITE);
	LCD_SetCursor(220, 50);
	LCD_Printf(B2_dispStr[0]);

	LCD_SetCursor(220, 70);
	LCD_SetTextColor(BLACK, WHITE);
	LCD_Printf("STATUS:");

	LCD_SetCursor(220, 90);
	LCD_SetTextColor(RED, WHITE);
	LCD_Printf(B2_dispStr[2]);
}

void drawYellowBox() {
	LCD_FillRoundRect(0, 130, 320, 110, 1, YELLOW);

	LCD_DrawHBorder(0, 130, 320, BROWN1, 5);
	LCD_DrawHBorder(0, 234, 320, BROWN1, 5);

	LCD_DrawVBorder(0, 130, 110, BROWN1, 5);
	LCD_DrawVBorder(225, 130, 110, BROWN1, 5);

	//=================== || Yellow Side Data box || =================//
	LCD_SetCursor(235, 139);
	LCD_SetTextSize(2);
	LCD_SetTextColor(BLACK, YELLOW);
	LCD_Printf(B3_dispStr[2]);

	//	LCD_DrawFastHLine(230, 125, 70, BLACK);
	LCD_FillRect(235, 157, 80, 25, WHITE);

	LCD_SetCursor(235, 188);
	//	LCD_SetTextSize(2);
	LCD_SetTextColor(BLACK, YELLOW);
	LCD_Printf(B3_dispStr[3]);
	LCD_FillRect(235, 207, 80, 25, WHITE);

	//=============================================================//

	//=================== || Graphs || =================//
	LCD_DrawRect(20, 150, 190, 20, BLACK);
	LCD_DrawRect(20, 190, 190, 20, BLACK);

	drawScale();

	LCD_DrawFastVLine(115, 150, 20, BLACK);
	LCD_DrawFastVLine(115, 190, 20, BLACK);
	LCD_DrawFastVLine(114, 150, 20, BLACK);
	LCD_DrawFastVLine(114, 190, 20, BLACK);
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

		adc_read(adcData, 4);
		adcData[0] = map(adcData[0], 0, 4095, 0, 500);
		adcData[1] = map(adcData[1], 0, 4095, 0, 500);
		adcData[2] = map(adcData[2], 0, 4095, 0, 100);
		adcData[3] = map(adcData[3], 0, 4095, 0, 360);

//		x = TOUCH_VAL('x');
//		y = TOUCH_VAL('y');
//		print("%d, %d\n", TOUCH_VAL('x'), TOUCH_VAL('y'));
		osDelay(50);
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

	for (;;) {
		LCD_SetTextSize(2);
		osSemaphoreWait(myBinarySem01Handle, osWaitForever);
		LCD_SetCursor(240, 162);
		LCD_SetTextColor(BLACK, WHITE);
		//		sprintf(placeHolder, "%d", adcData[0]);
		//		LCD_Printf("    ");
		LCD_SetCursor(240, 162);

		if (adcData[2] >= 1000)
			LCD_Printf(" %d", adcData[2]);
		else if (adcData[2] >= 100)
			LCD_Printf(" %d ", adcData[2]);
		else
			LCD_Printf("  %d ", adcData[2]);

		LCD_SetCursor(240, 212);
		LCD_SetTextColor(BLACK, WHITE);

		int16_t degreeVal;
		if (adcData[3] > 180) {
			degreeVal = adcData[3] - 180;
		} else if (adcData[3] <= 180) {
			degreeVal = (180 - adcData[3]) * (-1);
		}
		if (degreeVal >= 100)
			LCD_Printf(" %d", degreeVal);
		else if (degreeVal >= 0)
			LCD_Printf("  %d ", degreeVal);
		else
			LCD_Printf(" %d ", degreeVal);

		//==================================================//
		if ((cmdprintFlag == true) && (cmdrecFlag == true)) {
			uint8_t plLen = strlen(placeHolder);
			LCD_SetCursor(20, 30);
			LCD_SetTextSize(1);
			LCD_SetTextColor(GREEN, BLACK);
			LCD_Printf("--             ");
			if (plLen < 16) {
				LCD_SetCursor(20, 30);
				LCD_Printf(placeHolder);
			} else {
				LCD_SetCursor(20, 30);
				LCD_Printf("--             ");
			}
			if (plLen > 3) {
				if (placeHolder[0] == 'A' && placeHolder[1] == 'T'
						&& placeHolder[2] == '+') {
					char tempC[10] = { 0 };
					if (placeHolder[3] == 'I' && placeHolder[4] == 'D') {// ID Char read
//						uint8_t idchar[5] = "12345";
						B2_dispStr[0] = (placeHolder + 5);
						LCD_SetTextSize(2);
						LCD_SetTextColor(BLUE3, WHITE);
						LCD_SetCursor(220, 50);
						LCD_Printf(B2_dispStr[0]);
						LCD_DrawButton1("  OK", 135, 35, 50, 17, 2, GREEN,
						BLACK, 0, 5, 5, 1);
						USART_WRITE(USART2, "OK\n", 3);
						connectFlag = true;
					} else if (placeHolder[3] == 'C' && placeHolder[4] == 'F') {
						LCD_DrawButton1("  OK", 135, 35, 50, 17, 2, GREEN,
						BLACK, 0, 5, 5, 1);
						USART_WRITE(USART2, "OK\n", 3);
					} else if (placeHolder[3] == 'C' && placeHolder[4] == 'H') {

						LCD_DrawButton1("  OK", 135, 35, 50, 17, 2, GREEN,
						BLACK, 0, 5, 5, 1);
						USART_WRITE(USART2, "OK\n", 3);
					} else {
						LCD_DrawButton1("ERROR", 135, 35, 50, 17, 2, RED, BLACK,
								0, 5, 5, 1);
						USART_WRITE(USART2, "ERROR\n", 6);
					}
				} else {
					LCD_DrawButton1("ERROR", 135, 35, 50, 17, 2, RED, BLACK, 0,
							5, 5, 1);
					USART_WRITE(USART2, "ERROR\n", 6);
				}

			} else if (plLen <= 3) {
				if (placeHolder[0] == 'A' && placeHolder[1] == 'T') {
					USART_WRITE(USART2, "OK\n", 3);
					LCD_DrawButton1("  OK", 135, 35, 50, 17, 2, GREEN, BLACK, 0,
							5, 5, 1);
				} else if (placeHolder[0] != 'A') {
					LCD_DrawButton1("ERROR", 135, 35, 50, 17, 2, RED, BLACK, 0,
							5, 5, 1);
					USART_WRITE(USART2, "ERROR\n", 6);
				}
			}
			cmdrecFlag = false;
		}
		//==================================================//
		if (button3Flag) {
//			cnfModeFlag ^= cnfModeFlag;
			LCD_SetTextSize(1);
			LCD_SetTextColor(GREEN, BLACK);
			LCD_SetCursor(20, 20);
			LCD_Printf("                   ");
			LCD_SetCursor(20, 20);
			if (cnfModeFlag) {
				LCD_Printf("Device CNF MODE(DI)");
				cnfModeFlag = false;
				cmdprintFlag = false;
			} else {
				LCD_Printf("Device CNF MODE(EN)");
				cnfModeFlag = true;
				cmdprintFlag = true;
			}
			button3Flag = false;

		}
		osSemaphoreRelease(myBinarySem01Handle);
		osDelay(50);
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
		osSemaphoreWait(myBinarySem01Handle, osWaitForever);
		int16_t w1, w2;
		uint16_t color1, color2;
		if (adcData[0] > 250 && adcData[0] < 501) {
			w1 = map(adcData[0], 251, 500, 0, 92);
			if (w1 <= 35 && w1 > 0)
				color1 = PINK;
			else if (w1 <= 75 && w1 > 35)
				color1 = ORANGE;
			else if (w1 < 92 && w1 > 75)
				color1 = RED;
			LCD_FillRect(116, 150 + 1, w1, 20 - 2, color1);
			LCD_FillRect(116 + w1, 150 + 1, 210 - 118 - w1, 20 - 2, YELLOW);
			LCD_FillRect(21, 150 + 1, 94, 20 - 2, YELLOW);
		} else if (adcData[0] <= 250 && adcData[0] >= 0) {
			w1 = map(adcData[0], 0, 250, 0, 92);
			LCD_FillRect(116, 150 + 1, 93, 20 - 2, YELLOW);
			LCD_FillRect(21, 150 + 1, w1, 20 - 2, YELLOW);
			if (w1 <= 20 && w1 > 0)
				color1 = NAVY;
			else if (w1 <= 58 && w1 > 20)
				color1 = BLUE;
			else if (w1 < 92 && w1 > 58)
				color1 = CYAN;
			LCD_FillRect(21 + w1, 150 + 1, 94 - w1, 20 - 2, color1);
		}

		if (adcData[1] > 250 && adcData[1] < 501) {
			w2 = map(adcData[1], 251, 500, 0, 92);
			if (w2 <= 35 && w2 > 0)
				color2 = PINK;
			else if (w2 <= 75 && w2 > 35)
				color2 = ORANGE;
			else if (w2 < 92 && w2 > 75)
				color2 = RED;
			LCD_FillRect(116, 190 + 1, w2, 20 - 2, color2);
			LCD_FillRect(116 + w2, 190 + 1, 210 - 118 - w2, 20 - 2, YELLOW);
			LCD_FillRect(21, 190 + 1, 94, 20 - 2, YELLOW);
		} else if (adcData[1] <= 250 && adcData[1] >= 0) {
			w2 = map(adcData[1], 0, 250, 0, 92);
			LCD_FillRect(116, 190 + 1, 93, 20 - 2, YELLOW);
			LCD_FillRect(21, 190 + 1, w2, 20 - 2, YELLOW);
			if (w2 <= 20 && w2 > 0)
				color2 = NAVY;
			else if (w2 <= 58 && w2 > 20)
				color2 = BLUE;
			else if (w2 < 92 && w2 > 58)
				color2 = CYAN;
			LCD_FillRect(21 + w2, 190 + 1, 94 - w2, 20 - 2, color2);
		}

		if (button1Flag == true) {
			button1Flag = false;
		}
		if (button2Flag == true) {
			USART_WRITE(USART2, "Button2 Ok\n", 11);
			if (connectFlag) {
				if (connectbuttontoggleFlag) {
					LCD_SetCursor(220, 90);
					LCD_SetTextColor(RED, WHITE);
					LCD_Printf(B2_dispStr[2]);
					connectbuttontoggleFlag = false;
				} else {
					LCD_SetCursor(220, 90);
					LCD_SetTextColor(GREEN, WHITE);
					LCD_Printf(B2_dispStr[1]);
					connectbuttontoggleFlag = true;
				}
			}
			button2Flag = false;
		}
		if (button3Flag == true) {
			USART_WRITE(USART2, "Button3 Ok\n", 11);
			//			button3Flag = false;
		}

		osSemaphoreRelease(myBinarySem01Handle);
		osDelay(10);
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
//		xl++;

		osDelay(500);
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
