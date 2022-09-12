/*
 * graphics.h
 *
 *  Created on: May 29, 2022
 *      Author: hp
 */

#ifndef INC_GRAPHICS_H_
#define INC_GRAPHICS_H_

#include "st7783.h"
//#include "touch.h"

//typedef struct {
//	uint16_t x;
//	uint16_t y;
//	uint16_t h;
//	uint16_t w;
//	uint16_t r;
//} button_len;

void LCD_DrawButton1(char *c,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t bgColor, uint16_t textColor, uint8_t bg_draw, uint16_t xPadding, uint16_t yPadding, uint8_t textSize);
void LCD_DrawButton2(char *c,int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color1, uint16_t color2, uint8_t bg_draw);
void Display_Picture1(uint16_t x, uint16_t y);
void Display_Picture2(uint16_t x, uint16_t y);

void LCD_DrawHBorder(int16_t x, int16_t y, int16_t w, uint16_t color, int16_t BorderSize);
void LCD_DrawVBorder(int16_t x, int16_t y, int16_t h, uint16_t color, int16_t BorderSize);

#endif /* INC_GRAPHICS_H_ */
