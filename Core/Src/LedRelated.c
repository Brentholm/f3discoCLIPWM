/*
 * LedRelated.c
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */
// Path: Core/Src/LedRelated.c
/**
 * @file LedRelated.c
 * @brief Functions and structures for handling the 8 LED's on the PCB
 */
#include "gpio.h"
#include "LedRelated.h"

/**
 * @brief  array of struct of type CompassLed_t containing the  port, pin, and desired state of the LEDs
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
  * @brief  update states of all 8 LEDs to the ON state.
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

/**
  * @brief  update states of all 8 LEDs to the OFF state.
  * @param  CompassLedArray[] array of struct of type CompassLed_t containing the  port, pin, and desired state of the LEDs
  * @retval None
  */
void LedRoseClearAll(CompassLed_t leds[])
{
	for (int i= 0; i<8; i++)
	{
		leds[i].ledState = LED_OFF;
	}
}
/**
  * @brief  publish the LED states to the actual LEDs.
  * @param  CompassLedArray[] array of struct of type CompassLed_t containing the  port, pin, and desired state of the LEDs
  * @param  delay time in milliseconds to delay after each LED update...just for dramatic effect
  * @retval None
  */
 
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

// Path: Core/Src/LedRelated.c