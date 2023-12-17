/*
 * tft_display.c
 *
 *  Created on: Dec 16, 2023
 *      Author: holmb
 */
#include "gpio.h"
#include "../st7735/st7735.h"
#include "../st7735/fonts.h"


void TftDisplay_Init(void){
	HAL_GPIO_WritePin(ST7735_LITE_GPIO_Port, ST7735_LITE_Pin, SET);   // turn on the TFT backlight
	ST7735_FillScreen(ST7735_BLACK);      // fill the screen with black to blank it

	// draw a red border around the screen
	for(int x = 0; x < ST7735_WIDTH; x++) {
		ST7735_DrawPixel(x, 0, ST7735_RED);
		ST7735_DrawPixel(x, ST7735_HEIGHT-1, ST7735_RED);
	}

	for(int y = 0; y < ST7735_HEIGHT; y++) {
		ST7735_DrawPixel(0, y, ST7735_RED);
		ST7735_DrawPixel(ST7735_WIDTH-1, y, ST7735_RED);
	}

	// delay a half second before clearing the screen again
	HAL_Delay(500);
	ST7735_FillScreen(ST7735_BLACK);

	ST7735_WriteString(0, 3*10, "Hello Green Turtles", Font_11x18, ST7735_GREEN, ST7735_BLACK);
	HAL_Delay(500);
	// ST7735_FillScreen(ST7735_BLACK);
}
