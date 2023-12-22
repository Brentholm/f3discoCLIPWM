/*
 * tft_display.h
 *
 *  Created on: Dec 16, 2023
 *      Author: holmb
 */

#ifndef INC_TFT_DISPLAY_H_
#define INC_TFT_DISPLAY_H_



// Function prototypes
void TftDisplay_Init();       // basic splash screen to show the display is working at startup
void TftDisplayAccelData(LevelMode_e currentLevelState, AccelCalculations_t accelValues);


#endif /* INC_TFT_DISPLAY_H_ */
