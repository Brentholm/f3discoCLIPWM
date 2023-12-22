/*
 * tft_display.c
 *
 *  Created on: Dec 16, 2023
 *      Author: holmb
 */
#include "gpio.h"
#include <string.h>
#include <stdio.h>
#include "../st7735/st7735.h"
#include "../st7735/fonts.h"
#include "switch_debounce.h"


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

	ST7735_WriteString(0, 3*10, "Level Up!", Font_11x18, ST7735_GREEN, ST7735_BLACK);
	HAL_Delay(500);
	// ST7735_FillScreen(ST7735_BLACK);
}

void TftDisplayAccelData(LevelMode_e horizOrVertical, AccelCalculations_t results ){
	// initialize strings to hold formatted results
	char str1[20] = "3.14";
	char str2[20] = "42.0";
	static char str1_prev[20];
	static char str2_prev[20];

	if (horizOrVertical == Horizontal){
		sprintf(str1, "vert: %2.1f", results.vert_angle);
		sprintf(str2, "HORZ: %2.1f", results.horiz_angle);
	} else {
		sprintf(str1, "VERT: %2.1f", results.vert_angle);
		sprintf(str2, "horz: %2.1f", results.horiz_angle);
	}
	//ST7735_FillScreen(ST7735_BLACK);
	// instead of blanking the entire screen, write old value as black on black
	// TODO: initialize the first part of string, the label 'horz' or 'vert' and then just black out the numeric parts before updating
	ST7735_WriteString(0, (3*10+3*18), str1_prev, Font_11x18, ST7735_BLACK, ST7735_BLACK);  //font +background = black
	ST7735_WriteString(0, (3*10+3*18), str1,      Font_11x18, ST7735_GREEN, ST7735_BLACK);  //new reading

	ST7735_WriteString(0, (3*10+4*18), str2_prev, Font_11x18, ST7735_BLACK, ST7735_BLACK);  //font +background = black
	ST7735_WriteString(0, (3*10+4*18), str2,      Font_11x18, ST7735_GREEN, ST7735_BLACK);  //new reading

	//strcpy(destination, source);
	//preserve a copy of the old text such that it can be used to black out itself next time through loop
	strcpy(str1_prev, str1);
	strcpy(str2_prev, str2);
}
