/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
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
#include "i2c.h"
#include "spi.h"
#include "tim.h"
#include "usart.h"
#include "gpio.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "stm32f3_discovery_accelerometer.h"
#include "console.h"
#include "LedRelated.h"
#include "level_accel.h"
#include "switch_debounce.h"
#include "../st7735/st7735.h"
#include "../st7735/fonts.h"

/*
//new for the ST7735 TFT display
#include "../st7735/st7735.h"
#include "../st7735/fonts.h"
*/
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

/* USER CODE BEGIN PV */




/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
static void MX_NVIC_Init(void);
/* USER CODE BEGIN PFP */
void USART1_SendString(const char* str);
int __io_putchar(int ch);
int __io_getchar(int ch);
int my_getchar(void);

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
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
  MX_GPIO_Init();
  MX_I2C1_Init();
  MX_SPI1_Init();
  MX_USART1_UART_Init();
  MX_TIM3_Init();
  MX_TIM2_Init();
  MX_SPI2_Init();

  /* Initialize interrupts */
  MX_NVIC_Init();
  /* USER CODE BEGIN 2 */
  
  LedRoseUpdate(myLedStructArray,0);    // update the physical LED's to their initial state (OFF), with zero delay between each one

  LedRoseSetAll(myLedStructArray);      // set all LEDs to their ON state in the struct
  LedRoseUpdate(myLedStructArray,50);   // update the actual LED state in a pinwheel fashion with 50ms delay between each one
  
  LedRoseClearAll(myLedStructArray);    // set all LEDs to their OFF state in the struct
  LedRoseUpdate(myLedStructArray,50);   // update the actual LED state in a pinwheel fashion with 50ms delay between each one

  ST7735_Init();                        // initialize the TFT display

  HAL_GPIO_WritePin(ST7735_LITE_GPIO_Port, ST7735_LITE_Pin, SET);   // turn on the TFT backlight
  ST7735_FillScreen(ST7735_BLACK);      // fill the screen with black to blank it

  // draw a red border around the screen
  for(int x = 0; x < ST7735_WIDTH; x++) {
	  ST7735_DrawPixel(x, 0, ST7735_RED);
	  ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
  }

  for(int y = 0; y < ST7735_HEIGHT; y++) {
	  ST7735_DrawPixel(0, y, ST7735_RED);
	  ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
  }

  // delay a half second before clearing the screen again
  HAL_Delay(500);
  ST7735_FillScreen(ST7735_BLACK);

  ST7735_WriteString(0, 3*10, "Hello Green Turtles", Font_11x18, ST7735_GREEN, ST7735_BLACK);
  HAL_Delay(500);
  // ST7735_FillScreen(ST7735_BLACK);

  HAL_TIM_PWM_Start(&htim3, TIM_CHANNEL_1);  //pwm on pin PC6 just for fun - it's on the lower right corner of F3Disco board
  //don't start this here; it will get started when the button press ISR/callback fires
  //HAL_TIM_Base_Start_IT(&htim2);            // use this timer's rollover to cause interrupt that will check switch condition
    	  	  	  	  	  	  		    	  // the code to handle this event is in switch_debounce.c


  // exercise the console code
  USART1_SendString("Hello, World!\r\n");
  printf("Hi Brent\r\n");

  // initialize the onboard accelerometer 
  BSP_ACCELERO_Init();

  int16_t accelData[3] = {0};
  BSP_ACCELERO_GetXYZ(accelData);

  // practice putting a rounded float to the screen
  float myfloat = 3.14159;
  char str[6] = "3.14";
  char str2[6] = "999.9";
  ST7735_WriteString(0, (3*10+2*18), str, Font_11x18, ST7735_GREEN, ST7735_BLACK);
  // format float for printing as a string with two decimal places
  sprintf(str2, "%3f", myfloat);
  ST7735_WriteString(0, (3*10+3*18), str2, Font_11x18, ST7735_GREEN, ST7735_BLACK);
  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */

  while (1)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */

	  ConsoleInit();
#define READINGSTOAVERAGE 3
	  ReadAccelDataArray(rawAccelData,  accelDataArray, READINGSTOAVERAGE);
      AverageAccelData(accelDataArray,  &accelMath, READINGSTOAVERAGE);


	  while(1)
	  {
		  ConsoleProcess();
	  }

  }

  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
  RCC_PeriphCLKInitTypeDef PeriphClkInit = {0};

  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI|RCC_OSCILLATORTYPE_HSE;
  RCC_OscInitStruct.HSEState = RCC_HSE_BYPASS;
  RCC_OscInitStruct.HSEPredivValue = RCC_HSE_PREDIV_DIV1;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
  RCC_OscInitStruct.PLL.PLLMUL = RCC_PLL_MUL6;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }

  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
  RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
  PeriphClkInit.PeriphClockSelection = RCC_PERIPHCLK_USART1|RCC_PERIPHCLK_I2C1;
  PeriphClkInit.Usart1ClockSelection = RCC_USART1CLKSOURCE_PCLK2;
  PeriphClkInit.I2c1ClockSelection = RCC_I2C1CLKSOURCE_HSI;
  if (HAL_RCCEx_PeriphCLKConfig(&PeriphClkInit) != HAL_OK)
  {
    Error_Handler();
  }
}

/**
  * @brief NVIC Configuration.
  * @retval None
  */
static void MX_NVIC_Init(void)
{
  /* EXTI0_IRQn interrupt configuration */
  HAL_NVIC_SetPriority(EXTI0_IRQn, 0, 0);
  HAL_NVIC_EnableIRQ(EXTI0_IRQn);
}

/* USER CODE BEGIN 4 */
void USART1_SendString(const char* str) {
	HAL_UART_Transmit(&huart1, (uint8_t*)str, strlen(str), HAL_MAX_DELAY);
}
/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
/*PUTCHAR_PROTOTYPE
{
   Place your implementation of fputc here
   e.g. write a character to the USART1 and Loop until the end of transmission
  HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);

  return ch;
}*/

// these two functions are redefines that I added per Daniel
int __io_putchar(int ch){
	if (HAL_UART_Transmit(&huart1, (uint8_t*)&ch, 1, 0xFFFF) != HAL_OK)
		return -1;
	return 1;
}


/*
int __io_getchar(void){
	int c;
	HAL_UART_Receive(&huart1, (uint8_t*)&c, 1, 0xFFFF);
	return c;
}
*/




/*int my_getchar(void) {
	      return __io_getchar();
	  }*/
/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
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
