/*
 * graphics.c
 *
 *  Created on: May 29, 2022
 *      Author: hp
 */

#include "graphics.h"
#include "Pictures.h"

void LCD_DrawButton1(char *c, int16_t x, int16_t y, int16_t w, int16_t h,
		int16_t r, uint16_t color1, uint16_t color2, uint8_t bg_draw) {

	if (bg_draw == 1)
		LCD_FillRoundRect(x + 5, y + 5, w, h, r, color2);

	LCD_FillRoundRect(x, y, w, h, r, color1);
	LCD_DrawRoundRect(x, y, w, h, r, WHITE);
	LCD_SetCursor(x + 6, y + 17);
	LCD_SetTextSize(2);
	LCD_SetTextColor(color2, color1);
	LCD_Printf(c);

}

void LCD_DrawButton2(char *c, int16_t x, int16_t y, int16_t w, int16_t h,
		int16_t r, uint16_t color1, uint16_t color2, uint8_t bg_draw) {

	if (bg_draw == 1)
		LCD_FillRoundRect(x - 3, y - 3, w + 6, h + 6, r, color2);

	LCD_FillRoundRect(x, y, w, h, r, color1);
	LCD_DrawRoundRect(x, y, w, h, r, WHITE);
}

//void Display_QR1(uint16_t x, uint16_t y) {
//	/* Set the rotation that fit the image */
//	LCD_SetRotation(3);
//	uint8_t r, b, g;
//	/* Drawing Image to the LCD */
//	uint64_t k = 0;
//	for (uint32_t i = x + 0; i < x + 60; i++) {
//		for (uint32_t j = y + 60; j > y + 0; j--) {
//			r = qr_code[k++];
//			b = qr_code[k++];
//			g = qr_code[k++];
//			LCD_DrawPixel(i, j, LCD_Color565(g, b, r));
////			print("%X ,", LCD_Color565(g, b, r));
////			print("R: %X, B: %X, G: %X, P: %X // ", r, b, g, LCD_Color565(g, b, r));
//			k++;
//		}
//		print("\n");
//	}
//	LCD_SetRotation(0);
//}

void Display_Picture2(uint16_t x, uint16_t y) {
	/* Set the rotation that fit the image */
	LCD_SetRotation(0);

	/* Drawing Image to the LCD */
	uint64_t k = 0;
	for (uint32_t i = x + 0; i < x + 40; i++) {
		for (uint32_t j = y + 40; j > y + 0; j--) {
			LCD_DrawPixel(i, j, left_arrow[k]);
			k++;
		}
	}
}
