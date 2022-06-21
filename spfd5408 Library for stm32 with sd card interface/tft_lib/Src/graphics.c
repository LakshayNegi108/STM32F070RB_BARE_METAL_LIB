/*
 * graphics.c
 *
 *  Created on: May 29, 2022
 *      Author: hp
 */

#include "graphics.h"



void LCD_DrawButton1(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color1, uint16_t color2, uint8_t bg_draw) {

	if (bg_draw == 1)
		LCD_FillRoundRect(x + 5, y + 5, w, h, r, color2);

	LCD_FillRoundRect(x, y, w, h, r, color1);
	LCD_DrawRoundRect(x, y, w, h, r, WHITE);
}

void LCD_DrawButton2(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color1, uint16_t color2, uint8_t bg_draw) {

	if (bg_draw == 1)
		LCD_FillRoundRect(x - 3, y - 3, w + 6, h + 6, r, color2);

	LCD_FillRoundRect(x, y, w, h, r, color1);
	LCD_DrawRoundRect(x, y, w, h, r, WHITE);
}

void Display_Picture1(uint16_t x, uint16_t y)
{
	/* Set the rotation that fit the image */
	LCD_SetRotation(1);

	/* Drawing Image to the LCD */
	uint64_t k = 0;
	for(uint32_t i = x + 0; i < x + 40; i++)
	{
		for(uint32_t j = y + 40; j > y + 0; j--)
		{
			LCD_DrawPixel(i, j, temperature_icon_40x40[k]);
			k++;
		}
	}
	LCD_SetRotation(0);
}

void Display_Picture2(uint16_t x, uint16_t y)
{
	/* Set the rotation that fit the image */
	LCD_SetRotation(0);

	/* Drawing Image to the LCD */
	uint64_t k = 0;
	for(uint32_t i = x + 0; i < x + 40; i++)
	{
		for(uint32_t j = y + 40; j > y + 0; j--)
		{
			LCD_DrawPixel(i, j, left_arrow[k]);
			k++;
		}
	}
}
