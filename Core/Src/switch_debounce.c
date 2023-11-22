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

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_SET);    //my test pin for Saleae to watch
	DebounceSwitch1(&userButtonChanged, &userButtonPressed);
	HAL_GPIO_WritePin(GPIOE, GPIO_PIN_7, GPIO_PIN_RESET);  //my test pin for Saleae to watch
}

#define CHECK_MSEC 5 // Read hardware every 5 msec
#define PRESS_MSEC 10 // Stable time before registering pressed
#define RELEASE_MSEC 100 // Stable time before registering released

// This function reads the key state from the hardware.
extern bool RawKeyPressed();

extern bool RawKeyPressed()
{
	return (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0));  //pressing the blue button will connect the pin to Vdd
}

// This holds the debounced state of the key.
bool DebouncedKeyPress = false;
// Service routine called every CHECK_MSEC to
// debounce both edges
void DebounceSwitch1(bool *Key_changed, bool *Key_pressed)
{
	static uint8_t Count = RELEASE_MSEC / CHECK_MSEC;
	bool RawState;
	*Key_changed = false;
	*Key_pressed = DebouncedKeyPress;
	RawState = RawKeyPressed();
	if (RawState == DebouncedKeyPress) {
		// Set the timer which allows a change from current state.
		if (DebouncedKeyPress) Count = RELEASE_MSEC / CHECK_MSEC;
		else Count = PRESS_MSEC / CHECK_MSEC;
	} else {
		// Key has changed - wait for new state to become stable.
		if (--Count == 0) {
			// Timer expired - accept the change.
			DebouncedKeyPress = RawState;
			*Key_changed=true;
			*Key_pressed=DebouncedKeyPress;
			// And reset the timer.
			if (DebouncedKeyPress) Count = RELEASE_MSEC / CHECK_MSEC;
			else Count = PRESS_MSEC / CHECK_MSEC;
		}
	}
}
