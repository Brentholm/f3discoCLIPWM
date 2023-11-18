/*
 * LedRelated.c
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */
#include "gpio.h"
#include "LedRelated.h"

CompassLed_t myLedStructArray[8] = {
    {GPIOE, LD4_Blue_NW,   LED_ON},
    {GPIOE, LD3_Red_N,     LED_ON},
	{GPIOE, LD5_Orange_NE, LED_ON},
	{GPIOE, LD7_Green_E,   LED_ON},
	{GPIOE, LD9_Blue_SE,   LED_ON},
	{GPIOE, LD10_Red_S,    LED_ON},
	{GPIOE, LD8_Orange_SW, LED_ON},
	{GPIOE, LD6_Green_W,   LED_ON},
};


//todo: make this function take an argument that passes it the array
//then it can be a generic "updater"
void LedRoseSet()
{
	for (int i = 0; i<8; i++ ){
		HAL_GPIO_WritePin(myLedStructArray[i].ledPort, myLedStructArray[i].ledPin, myLedStructArray[i].ledState);
		HAL_Delay(100);
	}
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
 void LedRoseToggle()
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

