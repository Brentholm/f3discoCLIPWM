/*
 * LedRelated.h
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */

#ifndef SRC_LEDRELATED_H_
#define SRC_LEDRELATED_H_

#include "gpio.h"
#include "level_accel.h"

// Enum for LED states
typedef enum
{
	LED_ON = GPIO_PIN_SET,
	LED_OFF = GPIO_PIN_RESET,
	LED_BLINKING,    //to be implemented later
} LedState_e;

// Enum for LED names on the compass rose of the F3 Discovery board
// @note this enumeration makes it possible to use a for loop to iterate through the LEDs
// @note ...to keep the code more compact. 
// @note having a name for each LED makes the code more readable, one can use the name as the 'index' that goes inside the brackets
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
    TotalLeds       = 8 // A placeholder for the total number of LEDs
} LedName_e;


// Struct for each LED: its port , pin#, my name for it, and its state
typedef struct
{
	GPIO_TypeDef* ledPort;
	uint16_t      ledPin;
	LedName_e	  ledName;
	LedState_e    ledState;
} CompassLed_t;

// Declare the array for all my LEDs without allocating space (extern)
extern CompassLed_t myLedStructArray[8];

// Function prototypes
void SetLedState(CompassLed_t *led, LedState_e newState); // Set the state of a single LED. Updates the struct, but doesn't update the physical LEDs
void LedRoseSetAll(CompassLed_t leds[]);       // Set all LEDs to ON. Updates the struct, but doesn't update the physical LEDs
void LedRoseClearAll(CompassLed_t leds[]);     // Set all LEDs to OFF. Updates the struct, but doesn't update the physical LEDs
void LedRoseUpdate(CompassLed_t leds[], uint16_t delay);  // Update the physical LEDs to match the struct
void Led_Init(void);
void LedRoseDisplayBubble(LevelMode_e currentLevelState, AccelCalculations_t accelValues); // exercise all 8 LED's in a pinwheel pattern at startup;

#endif /* SRC_LEDRELATED_H_ */
