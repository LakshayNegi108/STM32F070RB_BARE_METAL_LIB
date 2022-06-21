/*
 * SDCard.c
 *
 *  Created on: 18-Jun-2022
 *      Author: hp
 */

#include "SDCard.h"
void sd_mount() {
	//Open the file system
	fres = f_mount(&FatFs, "", 1); //1=mount now
	if (fres != FR_OK) {
		print("Error in Mounting --- ");
		print("f_mount error (%i)\r\n", fres);
		while (1)
			;
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
		while (1)
			;
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
		print("Could not open '%s'", fileName);
		print("f_open error (%i)\r\n", fres);
		return 0;
	}
}

void sd_closeFile() {
	f_close(&fil);
}

void sd_fileOffset(int n) {
	fres = f_lseek(&fil, n);
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
	((uint8_t*) &result)[1] = sd_read8bits(c, offset);
	((uint8_t*) &result)[0] = sd_read8bits(c, offset + 1);
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
	((uint8_t*) &result)[3] = sd_read8bits(c, offset);
	((uint8_t*) &result)[2] = sd_read8bits(c, offset + 1);
	((uint8_t*) &result)[1] = sd_read8bits(c, offset + 2);
	((uint8_t*) &result)[0] = sd_read8bits(c, offset + 3);
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
	for(int x = 0; x < len; x++)
	{
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

//void bmpDraw(char *filename, int x, int y) {
//
////  uint8_t     bmpFile;
//	int bmpWidth, bmpHeight;   // W+H in pixels
//	uint8_t bmpDepth;              // Bit depth (currently must be 24)
//	uint32_t bmpImageoffset;        // Start of image data in file
//	uint32_t rowSize;               // Not always = bmpWidth; may have padding
//	uint8_t sdbuffer[3 * BUFFPIXEL]; // pixel in buffer (R+G+B per pixel)
//	uint16_t lcdbuffer[BUFFPIXEL];  // pixel out buffer (16-bit per pixel)
//	uint8_t buffidx = sizeof(sdbuffer); // Current position in sdbuffer
//	bool goodBmp = false;       // Set to true on valid header parse
//	bool flip = true;        // BMP is stored bottom-to-top
//	int w, h, row, col;
//	uint8_t r, g, b;
//	uint32_t pos = 0;
//	uint8_t lcdidx = 0;
//	bool first = true;
//	int offset = 0;
//
//	if ((x >= 240) || (y >= 320))
//		return;
//
//	print("\n");
//	print("Loading image '");
//	print(filename);
//	print('\'');
//	// Open requested file on SD card
////	if ((sd_openFile(filename)) == 0) {
////		print("File not found");
////		return;
////	}
//	sd_openFile(filename);
//	// Parse BMP header
//	if (sd_read16bits(filename, offset) == 0x4D42) { // BMP signature
//		offset += 2;
//		print("File size: ");
//		print("%X\n", sd_read32bits(filename, offset));
//		offset += 4;
////    (void)read32(bmpFile); // Read & ignore creator bytes
//		offset += 4;
//		bmpImageoffset = sd_read32bits(filename, offset); // Start of image data
//		offset += 4;
//		print("Image Offset: ");
//		print("%X\n", bmpImageoffset);
//		// Read DIB header
//		print("Header size: ");
//		print("%X\n", sd_read32bits(filename, offset));
//		offset += 4;
//		bmpWidth = sd_read32bits(filename, offset);
//		offset += 4;
//		bmpHeight = sd_read32bits(filename, offset);
//		offset += 4;
//		if (sd_read16bits(filename, offset) == 1) { // # planes -- must be '1'
//			offset += 2;
//			bmpDepth = sd_read16bits(filename, offset); // bits per pixel
//			offset += 2;
//			print("Bit Depth: ");
//			print("%X\n", bmpDepth);
//			uint32_t compress = sd_read32bits(filename, offset);
////			if ((bmpDepth == 18) && (compress == 0)) { // 0 = uncompressed
//			offset += 4;
//			goodBmp = true; // Supported BMP format -- proceed!
//			print("Image size: ");
//			print("%X", bmpWidth);
//			print("x");
//			print("%X\n", bmpHeight);
//
//			// BMP rows are padded (if needed) to 4-byte boundary
//			rowSize = (bmpWidth * 3 + 3) & ~3;
//
//			// If bmpHeight is negative, image is in top-down order.
//			// This is not canon but has been observed in the wild.
//			if (bmpHeight < 0) {
//				bmpHeight = -bmpHeight;
//				flip = false;
//			}
//
//			// Crop area to be loaded
//			w = bmpWidth;
//			h = bmpHeight;
//			if ((x + w - 1) >= 240)
//				w = 240 - x;
//			if ((y + h - 1) >= 320)
//				h = 320 - y;
//
//			// Set TFT address window to clipped image bounds
//			LCD_SetAddrWindow(x, y, x + w - 1, y + h - 1);
//
//			for (row = 0; row < h; row++) { // For each scanline...
//				// Seek to start of scan line.  It might seem labor-
//				// intensive to be doing this on every line, but this
//				// method covers a lot of gritty details like cropping
//				// and scanline padding.  Also, the seek only takes
//				// place if the file position actually needs to change
//				// (avoids a lot of cluster math in SD library).
//				if (flip) // Bitmap is stored bottom-to-top order (normal BMP)
//					pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
//				else
//					// Bitmap is stored top-to-bottom
//					pos = bmpImageoffset + row * rowSize;
////					if (bmpFile.position() != pos) { // Need seek?
////						bmpFile.seek(pos);
////						buffidx = sizeof(sdbuffer); // Force buffer reload
////					}
//				sd_fileOffset(pos);
//
//				for (col = 0; col < w; col++) { // For each column...
//					// Time to read more pixel data?
////						if (buffidx >= sizeof(sdbuffer)) { // Indeed
////							// Push LCD buffer to the display first
////							if (lcdidx > 0) {
////								tft.pushColors(lcdbuffer, lcdidx, first);
////								lcdidx = 0;
////								first = false;
////							}
////							bmpFile.read(sdbuffer, sizeof(sdbuffer));
////							buffidx = 0; // Set index to beginning
////						}
//
//					// Convert pixel from BMP to TFT format
//					b = sdbuffer[buffidx++];
//					g = sdbuffer[buffidx++];
//					r = sdbuffer[buffidx++];
////					lcdbuffer[lcdidx++] = LCD_Color565(r, g, b);
//					LCD_DrawPixel(col, row, LCD_Color565(r, g, b));
//				} // end pixel
//			} // end scanline
//			  // Write any remaining data to LCD
////				if (lcdidx > 0) {
////					tft.pushColors(lcdbuffer, lcdidx, first);
////				}
//			print("Loaded in ");
////			} // end goodBmp
//		}
//	}
//	sd_closeFile();
//	if (!goodBmp)
//		print("BMP format not recognized.");
//}
