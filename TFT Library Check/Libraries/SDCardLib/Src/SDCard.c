/*
 * SDCard.c
 *
 *  Created on: 18-Jun-2022
 *      Author: hp
 */

#include "SDCard.h"

//some variables for FatFs
FATFS FatFs; 	//Fatfs handle
FIL fil; 		//File handle
FRESULT fres; //Result after operations

//Read 30 bytes from "test.txt" on the SD card
BYTE readBuf[100];
uint8_t b;

void sd_mount() {
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		print("Error in Mounting --- ");
		print("f_mount error (%i)\r\n", fres);
//		while (1)
//			;
	}
}

void sd_space() {
	//Let's get some statistics from the SD card
	DWORD free_clusters, free_sectors, total_sectors;

	FATFS *getFreeFs;

	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
		print("Error in fetching space data --- ");
		print("f_getfree error (%i)\r\n", fres);
//		while (1)
//			;
	}

	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;

	print(
			"SD card stats:\r\n%10lu KiB total drive space.\r\n%10lu KiB available.\r\n",
			total_sectors / 2, free_sectors / 2);
}

int sd_openFile(char *c) {
	BYTE fileName[30];
	strncpy((char*) fileName, c, 30);
	fres = f_open(&fil, c, FA_READ);
	if (fres != FR_OK) {
		print("Could not open '%s'", fileName);
		print("f_open error (%i)\r\n", fres);
		return 0;
	}
	return 1;
//	print("I was able to open '%s' for reading!\r\n", fileName);
}

int sd_openFileW(char *c) {
	BYTE fileName[50];
	strncpy((char*) fileName, c, 30);
	fres = f_open(&fil, c,
	FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres == FR_OK) {
		return 1;
	} else {
		print("Could not open '%s'.", fileName);
		print("f_open error (%i).\r\n", fres);
		return 0;
	}
}

uint8_t sd_closeFile() {
	fres = f_close(&fil);
	if (fres == FR_OK) {
		return 1;
	} else {
		print("Could not close the file.");
		print("f_close error (%i).\r\n", fres);
		return 0;
	}
}

uint8_t sd_fileOffset(int n) {
	fres = f_lseek(&fil, n);
	if (fres == FR_OK) {
		return 1;
	} else {
		print("Could not seek line in file.");
		print("f_lseek error (%i).\r\n", fres);
		return 0;
	}
}

char sd_read8bits(char *c, int offset) {
	BYTE fileName[30];
	strncpy((char*) fileName, c, 30);
	char data_buf[2];
	fres = f_lseek(&fil, offset);

	TCHAR *rres = f_gets(data_buf, 2, &fil);
	if (rres != 0) {
//		print("Read string from '%s' contents: %c\r\n", fileName, data_buf[0]);
//		print("Read string from '%s' contents: %c\r\n", fileName, data_buf[1]);
		return data_buf[0];
	} else {
		print("Error in read8 --- ");
		print("f_gets error (%i)\r\n", fres);
		return '\0';
	}
}

uint8_t sd_read8(char *c, int offset) {
	sd_openFile(c);
	uint8_t data_buf;
	data_buf = sd_read8bits(c, offset);
	sd_closeFile();
	return data_buf;
}

uint16_t sd_read16bits(char *c, int offset) {
	uint16_t result;
	((uint8_t*) &result)[0] = sd_read8bits(c, offset);
	((uint8_t*) &result)[1] = sd_read8bits(c, offset + 1);
	return result;
}

uint16_t sd_read16(char *c, int offset) {
	sd_openFile(c);
	uint16_t result;
	result = sd_read16bits(c, offset);
	sd_closeFile();
	return result;
}

uint32_t sd_read24bits(char *c, int offset) {
	uint32_t result = 0;
	((uint8_t*) &result)[0] = sd_read8bits(c, offset);
	((uint8_t*) &result)[1] = sd_read8bits(c, offset + 1);
	((uint8_t*) &result)[2] = sd_read8bits(c, offset + 2);
//	((uint8_t*) &result)[3] = 0x00;
	return result;
}

uint32_t sd_read24(char *c, int offset) {
	sd_openFile(c);
	uint32_t result;
	result = sd_read24bits(c, offset);
	sd_closeFile();
	return result;
}

uint32_t sd_read32bits(char *c, int offset) {
	uint32_t result;
	((uint8_t*) &result)[0] = sd_read8bits(c, offset);
	((uint8_t*) &result)[1] = sd_read8bits(c, offset + 1);
	((uint8_t*) &result)[2] = sd_read8bits(c, offset + 2);
	((uint8_t*) &result)[3] = sd_read8bits(c, offset + 3);
	return result;
}

uint32_t sd_read32(char *c, int offset) {
	sd_openFile(c);
	uint32_t result;
	result = sd_read32bits(c, offset);
	sd_closeFile();
	return result;
}

void sd_writeArray(char *c, uint16_t *data, int len) {

	sd_openFileW(c);

	BYTE fileName[30];
	strncpy((char*) fileName, c, 30);

	//Copy in a string
	uint16_t data_buf[len];
	print("%X\n", data[0]);
	for (int x = 0; x < len; x++) {
		data_buf[x] = data[x];
	}
//	strncpy(data_buf, data, len);
	print("%X\n", data_buf[2]);
	UINT bytesWrote;
	fres = f_write(&fil, data_buf, len, &bytesWrote);
	if (fres == FR_OK) {
		print("Wrote %i bytes to '%s'!\r\n", bytesWrote, fileName);
	} else {
		print("f_write error (%i)\r\n", fres);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void sd_readFile(char *c) {
	//Now let's try to open file "test.txt"
	sd_openFile(c);
	BYTE fileName[30];
	strncpy((char*) fileName, c, 30);
	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	TCHAR *rres = f_gets((TCHAR*) readBuf, sizeof(readBuf), &fil);
	if (rres != 0) {
		print("Read string from '%s' contents: %s\r\n", fileName, readBuf);
	} else {
		print("f_gets error (%i)\r\n", fres);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void sd_seekFile(char *c, DWORD ofs) {
	//Now let's try to open file "test.txt"
	BYTE fileName[50];
	strncpy((char*) fileName, c, 30);
	fres = f_open(&fil, c, FA_READ);
	if (fres != FR_OK) {
		print("f_open error (%i)\r\n", fres);
		while (1)
			;
	}
	print("I was able to seek '%s' for reading!\r\n", fileName);

	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	fres = f_lseek(&fil, ofs);
//	strncpy((char*) readBuf, "a, new, file, is, made,!", 30);
	TCHAR *rres = f_gets((TCHAR*) readBuf, sizeof(readBuf), &fil);
	if (rres != 0) {
		print("Read ofs from '%s' contents: %s\r\n", fileName, readBuf);
	} else {
		print("f_gets error (%i)\r\n", fres);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void sd_writeFile(char *c, char *data) {
	BYTE fileName[50];
	strncpy((char*) fileName, c, 30);
	//Now let's try and write a file "write.txt"
	fres = f_open(&fil, c,
	FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if (fres == FR_OK) {
		print("I was able to open '%s' for writing\r\n", fileName);
	} else {
		print("f_open error (%i)\r\n", fres);
	}

	//Copy in a string
	strncpy((char*) readBuf, data, 30);
	UINT bytesWrote;
	fres = f_write(&fil, readBuf, strlen(data), &bytesWrote);
	if (fres == FR_OK) {
		print("Wrote %i bytes to '%s'!\r\n", bytesWrote, fileName);
	} else {
		print("f_write error (%i)\r\n", fres);
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
}

void sd_deMount() {
	//We're done, so de-mount the drive
	f_mount(NULL, "", 0);
}
uint8_t b;
void sd_readOne(char *c) {

	//Now let's try to open file "test.txt"

	BYTE fileName[50];
	strncpy((char*) fileName, c, 30);
	fres = f_open(&fil, c, FA_READ);
	if (fres != FR_OK) {
		print("f_open error (%i)\r\n", fres);
		while (1)
			;
	}
	print("I was able to open '%s' for reading!\r\n", fileName);

	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	for (int i = 0; i < 10; i++) {
		TCHAR *rres = f_gets((uint8_t*) b, sizeof(b), &fil);
		if (rres != 0) {
			print("Read string from '%s' contents: %c\r\n", fileName, b);
		} else {
			print("f_gets error (%i)\r\n", fres);
		}
//		print("%d\n\r", b);
//		print("Here\n\r");
	}

	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);

}

void getBMPImageData(char *file) {
	uint16_t result16;
	uint32_t result32;
	int offset = 0;
//	char file[] = "miniwoof.bmp";
	sd_openFile(file);
	result16 = sd_read16bits(file, offset);
	print("Identifier: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Size: %x\n", result32);
	offset += 4;
	result16 = sd_read16bits(file, offset);
	print("reserverd: %x\n", result16);
	offset += 2;
	result16 = sd_read16bits(file, offset);
	print("reserved: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Offset: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Header Size: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Width_px: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Height_px: %x\n", result32);
	offset += 4;
	result16 = sd_read16bits(file, offset);
	print("No. of Color Planes: %x\n", result16);
	offset += 2;
	result16 = sd_read16bits(file, offset);
	print("Bits per pixel: %x\n", result16);
	offset += 2;
	result32 = sd_read32bits(file, offset);
	print("Compression: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Image size(bytes): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("X resolution(PPM): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Y resolution(PPM): %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("No. of colors: %x\n", result32);
	offset += 4;
	result32 = sd_read32bits(file, offset);
	print("Important colors: %x\n", result32);
	offset += 4;
//	sd_closeFile();
	f_close(&fil);
}

void displayPic24bit(char *c, uint16_t row, uint16_t col) {

	sd_openFile(c);

	uint32_t picWidth, picHeight;
	uint32_t k = 0;
	bool drawFlag = true;
	uint8_t r, b, g;
	uint16_t color_buf_val = 0;
	uint16_t row_pt = row, col_pt = col;
	bool ft = true;
	uint8_t rotation = LCD_getRotation();
	uint16_t coordR1 = 0, coordC1 = 0, coordR2 = 0, coordC2 = 0;

	uint32_t offsetPointer = sd_read8bits(c, 10);
	print("Offset: %d\n", offsetPointer);
	picWidth = sd_read32bits(c, 18);
	print("Width: %d\n", picWidth);
	picHeight = sd_read32bits(c, 22);
	print("Height: %d\n", picHeight);
	uint8_t color_buf[3 * picWidth];
	uint16_t pixel_buf[picWidth];

	if (picWidth + row > 240) {
		row = 0;
	}
	if (picHeight + col > 320) {
		col = 0;
	}

	if ((rotation & 0x01) == 0) {
		coordR1 = row;
		coordC1 = col;
		coordR2 = (row + picWidth - 1);
		coordC2 = (col + picHeight - 1);
	} else if ((rotation & 0x01) == 1) {
		coordR1 = col;
		coordC1 = row;
		coordR2 = (col + picHeight - 1);
		coordC2 = (row + picWidth - 1);
	}
	LCD_SetAddrWindow(coordR1, coordC1, coordR2, coordC2);

	for (uint32_t i = row + 0; i < row + picHeight; i++) {
		k = 0;
		ft = true;
		color_buf_val = 0;
		for (uint32_t j = col + 0; j < col + picWidth; j++) {
			if (ft == true) {

				f_lseek(&fil, offsetPointer);
				f_gets(color_buf, sizeof(color_buf), &fil);
				offsetPointer += (3 * picWidth);
				ft = false;
			}
			r = color_buf[color_buf_val++];
			b = color_buf[color_buf_val++];
			g = color_buf[color_buf_val++];
			pixel_buf[k] = LCD_Color565(g, b, r);
			k++;
		}
		if (drawFlag == true) {
			LCD_pushColors(pixel_buf, picWidth, drawFlag);
			drawFlag = false;
		} else {
			LCD_pushColors(pixel_buf, picWidth, drawFlag);
		}
	}
	sd_closeFile();
	LCD_SetAddrWindow(0, 0, 240, 320);
}

void displayPic32bit(char *c, uint16_t row, uint16_t col) {

	sd_openFile(c);

	uint32_t picWidth, picHeight;
	uint32_t k = 0;
	bool drawFlag = true;
	uint8_t r, b, g;
	uint16_t color_buf_val = 0;
	uint16_t row_pt = row, col_pt = col;
	bool ft = true;
	uint8_t rotation = LCD_getRotation();
	uint16_t coordR1 = 0, coordC1 = 0, coordR2 = 0, coordC2 = 0;

	uint32_t offsetPointer = sd_read8bits(c, 10);
	print("Offset: %d\n", offsetPointer);
	picWidth = sd_read32bits(c, 18);
	print("Width: %d\n", picWidth);
	picHeight = sd_read32bits(c, 22);
	print("Height: %d\n", picHeight);
	uint8_t color_buf[4 * picWidth];
	uint16_t pixel_buf[picWidth];

	if (picWidth + row > 240) {
		row = 0;
	}
	if (picHeight + col > 320) {
		col = 0;
	}

	if ((rotation & 0x01) == 0) {
		coordR1 = row;
		coordC1 = col;
		coordR2 = row + picWidth - 1;
		coordC2 = col + picHeight - 1;
	} else if ((rotation & 0x01) == 1) {
		coordR1 = col;
		coordC1 = row;
		coordR2 = col + picHeight - 1;
		coordC2 = row + picWidth - 1;
	}
	LCD_SetAddrWindow(coordR1, coordC1, coordR2, coordC2);

	for (uint32_t i = row + 0; i < row + picHeight; i++) {
		k = 0;
		ft = true;
		color_buf_val = 0;
		for (uint32_t j = col + 0; j < col + picWidth; j++) {
			if (ft == true) {
				f_lseek(&fil, offsetPointer);
				f_gets(color_buf, sizeof(color_buf), &fil);
				offsetPointer += (4 * picWidth);
				ft = false;
			}
			r = color_buf[color_buf_val++];
			b = color_buf[color_buf_val++];
			g = color_buf[color_buf_val++];
			color_buf_val++;
			pixel_buf[k] = LCD_Color565(g, b, r);
			k++;
		}
		if (drawFlag == true) {
			LCD_pushColors(pixel_buf, picWidth, drawFlag);
			drawFlag = false;
		} else {
			LCD_pushColors(pixel_buf, picWidth, drawFlag);
		}

	}
	sd_closeFile();
	LCD_SetAddrWindow(0, 0, 240, 320);
}

//void displayPicO(char *c, uint16_t row, uint16_t col) {
//	sd_openFile(c);
//	uint32_t picWidth, picHeight;
//	uint32_t offsetPointer = sd_read8(c, 10);
//	print("Offset: %d\n", offsetPointer);
//
//	uint8_t r, b, g;
//	uint16_t color_buf_val = 0;
//
//	uint16_t row_pt = row, col_pt = col;
//
//	bool first = true;
//	bool ft = true;
//	LCD_SetRotation(0);
//
//	picWidth = sd_read32(c, 18);
//	print("Width: %d\n", picWidth);
//	picHeight = sd_read32(c, 22);
//	print("Height: %d\n", picHeight);
//
//	if (picWidth + row > 240) {
//		row = 0;
//	}
//	if (picHeight + col > 320) {
//		col = 0;
//	}
//
//	uint8_t color_buf[3 * picWidth];
//
//	uint32_t k = 0;
//	for (uint32_t i = col; i < col + picHeight; i++) {
//		k = 0;
//		ft = true;
//		color_buf_val = 0;
//
//		gpio_write(GPIOB, 0, 0);
//		LCD_WriteRegister16(0x0020, row_pt);
//		LCD_WriteRegister16(0x0021, col_pt);
//
//		for (uint32_t j = row; j < row + picWidth; j++) {
//			if (ft == true) {
//				f_open(&fil, c, FA_READ);
//				f_lseek(&fil, offsetPointer);
//				f_gets(color_buf, sizeof(color_buf), &fil);
//				offsetPointer += (3 * picWidth);
//				ft = false;
//			}
//			r = color_buf[color_buf_val++];
//			b = color_buf[color_buf_val++];
//			g = color_buf[color_buf_val++];
////			color_buf_val++;
//			LCD_WriteRegister16(0x0022,
//					(((g & 0xF8) << 8) | ((b & 0xFC) << 3) | (r >> 3)));
////			k++;
//		}
//		col_pt++;
//		gpio_write(GPIOB, 0, 1);
//	}
//	sd_closeFile();
//}

