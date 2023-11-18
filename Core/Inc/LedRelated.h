/*
 * LedRelated.h
 *
 *  Created on: Oct 12, 2023
 *      Author: holmb
 */

#ifndef SRC_LEDRELATED_H_
#define SRC_LEDRELATED_H_

#include "gpio.h"

#define LD4_Blue_NW 	(GPIO_PIN_8)
#define LD3_Red_N 		(GPIO_PIN_9)
#define LD5_Orange_NE 	(GPIO_PIN_10)
#define LD7_Green_E		(GPIO_PIN_11)
#define LD9_Blue_SE 	(GPIO_PIN_12)
#define LD10_Red_S 		(GPIO_PIN_13)
#define LD8_Orange_SW 	(GPIO_PIN_14)
#define LD6_Green_W 	(GPIO_PIN_15)


void LedRoseSet();
void LedRoseToggle();



#endif /* SRC_LEDRELATED_H_ */
