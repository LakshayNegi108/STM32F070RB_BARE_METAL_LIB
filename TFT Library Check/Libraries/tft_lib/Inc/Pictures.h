/*
 * Pictures.h
 *
 *  Created on: 24-Jun-2022
 *      Author: hp
 */

#ifndef INC_PICTURES_H_
#define INC_PICTURES_H_

//#include "st7783.h"

#define B	0x0000UL
#define W	0xFFFFUL

const uint16_t left_arrow[] = {
/*Pixel format: Red: 3 bit, Green: 3 bit, Blue: 2 bit*/
B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, W, W, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
		B, B, B, B, B, B, B, B, B, B, W, W, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, W, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, W, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
		B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, };


//const unsigned int temperature_icon_40x40[] = {
//B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, W, W, W, W, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, B, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, B, W, W,
//		B, B, B, B, B, B, B, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, B, W, W, W,
//		B, B, B, B, B, B, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, B, W, W, W, W,
//		B, B, B, B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, B, W, W, W, W, W,
//		B, B, B, B, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, B, B, W, W, W, W, W, W,
//		B, B, B, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, W, W, W,
//		B, B, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, W, W, W, W, W, W, W, W, W,
//		B, W, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, W,
//		W, W, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, W, W, W, W, W, W, W, W, W, B,
//		B, W, W, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, W, W, W, W, W, W, W, B, B,
//		B, B, W, W, W, W, W, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B, B,
//		B, B, B, B, B, B, B, B, W, W, W, W, W, B, B, B,
//
//};

uint8_t clock_50[] = { 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x00,
		0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
		0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x80, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x80, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x80, 0x80, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x80, 0x80,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0x80, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x00, 0xFF, 0xFF,
		0x00, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x80, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0x80, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x00, 0xFF, 0xFF,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0xFF, 0xFF, 0x00, 0x80, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80,
		0x00, 0x00, 0x80, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF, 0x00, 0x00, 0xFF,
		0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x00, 0x80, 0x00, 0x80, 0x80,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x80, 0x80, 0x80,
		0x00, 0x80, 0x80, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF, 0x00, 0xFF, 0xFF,
		0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0xC0, 0xC0, 0xC0, 0xFF, 0xFF, 0xFF,
		0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0x80, 0x80, 0x80,
		0x80, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x00, 0x80, 0x80,
		0x00, 0x80, 0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0, 0xC0,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF,
		0xFF, 0xFF, 0xFF };

#endif /* INC_PICTURES_H_ */