#include "image_data.h"

void storeImageInDDR() {
//	imageStorage = (u8*) 0x01FFFF86;
	imageStorage = (u8*) 0x05000000;
	rawDataStorage = (u8*) 0x02000000;

	u8 BMP_IMAGE_HEADER[] = {
		    // Bitmap File Header (14 bytes)
		    0x42, 0x4D,             // BM (bitmap identifier)
		    0x82, 0x00, 0x00, 0x00, // File size in bytes (70 bytes including headers and pixel data)
		    0x00, 0x00,             // Reserved (unused)
		    0x00, 0x00,             // Reserved (unused)
		    0x7A, 0x00, 0x00, 0x00, // Offset to start of pixel data (122 bytes including headers)

		    // DIB Header (40 bytes)
		    0x6C, 0x00, 0x00, 0x00, // DIB header size (40 bytes)
		    0x80, 0x02, 0x00, 0x00, // Image width (640 pixels)
		    0xE0, 0x01, 0x00, 0x00, // Image height (480 pixels)
		    0x01, 0x00,             // Number of color planes (must be 1)
		    0x10, 0x00,             // Bits per pixel (16 bits per pixel)
		    0x03, 0x00, 0x00, 0x00, // Compression method (BI_BITFIELDS)
		    0x7A, 0x60, 0x09, 0x00, // Size of raw image data
		    0xC4, 0x0E, 0x00, 0x00, // Horizontal resolution
		    0xC4, 0x0E, 0x00, 0x00, // Vertical resolution
		    0x00, 0x00, 0x00, 0x00, // Number of colors in the palette (not used)
		    0x00, 0x00, 0x00, 0x00, // Number of important colors (not used)

		    // Color Masks for RGBA4444 (16 bytes)
		    0x00, 0x0F, 0x00, 0x00, // Red mask (4 bytes)
		    0x00, 0xF0, 0x00, 0x00, // Green mask (4 bytes)
		    0x0F, 0x00, 0x00, 0x00, // Blue mask (4 bytes)
		    0xF0, 0x00, 0x00, 0x00, // Alpha mask (4 bytes)

//		    // Color Masks for RGBA4444 for raw data (16 bytes)
//		    0x0F, 0x00, 0x00, 0x00, // Red mask (4 bytes)
//		    0x00, 0xF0, 0x00, 0x00, // Green mask (4 bytes)
//		    0x00, 0x0F, 0x00, 0x00, // Blue mask (4 bytes)
//		    0xF0, 0x00, 0x00, 0x00, // Alpha mask (4 bytes)

			//52 bytes of 0x00 for some reason
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00,
	};

//	u8 BMP_IMAGE_DATA [] = {
//
//		    // Pixel Data (8 bytes)
//		    0xFF, 0xFF,             // Pixel (0, 0) - RGBA: (15, 15, 15, 15)
//		    0xF0, 0x0F,             // Pixel (1, 0) - RGBA: (0, 15, 15, 15)
//		    0xFF, 0x00,             // Pixel (0, 1) - RGBA: (15, 0, 15, 15)
//		    0xF0, 0xF0             // Pixel (1, 1) - RGBA: (0, 15, 0, 15)
//	};

	BMP_HEADER_SIZE = sizeof(BMP_IMAGE_HEADER);
	BMP_DATA_SIZE = 640*480*2;//sizeof(BMP_IMAGE_DATA);
	xil_printf("BMP_HEADER_SIZE holds %d.\r\n", BMP_HEADER_SIZE);
	for (int i=0; i < BMP_HEADER_SIZE; i++) {
		imageStorage[i] = BMP_IMAGE_HEADER[i];
	}

	u8 blue, red, green;
	u8 alpha = 0xF0;

	for (int j = 0; j < BMP_DATA_SIZE; j += 2) {
		blue = rawDataStorage[j*4 + 1] >> 4;
		green = rawDataStorage[j*4 + 2];
		red = rawDataStorage[j*4 + 2] >> 4;
		imageStorage[BMP_HEADER_SIZE + j] = alpha || blue;//0xF0;//BMP_IMAGE_DATA[j];
		imageStorage[BMP_HEADER_SIZE + j + 1] = green || red;//0x0F;//BMP_IMAGE_DATA[j];
	}

	xil_printf("Image stored to DDR.\r\n");

//	for (int j = 0; j < BMP_DATA_SIZE/4; j += 2) {
//		imageStorage[BMP_HEADER_SIZE + j] = 0xFA;//BMP_IMAGE_DATA[j];
//		imageStorage[BMP_HEADER_SIZE + j + 1] = 0x00;
//	}
//
//	for (int j = BMP_DATA_SIZE/4; j < BMP_DATA_SIZE/2; j += 2) {
//		imageStorage[BMP_HEADER_SIZE + j] = 0xF0;//BMP_IMAGE_DATA[j];
//		imageStorage[BMP_HEADER_SIZE + j + 1] = 0xA0;
//	}
//
//	for (int j = BMP_DATA_SIZE/2; j < 3*BMP_DATA_SIZE/4; j += 2) {
//			imageStorage[BMP_HEADER_SIZE + j] = 0xF0;//BMP_IMAGE_DATA[j];
//			imageStorage[BMP_HEADER_SIZE + j + 1] = 0x0A;
//		}
//
//	for (int j = 3*BMP_DATA_SIZE/4; j < BMP_DATA_SIZE; j += 2) {
//			imageStorage[BMP_HEADER_SIZE + j] = 0xF4;//BMP_IMAGE_DATA[j];
//			imageStorage[BMP_HEADER_SIZE + j + 1] = 0x44;
//		}
}

void write_BMP_to_SDCard() {
	xil_printf("write_BMP_to_SDCARD started running.\r\n");


	FRESULT Result;
	UINT NumBytesWritten;
//	UINT NumBytesRead;
//	u32 BuffCnt;
	BYTE work[FF_MAX_SS];
	u32 FileSize = BMP_HEADER_SIZE + BMP_DATA_SIZE;
	TCHAR *path = "0:/";

//	for (BuffCnt = 0; BuffCnt < FileSize; BuffCnt++) {
//		SourceAddress[BuffCnt] = TEST + BuffCnt;
//	}

	// Force mount the default drive on the SD Card and check if it is ready to work
	Result = f_mount(&Fatfs, path, 0);
	if (Result != FR_OK) {
		xil_printf("Error mounting SD Card.\r\n");
		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
		return;
	}

	Result = f_mkfs(path, FM_FAT32, 0, work, sizeof(work));
	if (Result != FR_OK) {
		xil_printf("Error initializing FAT32 System Parameters on SD Card.\r\n");
		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
		return;
	}

	SD_File = (char * ) FileName;

	//Create a file to write to
	Result = f_open(&File, SD_File , FA_WRITE | FA_CREATE_ALWAYS | FA_READ);
	if (Result != FR_OK) {
			xil_printf("Error creating file on SD Card.\r\n");
			xil_printf("Result holds %d for debugging purposes.\r\n", Result);
			return;
	}

	//Set the file read/write pointer to the beginning of file
	Result = f_lseek(&File, 0);
	if (Result != FR_OK) {
		xil_printf("Error setting file pointer for writing to beginning of file on SD Card.\r\n");
		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
		return;
	}

	//Write bmp data to file
	Result = f_write(&File, (const void*) imageStorage, FileSize, &NumBytesWritten);
	if (Result != FR_OK) {
			xil_printf("Error writing to file on SD Card.\r\n");
			xil_printf("Result holds %d for debugging purposes.\r\n", Result);
			f_close(&File);
			return;
	}

//	//Set the file read/write pointer to the beginning of file
//	Result = f_lseek(&File, 0);
//	if (Result != FR_OK) {
//		xil_printf("Error setting file pointer for reading to beginning of file on SD Card.\r\n");
//		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
//		return;
//	}
//
//	Result = f_read(&File, (void*)DestinationAddress, FileSize,
//			&NumBytesRead);
//	if (Result != FR_OK) {
//		xil_printf("Error reading file on SD Card.\r\n");
//		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
//		return;
//	}
//
//	/*
//	 * Data verification
//	 */
//	for(BuffCnt = 0; BuffCnt < FileSize; BuffCnt++){
//		if(imageStorage[BuffCnt] != DestinationAddress[BuffCnt]){
//			xil_printf("Data written does not match data read.\r\n");
//			return;
//		}
//	}

//	//Write bmp image data to file
//	result = f_write(&file, (const void*) bmp_image, size, &num_bytes_written);
//	if (result != FR_OK) {
//			xil_printf("Error writing to file on SD Card.\r\n");
//			xil_printf("Result holds %d for debugging purposes.\r\n", result);
//			f_close(&file);
//	}

	//Close the file
    Result = f_close(&File);
    if (Result != FR_OK) {
        xil_printf("Error closing file on SD Card.\r\n");
        xil_printf("Result holds %d for debugging purposes.\r\n", Result);
    }

//	xil_printf("BMP image writing completed.\r\n");

	// Force unmount the default drive on the SD Card and check if it is ready to work
	Result = f_mount(0, path, 0);
	if (Result != FR_OK) {
		xil_printf("Error unmounting SD Card.\r\n");
		xil_printf("Result holds %d for debugging purposes.\r\n", Result);
	}
}
