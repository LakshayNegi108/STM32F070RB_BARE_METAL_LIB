/*
 * SDCard.h
 *
 *  Created on: 18-Jun-2022
 *      Author: hp
 */

#ifndef INC_SDCARD_H_
#define INC_SDCARD_H_

#include "fatfs.h"
#include "BML_DRIVER.h"

//some variables for FatFs
FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres; //Result after operations

//Read 30 bytes from "test.txt" on the SD card
BYTE readBuf[100];
uint8_t b;

void sd_mount();
void sd_space();

int sd_openFile(char *c);
void sd_closeFile();

void sd_fileOffset(int n);

void sd_readFile(char *c);
void sd_writeFile(char *c, char *data);

char sd_read8bits(char *c, int offset);
uint8_t sd_read8(char *c, int offset);

uint16_t sd_read16bits(char *c, int offset);
uint16_t sd_read16(char *c, int offset);

uint32_t sd_read24bits(char *c, int offset);
uint32_t sd_read24(char *c, int offset);

uint32_t sd_read32bits(char *c, int offset);
uint32_t sd_read32(char *c, int offset);

void sd_seekFile(char *c, DWORD ofs);
void sd_readOne(char *c);

void sd_deMount();

void getBMPImageData(char *file);
void displayPic(char *c, uint16_t x, uint16_t y);
void displayPic2(char *c, uint16_t row, uint16_t col);
//void displayPic();

#endif /* INC_SDCARD_H_ */
