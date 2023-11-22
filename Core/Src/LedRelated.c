/*
 * LedRelated.c
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */
/**
 * @file LedRelated.c
 * @brief Functions and structures for handling the 8 LED's on the PCB
 */
#include "gpio.h"
#include "LedRelated.h"

/*
CompassLed_t myLedStructArray[8] = {
    {GPIOE, GPIO_PIN_9,  LD3_Red_N,     LED_OFF},
	{GPIOE, GPIO_PIN_10, LD5_Orange_NE, LED_OFF},
	{GPIOE, GPIO_PIN_11, LD7_Green_E,   LED_OFF},
	{GPIOE, GPIO_PIN_12, LD9_Blue_SE,   LED_OFF},
	{GPIOE, GPIO_PIN_13, LD10_Red_S,    LED_OFF},
	{GPIOE, GPIO_PIN_14, LD8_Orange_SW, LED_OFF},
	{GPIOE, GPIO_PIN_15, LD6_Green_W,   LED_OFF},
	{GPIOE, GPIO_PIN_8,  LD4_Blue_NW,   LED_OFF},
};
*/

 

CompassLed_t myLedStructArray[8] = {
		  {GPIOE, GPIO_PIN_9,  LD3_Red_N,     LED_OFF},
		  {GPIOE, GPIO_PIN_10, LD5_Orange_NE, LED_OFF},
		  {GPIOE, GPIO_PIN_11, LD7_Green_E,   LED_OFF},
		  {GPIOE, GPIO_PIN_12, LD9_Blue_SE,   LED_OFF},
		  {GPIOE, GPIO_PIN_13, LD10_Red_S,    LED_OFF},
		  {GPIOE, GPIO_PIN_14, LD8_Orange_SW, LED_OFF},
		  {GPIOE, GPIO_PIN_15, LD6_Green_W,   LED_OFF},
		  {GPIOE, GPIO_PIN_8,  LD4_Blue_NW,   LED_OFF},
  };
/**
  * @brief  update states of all 8 LEDs.
  * @param  CompassLedArray[] array of struct of type CompassLed_t containing the  port, pin, and desired state of the LEDs
  * @retval None
  */
void LedRoseSetAll(CompassLed_t leds[])
{
	for (int i= 0; i<8; i++)
	{
		leds[i].ledState = LED_ON;
	}
}

void LedRoseClearAll(CompassLed_t leds[])
{
	for (int i= 0; i<8; i++)
	{
		leds[i].ledState = LED_OFF;
	}
}

void LedRoseUpdate(CompassLed_t leds[], uint16_t delay)
{
	for (int i = 0; i<8; i++ )
	{
		HAL_GPIO_WritePin(leds[i].ledPort, leds[i].ledPin, leds[i].ledState);
		HAL_Delay(delay);
	}
}


/**
  * @brief  set the desired on/off state of an individual LED.
  * @param  CompassLedArray Struct of type CompassLed_t containing the  port, pin, and desired state of just one particularLED
  * @retval None
  */
void SetLedState(CompassLed_t *led, LedState_e newState)
{
	led->ledState = newState;
}

//old version for comparison:

 /*void LedRoseSet()
 {
	 //turn on the LED's one at a time in clockwise fashion
	 HAL_GPIO_WritePin(GPIOE, LD4_Blue_NW, GPIO_PIN_SET);  //blue, LD4
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD3_Red_N, GPIO_PIN_SET);  //red, LD3
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD5_Orange_NE, GPIO_PIN_SET); //orange, LD5
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD7_Green_E, GPIO_PIN_SET);  //green, LD7
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD9_Blue_SE, GPIO_PIN_SET);  //blue, LD9
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD10_Red_S, GPIO_PIN_SET); //red, LD10
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD8_Orange_SW, GPIO_PIN_SET);  //orange, LD8
	 HAL_Delay(100);
	 HAL_GPIO_WritePin(GPIOE, LD6_Green_W, GPIO_PIN_SET);  //green, LD6

 }
*/
 /*void LedRoseToggle()
 {
	 HAL_GPIO_TogglePin(GPIOE, LD4_Blue_NW);  //blue, LD4
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD3_Red_N);  //red, LD3
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD5_Orange_NE); //orange, LD5
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD7_Green_E);  //green, LD7
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD9_Blue_SE);  //blue, LD9
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD10_Red_S); //red, LD10
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD8_Orange_SW);  //orange, LD8
	 HAL_Delay(100);
	 HAL_GPIO_TogglePin(GPIOE, LD6_Green_W);  //green, LD6
	 HAL_Delay(100);
 }
*/
