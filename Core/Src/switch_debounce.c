/*
 * switch_debounce.c
 *
 *  Created on: Nov 16, 2023
 *      Author: holmb
 */

#include "switch_debounce.h"
#include "level_accel.h"
#include "stm32f3_discovery.h"
#include "tim.h"
#include  <stdbool.h>

bool userButtonChanged;
bool userButtonPressed;

volatile LevelMode_e mode = Horizontal;

LevelMode_e get_current_mode() {
  return mode; // Return the current mode value
}


/* 
* @brief this is a callback function for the interrupt created by the user button rising edge
* @param GPIO_Pin the pin that triggered the interrupt
* @retval None
* @note this function is called by the HAL_GPIO_EXTI_Callback function
* @note this function starts the timer that will be used to debounce the button 5 msec after the button is pressed
* @note this function also sets the userButtonChanged flag to true
* */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	//disable the GPIO interrupt so a second/third bounce doesn't cause another interrupt
	HAL_NVIC_DisableIRQ(EXTI0_IRQn);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
	//HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_CC1);              //make sure no prior interrupts pending
	MX_TIM2_Init();
	__HAL_TIM_CLEAR_FLAG(&htim2, TIM_FLAG_UPDATE);
	HAL_TIM_Base_Start_IT(&htim2);
	//HAL_TIM_OC_Start_IT(&htim2, TIM_CHANNEL_1);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);
	return;
}

/*
* @brief Interrupt callback function for timer 2
* @param htim pointer to a TIM_HandleTypeDef structure that contains a handle to the timer
* @retval None	
*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
	// if we have arrived here, it means the button was pressed once AND that a timer has expired so it's
	// time to check it again (~5ms later)
	HAL_TIM_Base_Stop_IT(&htim2);    //shut off the timer so it doesn't check again and again
	if (HAL_GPIO_ReadPin(USER_BUTTON_GPIO_PORT, USER_BUTTON_PIN)){
		if (mode == Horizontal){
			mode = Vertical;
			//HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
		} else {
			mode = Horizontal;
			//HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);    //my test pin for Saleae to watch
		}
	}
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);  //my test pin for Saleae to watch
	//enable the GPIO edge triggered interrupt again on the way out
	HAL_NVIC_EnableIRQ(EXTI0_IRQn);
	return;
}

