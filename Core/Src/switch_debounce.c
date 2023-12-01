/*
 * switch_debounce.c
 *
 *  Created on: Nov 16, 2023
 *      Author: holmb
 */

#include "switch_debounce.h"
#include  <stdbool.h>

bool userButtonChanged;
bool userButtonPressed;

/*
* @brief Interrupt callback function for timer 2
* @param htim pointer to a TIM_HandleTypeDef structure that contains a handle to the timer
* @retval None	
*/

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
	// todo: write code to check the button state
	// and to start a timer in one-shot mode to start a debounce timer to check the button state again after ~20 msec

	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);  //my test pin for Saleae to watch
}

// this callback starts the timer
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
	HAL_TIM_Base_Start_IT(&htim2);
	HAL_Delay(1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
}
