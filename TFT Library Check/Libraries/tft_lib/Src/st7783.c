/*
 * STM7783.c
 *
 * Created: Mar 15, 2015
 * 
 * Grafic LCD Function (Chip=ST7783)
 *
 * This code has been taken from the Adafruit TFT Library and modified
 * for use with TFT Shields / Modules
 * For original code / licensing please refer to
 * https://github.com/adafruit/TFTLCD-Library
 *
 * This code has been taken from Smoke And Wires
 * for use with TFT Shields / Modules
 * For original code / licensing please refer to
 * http://www.smokeandwires.co.nz
 *
 */
#include "st7783.h"

//#include "main.h"
//#include <stdlib.h>
//#include <stdarg.h>
//#include <stdio.h>
//#include <stdbool.h>

////#include "stm32f0xx_hal.h"
//#include "glcdfont.h"
//#include "stm32f070xb.h"




#define TFTWIDTH   240
#define TFTHEIGHT  320

#define TFTLCD_DELAY 0xFF

uint8_t cursor_y = 0, cursor_x = 0;
uint8_t textsize = 1;
uint16_t textcolor = 0xffff, textbgcolor = 0xFFFF;
uint8_t wrap = true;
uint8_t _cp437 = false;
uint8_t rotation = 0;

#define pgm_read_byte(addr) (*(const unsigned char *)(addr))
#define pgm_read_word(addr) (*(const unsigned short *)(addr))
#define pgm_read_pointer(addr) ((void *)pgm_read_word(addr))

// GPIO to data bus pin connections
// ---- PORT Pin ---     --- Data ----
// GPIOA, GPIO_PIN_9  -> BIT 0
// GPIOC, GPIO_PIN_7  -> BIT 1
// GPIOA, GPIO_PIN_10 -> BIT 2
// GPIOB, GPIO_PIN_3  -> BIT 3
// GPIOB, GPIO_PIN_5  -> BIT 4
// GPIOB, GPIO_PIN_4  -> BIT 5
// GPIOB, GPIO_PIN_10 -> BIT 6
// GPIOA, GPIO_PIN_8  -> BIT 7

#define LCD_CS_PIN  0	// PB0 -> A3 // Chip Select goes to Analog 3
#define LCD_CD_PIN  4	// PA4 -> A2 // Command/Data goes to Analog 2
#define LCD_WR_PIN  1	// PA1 -> A1 // LCD Write goes to Analog 1
#define LCD_RD_PIN  0	// PA0 -> A0 // LCD Read goes to Analog 0
#define LCD_RST_PIN 1	// PC1 -> RESET

#define LCD_CS_GPIO_PORT  GPIOB
#define LCD_CS_HIGH()     gpio_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, HIGH)
#define LCD_CS_LOW()      gpio_write(LCD_CS_GPIO_PORT, LCD_CS_PIN, LOW)

#define LCD_RD_GPIO_PORT  GPIOA
#define LCD_RD_HIGH()      gpio_write(LCD_RD_GPIO_PORT, LCD_RD_PIN, HIGH)
#define LCD_RD_LOW()       gpio_write(LCD_RD_GPIO_PORT, LCD_RD_PIN, LOW)

#define LCD_WR_GPIO_PORT  GPIOA
#define LCD_WR_HIGH()	   gpio_write(LCD_WR_GPIO_PORT, LCD_WR_PIN, HIGH)
#define LCD_WR_LOW()       gpio_write(LCD_WR_GPIO_PORT, LCD_WR_PIN, LOW)

#define LCD_CD_GPIO_PORT  GPIOA
#define LCD_CD_HIGH()      gpio_write(LCD_CD_GPIO_PORT, LCD_CD_PIN, HIGH)
#define LCD_CD_LOW()       gpio_write(LCD_CD_GPIO_PORT, LCD_CD_PIN, LOW)

#define LCD_RST_GPIO_PORT GPIOC
#define LCD_RST_HIGH()     gpio_write(LCD_RST_GPIO_PORT, LCD_RST_PIN, HIGH)
#define LCD_RST_LOW()      gpio_write(LCD_RST_GPIO_PORT, LCD_RST_PIN, LOW)

#define LCD_WR_STROBE() { LCD_WR_LOW(); delay(1); LCD_WR_HIGH(); delay(1); }

#define swap(a, b) { int16_t t = a; a = b; b = t; }

static int16_t m_width;
static int16_t m_height;
static int16_t m_cursor_x;
static int16_t m_cursor_y;

static uint16_t m_textcolor;
static uint16_t m_textbgcolor;
static uint8_t m_textsize;
static uint8_t m_rotation;
static uint8_t m_wrap;

// Initialization commands
static const uint16_t ST7781_regValues[] = { 0x0001, 0x0100, 0x0002, 0x0700,
		0x0003, 0x1030, 0x0008, 0x0302, 0x0009, 0x0000, 0x000A, 0x0008,
		//*******POWER CONTROL REGISTER INITIAL*******//
		0x0010, 0x0790, 0x0011, 0x0005, 0x0012, 0x0000, 0x0013, 0x0000,
		//delayms(50,
		//********POWER SUPPPLY STARTUP 1 SETTING*******//
		0x0010, 0x12B0,
		// delayms(50,
		0x0011, 0x0007,
		//delayms(50,
		//********POWER SUPPLY STARTUP 2 SETTING******//
		0x0012, 0x008C, 0x0013, 0x1700, 0x0029, 0x0022,
		// delayms(50,
		//******GAMMA CLUSTER SETTING******//
		0x0030, 0x0000, 0x0031, 0x0505, 0x0032, 0x0205, 0x0035, 0x0206, 0x0036,
		0x0408, 0x0037, 0x0000, 0x0038, 0x0504, 0x0039, 0x0206, 0x003C, 0x0206,
		0x003D, 0x0408,
		// -----------DISPLAY WINDOWS 240*320-------------//
		0x0050, 0x0000, 0x0051, 0x00EF, 0x0052, 0x0000, 0x0053, 0x013F,
		//-----FRAME RATE SETTING-------//
		0x0060, 0xA700, 0x0061, 0x0001, 0x0090,
		0x0033, //RTNI setting
		//-------DISPLAY ON------//
		0x0007, 0x0133, 0x0001, 0x0100, 0x0002, 0x0700, 0x0003, 0x1030, 0x0008,
		0x0302, 0x0009, 0x0000, 0x000A, 0x0008,
		//*******POWER CONTROL REGISTER INITIAL*******//
		0x0010, 0x0790, 0x0011, 0x0005, 0x0012, 0x0000, 0x0013, 0x0000,
		//delayms(50,
		//********POWER SUPPPLY STARTUP 1 SETTING*******//
		0x0010, 0x12B0,
		// delayms(50,
		0x0011, 0x0007,
		// delayms(50,
		//********POWER SUPPLY STARTUP 2 SETTING******//
		0x0012, 0x008C, 0x0013, 0x1700, 0x0029, 0x0022,
		// delayms(50,
		//******GAMMA CLUSTER SETTING******//
		0x0030, 0x0000, 0x0031, 0x0505, 0x0032, 0x0205, 0x0035, 0x0206, 0x0036,
		0x0408, 0x0037, 0x0000, 0x0038, 0x0504, 0x0039, 0x0206, 0x003C, 0x0206,
		0x003D, 0x0408,
		// -----------DISPLAY WINDOWS 240*320-------------//
		0x0050, 0x0000, 0x0051, 0x00EF, 0x0052, 0x0000, 0x0053, 0x013F,
		//-----FRAME RATE SETTING-------//
		0x0060, 0xA700, 0x0061, 0x0001, 0x0090, 0x0033, //RTNI setting
		//-------DISPLAY ON------//
		0x0007, 0x0133, };

void delay(unsigned int t) {
	for (; t > 0; t--) {
		__asm("nop");
	}
}

/**
 * \brief GPIO Initialization
 * 
 * \param 
 * 
 * \return void
 */
static void GPIO_Init(void) {
	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	__GPIOC_CLK_ENABLE()
	;
	__GPIOA_CLK_ENABLE()
	;
	__GPIOB_CLK_ENABLE()
	;

	/*Configure GPIO pins : PC1 PC7 */
	gpio_config(PORTC, 1, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTC, 7, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);

	/*Configure GPIO pins : PA0 PA1 PA4 PA8 PA9 PA10 */
	gpio_config(PORTA, 0, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 1, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 4, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 8, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 9, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTA, 10, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);

	/*Configure GPIO pins : PB0 PB3 PB4 PB5 PB10 */
	gpio_config(PORTB, 0, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTB, 3, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTB, 4, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTB, 5, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
	gpio_config(PORTB, 10, OUTPUT_MODE, HIGH_SPEED, DI_PUPD, PHPL);
}

/**
 * \brief LCD Initialization
 * 
 * \param 
 * 
 * \return void
 */
void LCD_Begin(void) {
	m_width = TFTWIDTH;
	m_height = TFTHEIGHT;
	m_rotation = 0;
	m_cursor_y = m_cursor_x = 0;
	m_textsize = 4;
	m_textcolor = m_textbgcolor = 0xFFFF;
	m_wrap = 1;

	uint8_t i = 0;
	uint16_t a, d;

	GPIO_Init();

	LCD_Reset();

	LCD_CS_LOW();

	while (i < sizeof(ST7781_regValues) / sizeof(uint16_t)) {
		a = ST7781_regValues[i++];
		d = ST7781_regValues[i++];
		if (a == TFTLCD_DELAY) {
			delay(d);
		} else {
			LCD_WriteRegister16(a, d);
		}
	}

	LCD_SetRotation(m_rotation);
	LCD_SetAddrWindow(0, 0, TFTWIDTH - 1, TFTHEIGHT - 1);
}

/**
 * \brief Calucalte 16Bit-RGB
 * 
 * \param r	Red
 * \param g	Green
 * \param b	Blue
 * 
 * \return uint16_t	16Bit-RGB
 */
uint16_t LCD_Color565(uint8_t r, uint8_t g, uint8_t b) {
	return ((r & 0xF8) << 8) | ((g & 0xFC) << 3) | (b >> 3);
}

/**
 * \brief Draws a point at the specified coordinates
 * 
 * \param x		x-Coordinate
 * \param y		y-Coordinate
 * \param color	Color
 * 
 * \return void
 */
void LCD_DrawPixel(int16_t x, int16_t y, uint16_t color) {
	// Clip
	if ((x < 0) || (y < 0) || (x >= TFTWIDTH) || (y >= TFTHEIGHT))
		return;

	LCD_CS_LOW();

	int16_t t;
	switch (m_rotation) {
	case 1:
		t = x;
		x = TFTWIDTH - 1 - y;
		y = t;
		break;
	case 2:
		x = TFTWIDTH - 1 - x;
		y = TFTHEIGHT - 1 - y;
		break;
	case 3:
		t = x;
		x = y;
		y = TFTHEIGHT - 1 - t;
		break;
	}

	LCD_WriteRegister16(0x0020, x);
	LCD_WriteRegister16(0x0021, y);
	LCD_WriteRegister16(0x0022, color);

	LCD_CS_HIGH();
}

/**
 * \brief Draws a line connecting the two points specified by the coordinate pairs
 * 
 * \param x0	The x-coordinate of the first point
 * \param y0	The y-coordinate of the first point
 * \param x1	The x-coordinate of the second point
 * \param y1	The y-coordinate of the second point.
 * \param color	Color
 * 
 * \return void
 */
void LCD_DrawLine(int16_t x1, int16_t y1, int16_t x2, int16_t y2,
		uint16_t color) {
	// Bresenham's algorithm - thx wikpedia

	int16_t steep = abs(y2 - y1) > abs(x2 - x1);
	if (steep) {
		swap(x1, y1);
		swap(x2, y2);
	}

	if (x1 > x2) {
		swap(x1, x2);
		swap(y1, y2);
	}

	int16_t dx, dy;
	dx = x2 - x1;
	dy = abs(y2 - y1);

	int16_t err = dx / 2;
	int16_t ystep;

	if (y1 < y2) {
		ystep = 1;
	} else {
		ystep = -1;
	}

	for (; x1 <= x2; x1++) {
		if (steep) {
			LCD_DrawPixel(y1, x1, color);
		} else {
			LCD_DrawPixel(x1, y1, color);
		}
		err -= dy;
		if (err < 0) {
			y1 += ystep;
			err += dx;
		}
	}
}

/**
 * \brief Draws a horizontal line
 *
 * \param x			The x-coordinate of the first point
 * \param y			The y-coordinate of the first point
 * \param length	Length of the line
 * \param color	Color
 * 
 * \return void
 */
void LCD_DrawFastHLine(int16_t x, int16_t y, int16_t length, uint16_t color) {
	int16_t x2;

	// Initial off-screen clipping
	if ((length <= 0) || (y < 0) || (y >= m_height) || (x >= m_width) || ((x2 =
			(x + length - 1)) < 0))
		return;

	if (x < 0) { // Clip left
		length += x;
		x = 0;
	}

	if (x2 >= m_width) { // Clip right
		x2 = m_width - 1;
		length = x2 - x + 1;
	}

	LCD_SetAddrWindow(x, y, x2, y);
	LCD_Flood(color, length);
	LCD_SetAddrWindow(0, 0, m_width - 1, m_height - 1);

}

/**
 * \brief Draws a vertical line
 *
 * \param x		The x-coordinate of the first point
 * \param y		The y-coordinate of the first point
 * \param h		High of the line
 * \param color	Color
 * 
 * \return void
 */
void LCD_DrawFastVLine(int16_t x, int16_t y, int16_t h, uint16_t color) {
	// Update in subclasses if desired!
	LCD_DrawLine(x, y, x, y + h - 1, color);
}

/**
 * \brief Draws a Triangle specified by a coordinate pair, a width, and a height.
 *
 * \param x0			The x-coordinate of first corner of the triangle to draw
 * \param y0			The y-coordinate of first corner of the triangle to draw
 * \param x1			The x-coordinate of second corner of the triangle to draw
 * \param y1			The y-coordinate of second corner of the triangle to draw
 * \param x2			The x-coordinate of third corner of the triangle to draw
 * \param y2			The y-coordinate of third corner of the triangle to draw
 * \param color		Color
 *
 * \return void
 */
void LCD_DrawTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {
	LCD_DrawLine(x0, y0, x1, y1, color);
	LCD_DrawLine(x1, y1, x2, y2, color);
	LCD_DrawLine(x2, y2, x0, y0, color);
}

void LCD_FillTriangle(int16_t x0, int16_t y0, int16_t x1, int16_t y1,
		int16_t x2, int16_t y2, uint16_t color) {

	int16_t a, b, y, last;

	// Sort coordinates by Y order (y2 >= y1 >= y0)
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}
	if (y1 > y2) {
		swap(y2, y1);
		swap(x2, x1);
	}
	if (y0 > y1) {
		swap(y0, y1);
		swap(x0, x1);
	}

	if (y0 == y2) { // Handle awkward all-on-same-line case as its own thing
		a = b = x0;
		if (x1 < a)
			a = x1;
		else if (x1 > b)
			b = x1;
		if (x2 < a)
			a = x2;
		else if (x2 > b)
			b = x2;
		LCD_DrawFastHLine(a, y0, b - a + 1, color);
		return;
	}

	int16_t dx01 = x1 - x0, dy01 = y1 - y0, dx02 = x2 - x0, dy02 = y2 - y0,
			dx12 = x2 - x1, dy12 = y2 - y1, sa = 0, sb = 0;

	// For upper part of triangle, find scanline crossings for segments
	// 0-1 and 0-2.  If y1=y2 (flat-bottomed triangle), the scanline y1
	// is included here (and second loop will be skipped, avoiding a /0
	// error there), otherwise scanline y1 is skipped here and handled
	// in the second loop...which also avoids a /0 error here if y0=y1
	// (flat-topped triangle).
	if (y1 == y2)
		last = y1;   // Include y1 scanline
	else
		last = y1 - 1; // Skip it

	for (y = y0; y <= last; y++) {
		a = x0 + sa / dy01;
		b = x0 + sb / dy02;
		sa += dx01;
		sb += dx02;

		if (a > b)
			swap(a, b);
		LCD_DrawFastHLine(a, y, b - a + 1, color);
	}

	// For lower part of triangle, find scanline crossings for segments
	// 0-2 and 1-2.  This loop is skipped if y1=y2.
	sa = dx12 * (y - y1);
	sb = dx02 * (y - y0);
	for (; y <= y2; y++) {
		a = x1 + sa / dy12;
		b = x0 + sb / dy02;
		sa += dx12;
		sb += dx02;

		if (a > b)
			swap(a, b);
		LCD_DrawFastHLine(a, y, b - a + 1, color);
	}
}
/**
 * \brief Draws a rectangle specified by a coordinate pair, a width, and a height.
 * 
 * \param x			The x-coordinate of the upper-left corner of the rectangle to draw
 * \param y			The y-coordinate of the upper-left corner of the rectangle to draw
 * \param w			Width of the rectangle to draw
 * \param h			Height of the rectangle to draw
 * \param color		Color
 * 
 * \return void
 */
void LCD_DrawRect(int16_t x, int16_t y, int16_t w, int16_t h, uint16_t color) {
	LCD_DrawFastHLine(x, y, w, color);
	LCD_DrawFastHLine(x, y + h - 1, w, color);
	LCD_DrawFastVLine(x, y, h, color);
	LCD_DrawFastVLine(x + w - 1, y, h, color);
}

/**
 * \brief Draws a rectangle with rounded corners specified by a coordinate pair, a width, and a height.
 * 
 * \param x			The x-coordinate of the upper-left corner of the rectangle to draw
 * \param y			The y-coordinate of the upper-left corner of the rectangle to draw
 * \param w			Width of the rectangle to draw
 * \param h			Height of the rectangle to draw
 * \param r			Radius
 * \param color		Color
 * 
 * \return void
 */
void LCD_DrawRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color) {
	// smarter version
	LCD_DrawFastHLine(x + r, y, w - 2 * r, color); // Top
	LCD_DrawFastHLine(x + r, y + h - 1, w - 2 * r, color); // Bottom
	LCD_DrawFastVLine(x, y + r, h - 2 * r, color); // Left
	LCD_DrawFastVLine(x + w - 1, y + r, h - 2 * r, color); // Right
	// draw four corners
	LCD_DrawCircleHelper(x + r, y + r, r, 1, color);
	LCD_DrawCircleHelper(x + w - r - 1, y + r, r, 2, color);
	LCD_DrawCircleHelper(x + w - r - 1, y + h - r - 1, r, 4, color);
	LCD_DrawCircleHelper(x + r, y + h - r - 1, r, 8, color);
}

/**
 * \brief Helper function drawing rounded corners
 * 
 * \param x0			The x-coordinate
 * \param y0			The y-coordinate
 * \param r				Radius
 * \param cornername	Corner (1, 2, 3, 4)
 * \param color			Color
 * 
 * \return void
 */
void LCD_DrawCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
		uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;
		if (cornername & 0x4) {
			LCD_DrawPixel(x0 + x, y0 + y, color);
			LCD_DrawPixel(x0 + y, y0 + x, color);
		}
		if (cornername & 0x2) {
			LCD_DrawPixel(x0 + x, y0 - y, color);
			LCD_DrawPixel(x0 + y, y0 - x, color);
		}
		if (cornername & 0x8) {
			LCD_DrawPixel(x0 - y, y0 + x, color);
			LCD_DrawPixel(x0 - x, y0 + y, color);
		}
		if (cornername & 0x1) {
			LCD_DrawPixel(x0 - y, y0 - x, color);
			LCD_DrawPixel(x0 - x, y0 - y, color);
		}
	}
}

/**
 * \brief Draws an circle defined by a pair of coordinates and radius
 * 
 * \param x0		The x-coordinate
 * \param y0		The y-coordinate
 * \param r			Radius
 * \param color		Color
 * 
 * \return void
 */
void LCD_DrawCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	LCD_DrawPixel(x0, y0 + r, color);
	LCD_DrawPixel(x0, y0 - r, color);
	LCD_DrawPixel(x0 + r, y0, color);
	LCD_DrawPixel(x0 - r, y0, color);

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		LCD_DrawPixel(x0 + x, y0 + y, color);
		LCD_DrawPixel(x0 - x, y0 + y, color);
		LCD_DrawPixel(x0 + x, y0 - y, color);
		LCD_DrawPixel(x0 - x, y0 - y, color);
		LCD_DrawPixel(x0 + y, y0 + x, color);
		LCD_DrawPixel(x0 - y, y0 + x, color);
		LCD_DrawPixel(x0 + y, y0 - x, color);
		LCD_DrawPixel(x0 - y, y0 - x, color);
	}
}

/**
 * \brief Draws a character at the specified coordinates
 * 
 * \param x			The x-coordinate
 * \param y			The y-coordinate
 * \param c			Character
 * \param color		Character color
 * \param bg		Background color
 * \param size		Character Size
 * 
 * \return void
 */
void LCD_DrawChar(int16_t x, int16_t y, unsigned char c, uint16_t color,
		uint16_t bg, uint8_t size) {
	if ((x >= m_width) || // Clip right
			(y >= m_height) || // Clip bottom
			((x + 6 * size - 1) < 0) || // Clip left
			((y + 8 * size - 1) < 0))   // Clip top
		return;

	for (int8_t i = 0; i < 6; i++) {
		uint8_t line;
		if (i == 5) {
			line = 0x0;
		} else {
			line = font[c * 5 + i];   //pgm_read_byte(font+(c*5)+i);
			for (int8_t j = 0; j < 8; j++) {
				if (line & 0x1) {
					if (size == 1) { // default size
						LCD_DrawPixel(x + i, y + j, color);
					} else {  // big size
						LCD_FillRect(x + (i * size), y + (j * size), size, size,
								color);
					}
				} else if (bg != color) {
					if (size == 1) { // default size
						LCD_DrawPixel(x + i, y + j, bg);
					} else {  // big size
						LCD_FillRect(x + i * size, y + j * size, size, size,
								bg);
					}
				}
				line >>= 1;
			}
		}
	}
}

/**
 * \brief Draws a filled circle defined by a pair of coordinates and radius
 * 
 * \param x0		The x-coordinate
 * \param y0		The y-coordinate
 * \param r			Radius
 * \param color		Color
 * 
 * \return void
 */
void LCD_FillCircle(int16_t x0, int16_t y0, int16_t r, uint16_t color) {
	LCD_DrawFastVLine(x0, y0 - r, 2 * r + 1, color);
	LCD_FillCircleHelper(x0, y0, r, 3, 0, color);
}

/**
 * \brief Helper function to draw a filled circle
 * 
 * \param x0			The x-coordinate
 * \param y0			The y-coordinate
 * \param r				Radius
 * \param cornername	Corner (1, 2, 3, 4)
 * \param delta			Delta
 * \param color			Color
 * 
 * \return void
 */
void LCD_FillCircleHelper(int16_t x0, int16_t y0, int16_t r, uint8_t cornername,
		int16_t delta, uint16_t color) {
	int16_t f = 1 - r;
	int16_t ddF_x = 1;
	int16_t ddF_y = -2 * r;
	int16_t x = 0;
	int16_t y = r;

	while (x < y) {
		if (f >= 0) {
			y--;
			ddF_y += 2;
			f += ddF_y;
		}
		x++;
		ddF_x += 2;
		f += ddF_x;

		if (cornername & 0x1) {
			LCD_DrawFastVLine(x0 + x, y0 - y, 2 * y + 1 + delta, color);
			LCD_DrawFastVLine(x0 + y, y0 - x, 2 * x + 1 + delta, color);
		}
		if (cornername & 0x2) {
			LCD_DrawFastVLine(x0 - x, y0 - y, 2 * y + 1 + delta, color);
			LCD_DrawFastVLine(x0 - y, y0 - x, 2 * x + 1 + delta, color);
		}
	}
}

/**
 * \brief Draws a filled rectangle specified by a coordinate pair, a width, and a height.
 * 
 * \param x				The x-coordinate of the upper-left corner of the rectangle to draw
 * \param y				The y-coordinate of the upper-left corner of the rectangle to draw
 * \param w				Width of the rectangle to draw
 * \param h				Height of the rectangle to draw
 * \param fillcolor		Color
 * 
 * \return void
 */
void LCD_FillRect(int16_t x, int16_t y1, int16_t w, int16_t h,
		uint16_t fillcolor) {
	int16_t x2, y2;

	// Initial off-screen clipping
	if ((w <= 0) || (h <= 0) || (x >= m_width) || (y1 >= m_height)
			|| ((x2 = x + w - 1) < 0) || ((y2 = y1 + h - 1) < 0))
		return;
	if (x < 0) { // Clip left
		w += x;
		x = 0;
	}
	if (y1 < 0) { // Clip top
		h += y1;
		y1 = 0;
	}
	if (x2 >= m_width) { // Clip right
		x2 = m_width - 1;
		w = x2 - x + 1;
	}
	if (y2 >= m_height) { // Clip bottom
		y2 = m_height - 1;
		h = y2 - y1 + 1;
	}

	LCD_SetAddrWindow(x, y1, x2, y2);
	LCD_Flood(fillcolor, (uint32_t) w * (uint32_t) h);
	LCD_SetAddrWindow(0, 0, m_width - 1, m_height - 1);
}

/**
 * \brief Draws a filled rounded rectangle specified by a coordinate pair, a width, and a height.
 * 
 * \param x				The x-coordinate of the upper-left corner of the rectangle to draw
 * \param y				The y-coordinate of the upper-left corner of the rectangle to draw
 * \param w				Width of the rectangle to draw
 * \param h				Height of the rectangle to draw
 * \param r				Radius
 * \param fillcolor		Color
 * 
 * \return void
 */
void LCD_FillRoundRect(int16_t x, int16_t y, int16_t w, int16_t h, int16_t r,
		uint16_t color) {
	// smarter version
	LCD_FillRect(x + r, y, w - 2 * r, h, color);

	// draw four corners
	LCD_FillCircleHelper(x + w - r - 1, y + r, r, 1, h - 2 * r - 1, color);
	LCD_FillCircleHelper(x + r, y + r, r, 2, h - 2 * r - 1, color);
}

/**
 * \brief Fills the screen with the specified color
 * 
 * \param color	Color
 * 
 * \return void
 */
void LCD_FillScreen(uint16_t color) {
	// For the 932X, a full-screen address window is already the default
	// state, just need to set the address pointer to the top-left corner.
	// Although we could fill in any direction, the code uses the current
	// screen rotation because some users find it disconcerting when a
	// fill does not occur top-to-bottom.
	uint16_t x, y;
	switch (m_rotation) {
	default:
		x = 0;
		y = 0;
		break;
	case 1:
		x = TFTWIDTH - 1;
		y = 0;
		break;
	case 2:
		x = TFTWIDTH - 1;
		y = TFTHEIGHT - 1;
		break;
	case 3:
		x = 0;
		y = TFTHEIGHT - 1;
		break;
	}
	LCD_CS_LOW();
	LCD_WriteRegister16(0x0020, x);
	LCD_WriteRegister16(0x0021, y);

	LCD_Flood(color, (long) TFTWIDTH * (long) TFTHEIGHT);
}

/**
 * \brief Flood
 * 
 * \param color	Color
 * \param len	Length
 * 
 * \return void
 */
void LCD_Flood(uint16_t color, uint32_t len) {
	uint16_t blocks;
	uint8_t i, hi = color >> 8, lo = color;

	LCD_CS_LOW();
	LCD_CD_LOW();
	LCD_Write8(0x00); // High byte of GRAM register...
	LCD_Write8(0x22); // Write data to GRAM

	// Write first pixel normally, decrement counter by 1
	LCD_CD_HIGH();
	LCD_Write8(hi);
	LCD_Write8(lo);
	len--;

	blocks = (uint16_t) (len / 64); // 64 pixels/block
	if (hi == lo) {
		// High and low bytes are identical.  Leave prior data
		// on the port(s) and just toggle the write strobe.
		while (blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				LCD_WR_STROBE();
				LCD_WR_STROBE();
				LCD_WR_STROBE();
				LCD_WR_STROBE(); // 2 bytes/pixel
				LCD_WR_STROBE();
				LCD_WR_STROBE();
				LCD_WR_STROBE();
				LCD_WR_STROBE(); // x 4 pixels
			} while (--i);
		}
		// Fill any remaining pixels (1 to 64)
		for (i = (uint8_t) len & 63; i--;) {
			LCD_WR_STROBE();
			LCD_WR_STROBE();
		}
	} else {
		while (blocks--) {
			i = 16; // 64 pixels/block / 4 pixels/pass
			do {
				LCD_Write8(hi);
				LCD_Write8(lo);
				LCD_Write8(hi);
				LCD_Write8(lo);
				LCD_Write8(hi);
				LCD_Write8(lo);
				LCD_Write8(hi);
				LCD_Write8(lo);
			} while (--i);
		}
		for (i = (uint8_t) len & 63; i--;) {
			LCD_Write8(hi);
			LCD_Write8(lo);
		}
	}
	LCD_CS_HIGH();
}


void LCD_pushColors(uint16_t *data, uint8_t len, bool first) {
	uint16_t color;
	uint8_t hi, lo;
	LCD_CS_LOW();

	if (first == true) {
	LCD_CD_LOW();
	LCD_Write8(0x00); // High byte of GRAM register...
	LCD_Write8(0x22); // Write data to GRAM
	}

	LCD_CD_HIGH();
	while (len--) {
		color = *data++;
		hi = color >> 8; // Don't simplify or merge these
		lo = color;      // lines, there's macro shenanigans
		LCD_Write8(hi);		//going on
		LCD_Write8(lo);
	}
	LCD_CS_HIGH();
}

void LCD_pushAColors(uint16_t *arr, uint16_t len, uint16_t row, uint16_t col){
	LCD_SetAddrWindow(row, col, row + len, col);
	LCD_pushColors(arr, len - 1, true);
}

void LCD_pushColors2(uint16_t *data, uint8_t len) {
	uint16_t color;
	uint16_t blocks;
	uint8_t i = 0;
	uint8_t hi = data[0] >> 8, lo = data[0];
	uint16_t idx = 0;
	LCD_CS_LOW();
	LCD_CD_LOW();
	LCD_Write8(0x00); // High byte of GRAM register...
	LCD_Write8(0x22); // Write data to GRAM

	LCD_CD_HIGH();
	LCD_Write8(hi);
	LCD_Write8(lo);
	len--;
	idx++;

	blocks = (uint16_t) (len / 64); // 64 pixels/block
	while (blocks--) {
		i = 16; // 64 pixels/block / 4 pixels/pass
		do {
			for (int x = 0; x < 4; x++) {
				LCD_Write8(data[idx] >> 8);
				LCD_Write8(data[idx]);
				idx++;
			}
		} while (--i);
	}
	for (i = (uint8_t) len & 63; i--;) {
		LCD_Write8(data[idx] >> 8);
		LCD_Write8(data[idx]);
		idx++;
	}
	LCD_CS_HIGH();
}

void LCD_pushArray(int16_t x, int16_t y, uint16_t *arr, uint16_t len) {
	if ((x < 0) || (y < 0) || (x >= TFTWIDTH) || (y >= TFTHEIGHT))
		return;

	gpio_write(GPIOB, 0, LOW);

	for (int i = 0; i < len; i++) {
		LCD_WriteRegister16(0x0020, x + i);
		LCD_WriteRegister16(0x0021, y);
		LCD_WriteRegister16(0x0022, arr[i]);
	}

	gpio_write(GPIOB, 0, HIGH);
}

/**
 * \brief Print the specified Text
 * 
 * \param fmt	Format text
 * \param 
 * 
 * \return void
 */
void LCD_Printf(const char *fmt, ...) {
	static char buf[256];
	char *p;
	va_list lst;

	va_start(lst, fmt);
	vsprintf(buf, fmt, lst);
	va_end(lst);

	p = buf;
	while (*p) {
		if (*p == '\n') {
			m_cursor_y += m_textsize * 8;
			m_cursor_x = 0;
		} else if (*p == '\r') {
			// skip em
		} else {
			LCD_DrawChar(m_cursor_x, m_cursor_y, *p, m_textcolor, m_textbgcolor,
					m_textsize);
			m_cursor_x += m_textsize * 6;
			if (m_wrap && (m_cursor_x > (m_width - m_textsize * 6))) {
				m_cursor_y += m_textsize * 8;
				m_cursor_x = 0;
			}
		}
		p++;
	}
}

/**
 * \brief Resets the Display
 * 
 * \param 
 * 
 * \return void
 */
void LCD_Reset(void) {
	LCD_CS_HIGH();
	LCD_WR_HIGH();
	LCD_RD_HIGH();

	LCD_RST_LOW();
	delay(100);
	LCD_RST_HIGH();

	// Data transfer sync
	LCD_CS_LOW();

	LCD_CD_LOW();
	LCD_Write8(0x00);
	for (uint8_t i = 0; i < 3; i++)
		LCD_WR_STROBE(); // Three extra 0x00s
	LCD_CS_HIGH();
}

/**
 * \brief Sets the cursor coordinates
 * 
 * \param x		The x-coordinate
 * \param y		The y-coordinate
 * 
 * \return void
 */
void LCD_SetCursor(unsigned int x, unsigned int y) {
	m_cursor_x = x;
	m_cursor_y = y;
}

/**
 * \brief Sets the text size
 * 
 * \param s	Size
 * 
 * \return void
 */
void LCD_SetTextSize(uint8_t s) {
	m_textsize = (s > 0) ? s : 1;
}

/**
 * \brief Sets the text color
 * 
 * \param c		Text color
 * \param b		Background color
 * 
 * \return void
 */
void LCD_SetTextColor(uint16_t c, uint16_t b) {
	m_textcolor = c;
	m_textbgcolor = b;
}

/**
 * \brief Set Text wrap
 * 
 * \param w 
 * 
 * \return void
 */
void LCD_SetTextWrap(uint8_t w) {
	m_wrap = w;
}

/**
 * \brief Set display rotation
 * 
 * \param x	rotation
 * 
 * \return void
 */
void LCD_SetRotation(uint8_t x) {
	m_rotation = (x & 3);
	switch (m_rotation) {
	case 0:
	case 2:
		m_width = TFTWIDTH;
		m_height = TFTHEIGHT;
		break;
	case 1:
	case 3:
		m_width = TFTHEIGHT;
		m_height = TFTWIDTH;
		break;
	}
}

/**
 * \brief get display rotation
 *
 * \param None
 *
 * \return uint8_t
 */
uint8_t LCD_getRotation(void) {
	return m_rotation;
}

/**
 * \brief Sets window address
 * 
 * \param x1
 * \param y1
 * \param x2
 * \param y2
 * 
 * \return void
 */
void LCD_SetAddrWindow(int x1, int y1, int x2, int y2) {

	LCD_CS_LOW();

	// Values passed are in current (possibly rotated) coordinate
	// system.  932X requires hardware-native coords regardless of
	// MADCTL, so rotate inputs as needed.  The address counter is
	// set to the top-left corner -- although fill operations can be
	// done in any direction, the current screen rotation is applied
	// because some users find it disconcerting when a fill does not
	// occur top-to-bottom.
	int x, y, t;
	switch (m_rotation) {
	default:
		x = x1;
		y = y1;
		break;
	case 1:
		t = y1;
		y1 = x1;
		x1 = TFTWIDTH - 1 - y2;
		y2 = x2;
		x2 = TFTWIDTH - 1 - t;
		x = x2;
		y = y1;
		break;
	case 2:
		t = x1;
		x1 = TFTWIDTH - 1 - x2;
		x2 = TFTWIDTH - 1 - t;
		t = y1;
		y1 = TFTHEIGHT - 1 - y2;
		y2 = TFTHEIGHT - 1 - t;
		x = x2;
		y = y2;
		break;
	case 3:
		t = x1;
		x1 = y1;
		y1 = TFTHEIGHT - 1 - x2;
		x2 = y2;
		y2 = TFTHEIGHT - 1 - t;
		x = x1;
		y = y2;
		break;
	}

	LCD_WriteRegister16(0x0050, x1); // Set address window
	LCD_WriteRegister16(0x0051, x2);
	LCD_WriteRegister16(0x0052, y1);
	LCD_WriteRegister16(0x0053, y2);
	LCD_WriteRegister16(0x0020, x); // Set address counter to top left
	LCD_WriteRegister16(0x0021, y);

	LCD_CS_HIGH();
}

/**
 * \brief Writes 8-Bit data
 * 
 * \param data	8-Bit Data
 * 
 * \return void
 */
void LCD_Write8(uint8_t data) {
	// ------ PORT -----     --- Data ----
	// GPIOA, GPIO_PIN_9  -> BIT 0 -> 0x01
	// GPIOC, GPIO_PIN_7  -> BIT 1 -> 0x02
	// GPIOA, GPIO_PIN_10 -> BIT 2 -> 0x04
	// GPIOB, GPIO_PIN_3  -> BIT 3 -> 0x08
	// GPIOB, GPIO_PIN_5  -> BIT 4 -> 0x10
	// GPIOB, GPIO_PIN_4  -> BIT 5 -> 0x20
	// GPIOB, GPIO_PIN_10 -> BIT 6 -> 0x40
	// GPIOA, GPIO_PIN_8  -> BIT 7 -> 0x80

	GPIOA->ODR = (GPIOA->ODR & 0xF8FF) | ((data & 0x01) << 9)
			| ((data & 0x04) << 8) | ((data & 0x80) << 1);
	GPIOB->ODR = (GPIOB->ODR & 0xFBC7) | (data & 0x08) | ((data & 0x10) << 1)
			| ((data & 0x20) >> 1) | ((data & 0x40) << 4);
	GPIOC->ODR = (GPIOC->ODR & 0xFF7F) | ((data & 0x02) << 6);

	LCD_WR_STROBE();
}

/**
 * \brief Writes 8-Bit register
 * 
 * \param data	8-Bit Data
 * 
 * \return void
 */
void LCD_WriteRegister8(uint8_t a, uint8_t d) {
	LCD_CD_LOW();
	LCD_Write8(a);
	LCD_CD_HIGH();
	LCD_Write8(d);
}

/**
 * \brief Writes 16-Bit register
 * 
 * \param a		Register
 * \param d		Data
 * 
 * \return void
 */
void LCD_WriteRegister16(uint16_t a, uint16_t d) {
	uint8_t hi, lo;
	hi = (a) >> 8;
	lo = (a);
	LCD_CD_LOW();
	LCD_Write8(hi);
	LCD_Write8(lo);
	hi = (d) >> 8;
	lo = (d);
	LCD_CD_HIGH();
	LCD_Write8(hi);
	LCD_Write8(lo);
}

size_t write(uint8_t c) {
	{

		if (c == '\n') {
			cursor_x = 0;
			cursor_y += (int16_t) textsize
					* (uint8_t) pgm_read_byte(&gfxFont->yAdvance);
		} else if (c != '\r') {
			uint8_t first = pgm_read_byte(&gfxFont->first);
			if ((c >= first)
					&& (c <= (uint8_t) pgm_read_byte(&gfxFont->last))) {
				GFXglyph *glyph = &(((GFXglyph*) pgm_read_pointer(
						&gfxFont->glyph))[c - first]);
				uint8_t w = pgm_read_byte(&glyph->width), h = pgm_read_byte(
						&glyph->height);
				if ((w > 0) && (h > 0)) { // Is there an associated bitmap?
					int16_t xo = (int8_t) pgm_read_byte(&glyph->xOffset); // sic
					if (wrap && ((cursor_x + textsize * (xo + w)) > TFTWIDTH)) {
						cursor_x = 0;
						cursor_y += (int16_t) textsize
								* (uint8_t) pgm_read_byte(&gfxFont->yAdvance);
					}
					LCD_DrawChar(cursor_x, cursor_y, c, textcolor, textbgcolor,
							textsize);
				}
//                cursor_x += (uint8_t)pgm_read_byte(&glyph->xAdvance) * (int16_t)textsize;
				cursor_x += 13;
			}
		}

	}
	return 1;
}

void setFont(const GFXfont *f) {
	if (f) {            // Font struct pointer passed in?
		if (!gfxFont) { // And no current font struct?
			// Switching from classic to new font behavior.
			// Move cursor pos down 6 pixels so it's on baseline.
			cursor_y += 6;
		}
	} else if (gfxFont) { // NULL passed.  Current font struct defined?
		// Switching from new to classic font behavior.
		// Move cursor pos up 6 pixels so it's at top-left of char.
//        cursor_y -= 6;
	}
	gfxFont = (GFXfont*) f;
}

void printnewtstr(int row, int col, uint16_t txtcolor, uint16_t textbgcol,
		const GFXfont *f, uint8_t txtsize, uint8_t *str) {
	setFont(f);
	textcolor = txtcolor;
	textbgcolor = textbgcol;
	textsize = (txtsize > 0) ? txtsize : 1;
//	setCursor(0, row);
//	LCD_SetCursor(0, row);
	cursor_x = row;
	cursor_y = col;
	while (*str)
		write(*str++);
}

void printstr(uint8_t *str) {
	while (*str)
		write(*str++);
}


