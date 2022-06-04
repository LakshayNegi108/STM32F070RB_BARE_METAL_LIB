#include "main.h"
#include "BML_DRIVER.h"
#include "st7783.h"
#include "touch.h"
#include "math.h"

uint8_t button1_flag = 0;
uint8_t button1ON_flag = 0;

uint8_t button1_pressed = 0;
uint8_t button1_anichange = 0;
uint8_t button1_color1_changed = 0;
uint8_t button1_color2_changed = 0;
uint8_t button1_drawn = 0;

typedef struct {
	uint16_t x;
	uint16_t y;
	uint16_t h;
	uint16_t w;
	uint16_t r;

	uint16_t ts_x1;
	uint16_t ts_y1;

	uint16_t ts_x2;
	uint16_t ts_y2;

	uint16_t ts_x3;
	uint16_t ts_y3;

	uint16_t ts_x4;
	uint16_t ts_y4;
} button_len;

uint16_t x = 0, y = 0;

void print_touch() {
	for (int a = 0; a < 2; a++) {
		x = TOUCH_VAL('x');
		y = TOUCH_VAL('y');
	}
	print("Pos: %d, %d,\n\r", x, y);

	char buf[20];
	sprintf(buf, "-> %d, %d      ", x, y);
	LCD_SetCursor(3, 310);
	LCD_Printf(buf);
}

void check_button1_pressed(uint16_t ts_x1, uint16_t ts_y1, uint16_t ts_x2,
		uint16_t ts_y2, uint16_t ts_x3, uint16_t ts_y3, uint16_t ts_x4,
		uint16_t ts_y4) {
	if ((x > ts_x1 && y > ts_y1) && (x < ts_x2 && y < ts_y2)
			|| (x > ts_x3 && y > ts_y3) && (x < ts_x4 && y < ts_y4)) {
		button1_pressed = 1;
	} else {
		button1_pressed = 0;
	}
}

void change_button1_animation() {
	if (button1_pressed) {
		if (button1_anichange == 0) {
			button1_anichange = 1;
		} else if (button1_anichange == 1) {
			button1_anichange = 0;
		}
		if (button1_color1_changed == 1) {
			button1_color1_changed = 0;
		} else if (button1_color2_changed == 1) {
			button1_color2_changed = 0;
		}
	}
}

void button_animation1(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t r) {
	LCD_DrawButton1(x, y, w, h, r, EMERALD, BLUE, 1);
	LCD_SetCursor(x + 10, y + 17);
	LCD_SetTextSize(2);
	LCD_SetTextColor(WHITE, EMERALD);
	LCD_Printf("Weather");
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
}
void button_animation2(uint16_t x, uint16_t y, uint16_t w, uint16_t h,
		uint16_t r) {
	LCD_DrawButton1(x, y, w, h, r, NAVY, BLUE, 1);
	LCD_SetCursor(x + 24, y + 17);
	LCD_SetTextSize(2);
	LCD_SetTextColor(WHITE, NAVY);
	LCD_Printf("Time");
	LCD_SetTextSize(1);
	LCD_SetTextColor(WHITE, BLACK);
}

volatile uint32_t tiktik = 0;
volatile uint32_t one_sec = 0;



int main() {
	RCC_CONFIG_48MHZ();
	ticks_timer(48);
	uart_print_config(9600, 48);
	adc_Init();

	button_len Button1;
	Button1.x = 130;
	Button1.y = 10;
	Button1.w = 100;
	Button1.h = 50;
	Button1.r = 7;

	Button1.ts_x1 = 650;
	Button1.ts_y1 = 800;

	Button1.ts_x2 = 900;
	Button1.ts_y2 = 1200;

	Button1.ts_x3 = 500;
	Button1.ts_y3 = 700;

	Button1.ts_x4 = 800;
	Button1.ts_y4 = 1000;

	print("Running\r\n");

	LCD_Begin();
	LCD_SetRotation(0);
	LCD_FillScreen(BLACK);
	Touch_Begin();

	LCD_SetTextColor(WHITE, BLACK);
	LCD_SetTextSize(1);

	while (1) {

		LCD_SetCursor(0, 0);
			print_touch();

		//===============================================================
		check_button1_pressed(Button1.ts_x1, Button1.ts_y1, Button1.ts_x2,
				Button1.ts_y2, Button1.ts_x3, Button1.ts_y3, Button1.ts_x4,
				Button1.ts_y4);
		//===============================================================
		//===============================================================
		change_button1_animation(Button1.x, Button1.y, Button1.w, Button1.h,
				Button1.r);
		//===============================================================
		//===============================================================
		if (button1_anichange == 0) {
			if (button1_color1_changed == 0) {
				button_animation2(Button1.x, Button1.y, Button1.w, Button1.h,
						Button1.r);
				button1_color1_changed = 1;
			}
		} else if (button1_anichange == 1) {
			if (button1_color2_changed == 0) {
				button_animation1(Button1.x, Button1.y, Button1.w, Button1.h,
						Button1.r);
				button1_color2_changed = 1;
			}
		}
		//===============================================================

	}
	return 0;
}
