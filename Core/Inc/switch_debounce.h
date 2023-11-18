/*
 * switch_debounce.h
 *
 *  Created on: Nov 16, 2023
 *      Author: holmb
 */

#ifndef INC_SWITCH_DEBOUNCE_H_
#define INC_SWITCH_DEBOUNCE_H_

#include "gpio.h"
#include "tim.h"
#include <stdbool.h>

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim);
void DebounceSwitch1(bool *Key_changed, bool *Key_pressed);


#endif /* INC_SWITCH_DEBOUNCE_H_ */
