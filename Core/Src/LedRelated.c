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
#include "level_accel.h"
#include "math.h"

#define CLOSE_ENOUGH_THRESHOLD (1.0)
#define ZERO_MS_DELAY (0)
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
 * @brief exercise all 8 LED's in a pinwheel pattern at startup;
 * @param no parameters required
 * @retval none
 */

void Led_Init(){
	LedRoseUpdate(myLedStructArray,0);    // update the physical LED's to their initial state (OFF), with zero delay between each one

	LedRoseSetAll(myLedStructArray);      // set all LEDs to their ON state in the struct
	LedRoseUpdate(myLedStructArray,50);   // update the actual LED state in a pinwheel fashion with 50ms delay between each successive one

	LedRoseClearAll(myLedStructArray);    // set all LEDs to their OFF state in the struct
	LedRoseUpdate(myLedStructArray,50);   // update the actual LED state in a pinwheel fashion with 50ms delay between each successive one
}

/*
 * @brief uses the compass rose to turn on two diametrically opposed LED's, intended to emulate the bubble in a traditional spirit level
 * @note depending on what the current desired state of the level is (whether we're indicating horizontal "level" or vertical "plumb")
 * @note and whether the angle is "close enough" the pair of LED's chose will indicate either "tilted left", "right on" or "tilted right"
 * @note 'fabs' is the floating point absolute function
 *  * @retval none
 */
void LedRoseDisplayBubble(LevelMode_e currentLevelState, AccelCalculations_t accelValues){
	LedRoseClearAll(myLedStructArray); //reset the states of all LEDs to OFF
	switch (currentLevelState) {
	case Horizontal:   //comparing angles to see how close to flat horizontal they are
		if (fabs(accelValues.horiz_angle) < CLOSE_ENOUGH_THRESHOLD){
			SetLedState(&myLedStructArray[LD7_Green_E], LED_ON);   //light "east" and "west" to make a horizontal bar
			SetLedState(&myLedStructArray[LD6_Green_W], LED_ON);
			//break;
		} else if (accelValues.horiz_angle > 0) {
			SetLedState(&myLedStructArray[LD5_Orange_NE], LED_ON); //this pair makes a bar sloping up and to the right
			SetLedState(&myLedStructArray[LD8_Orange_SW], LED_ON);
			//break;
		} else {
			SetLedState(&myLedStructArray[LD9_Blue_SE], LED_ON);   //this pair makes a bar sloping down and to the right
			SetLedState(&myLedStructArray[LD4_Blue_NW], LED_ON);
		} break;
	case Vertical:   //comparing angles to see how close to straight up and down they are
		if (fabs(accelValues.vert_angle) < CLOSE_ENOUGH_THRESHOLD){
			SetLedState(&myLedStructArray[LD3_Red_N], LED_ON);     //light "north" and south to make a vertical bar
			SetLedState(&myLedStructArray[LD10_Red_S], LED_ON);
			//break;
		} else if (accelValues.vert_angle < 0) {
			SetLedState(&myLedStructArray[LD9_Blue_SE], LED_ON);   //this pair makes makes a bar sloping up and to left
			SetLedState(&myLedStructArray[LD4_Blue_NW], LED_ON);   //that is, more counter-clockwise than vertical

			//break;
		} else {
			SetLedState(&myLedStructArray[LD5_Orange_NE], LED_ON);  //this pair makes a bar sloping up and to the right
			SetLedState(&myLedStructArray[LD8_Orange_SW], LED_ON);  //that is, more clockwise than vertical
		} break;
	}
	LedRoseUpdate(myLedStructArray,ZERO_MS_DELAY);  //actually illuminate the intended LEDs; zero delay between GPIO updates
}


/**
  * @brief  update states of all 8 LEDs to the ON state. Does not update actual LEDs; must call LedRoseUpdate() following this
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
  * @brief  update states of all 8 LEDs to the OFF state. Does not update actual LEDs; must call LedRoseUpdate() following this
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
