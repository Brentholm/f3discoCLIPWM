/*
 * LedRelated.h
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */

#ifndef SRC_LEDRELATED_H_
#define SRC_LEDRELATED_H_

#include "gpio.h"

/*
#define LD4_Blue_NW 	(GPIO_PIN_8)
#define LD3_Red_N 		(GPIO_PIN_9)
#define LD5_Orange_NE 	(GPIO_PIN_10)
#define LD7_Green_E		(GPIO_PIN_11)
#define LD9_Blue_SE 	(GPIO_PIN_12)
#define LD10_Red_S 		(GPIO_PIN_13)
#define LD8_Orange_SW 	(GPIO_PIN_14)
#define LD6_Green_W 	(GPIO_PIN_15)

*/

typedef enum
{
	LED_ON = GPIO_PIN_SET,
	LED_OFF = GPIO_PIN_RESET,
	LED_BLINKING,    //to be implemented later
} LedState_e;

// Enum for LED names
typedef enum
{
    LD3_Red_N       = 0,
    LD5_Orange_NE   = 1,
    LD7_Green_E     = 2,
	LD9_Blue_SE     = 3,
	LD10_Red_S      = 4,
	LD8_Orange_SW   = 5,
	LD6_Green_W     = 6,
	LD4_Blue_NW     = 7,
    // Add more names as needed
    TotalLeds       = 8,// A placeholder for the total number of LEDs
} LedName_e;


typedef struct
{
	GPIO_TypeDef* ledPort;
	uint16_t      ledPin;
	LedName_e	  ledName;
	LedState_e    ledState;
} CompassLed_t;


// Declare the array without allocating space (extern)
extern CompassLed_t myLedStructArray[8];



void LedRoseSetAll(CompassLed_t leds[]);
void LedRoseClearAll(CompassLed_t leds[]);
void LedRoseUpdate(CompassLed_t leds[]);

void SetLedState(CompassLed_t singleLed);




#endif /* SRC_LEDRELATED_H_ */
