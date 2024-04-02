#include <stdio.h>
#include "xaxivdma.h"
#include "xparameters.h"
#include "xil_exception.h"
#include "xil_cache.h"
#include "xil_io.h"
#include "xscugic.h"
#include "xil_types.h"
#include "platform.h"
#include "xil_printf.h"
#include "camera.h"

// https://www.youtube.com/watch?v=IGdr4QRrOcs


#define packagedHSize 320

#define HSizeInput 640 / 2 * 4
#define HStrideLength 640 / 2 * 4
#define VSizeInput 480 * 4


int* writeBuffer1 = (int*) CAMERA_BASE_ADDR;
int* writeBuffer2 = (int*) CAMERA_BASE_ADDR + 4*320*480;
int* writeBuffer3 = (int*) CAMERA_BASE_ADDR + 2* 4*320*480;

int* vgaBuffer = (int*) 0x02000000;

int* grayBuffer = (int*) GRAYSCALE_BASE_ADDR;
int* rgbBuffer = (int*) RGB_BASE_ADDR;

int* tempBuffer[640*480];

int main() {
    int data;
	init_platform();

	printf("\n\nHello World! \r\n");

	XAxiVdma vdma;  // VDMA instance

	// Look up the VDMA configuration
	XAxiVdma_Config *vdma_config = XAxiVdma_LookupConfig(XPAR_AXI_VDMA_0_DEVICE_ID);
	if (!vdma_config) {
	    xil_printf("VDMA device not found\r\n");
	}

	// Initialize the VDMA instance
	int status = XAxiVdma_CfgInitialize(&vdma, vdma_config, vdma_config->BaseAddress);
	if (status != XST_SUCCESS) {
	    xil_printf("VDMA initialization failed\r\n");
	}

	// Configure DMA setup parameters
	XAxiVdma_DmaSetup dma_setup;
	dma_setup.VertSizeInput = VSizeInput;  // Vertical size of input frame
	dma_setup.HoriSizeInput = HSizeInput;  // Horizontal size of input frame
	dma_setup.Stride = HStrideLength;         // Stride (bytes per line)
	dma_setup.FrameDelay = 0;       // No frame delay
	dma_setup.EnableCircularBuf = 1; // Enable circular buffering
	dma_setup.FixedFrameStoreAddr = 0; // No fixed frame store address

	// Set up buffer addresses in DDR memory
	UINTPTR frame_buffer_addr[1];
	frame_buffer_addr[0] = &(writeBuffer1[0]);
	frame_buffer_addr[1] = &(writeBuffer2[0]);
	frame_buffer_addr[2] = &(writeBuffer3[0]);
	// Initialize frame_buffer_addr array with addresses of DDR memory buffers

	// Configure the VDMA for write operation
	status = XAxiVdma_DmaConfig(&vdma, XAXIVDMA_WRITE, &dma_setup);
	if (status != XST_SUCCESS) {
	    xil_printf("VDMA configuration failed\r\n");
	}

	// Set buffer addresses for writing
	status = XAxiVdma_DmaSetBufferAddr(&vdma, XAXIVDMA_WRITE, frame_buffer_addr);
	if (status != XST_SUCCESS) {
	    xil_printf("VDMA buffer address setup failed\r\n");
	}

	// Start the VDMA operation
	status = XAxiVdma_DmaStart(&vdma, XAXIVDMA_WRITE);
	if (status != XST_SUCCESS) {
	    xil_printf("VDMA start failed\r\n");
	}

	XAxiVdma_DmaStop(&vdma, XAXIVDMA_WRITE);

	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0x30, 0x83);
	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xAC, &(writeBuffer1[0]));
	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xB0, &(writeBuffer2[0]));
	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xB4, &(writeBuffer3[0]));

	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xA8, HStrideLength);
	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xA4, HSizeInput);
	Xil_Out32(XPAR_AXI_VDMA_0_BASEADDR + 0xA0, VSizeInput);

//    for (int i = 0; i < 500; i++) {
//    	data = writeBuffer1[i];
//    	printf("Data = 0x%08x, Memory Location = 0x%08x\n", data, (&writeBuffer1[i]));
//    }

//    for (int i = 0; i < 1000000; i++) {
//    	if (i % 10000 == 0) {
//        	data = writeBuffer[100];
//        	printf("Data = 0x%08x, Memory Location = 0x%08x\n", data, (&writeBuffer[100]));
//    	}
//    }

	printf("Starting Stall\n");
	for (int i = 0; i < 5000000; i++) {
		int index = 0;
		index = index + 1;
	}
	printf("Done Stall\n");

	Xil_DCacheFlush();
	printf("White Canvas\n");
	for (int i = 0; i < 640*480; i++) {
		vgaBuffer[i] = 0x00F0F0F0;
	}

    while(1) {
    	Xil_DCacheFlush();
//    	unpackCameraData(writeBuffer1, vgaBuffer, grayBuffer);

//    	unpackRGB(writeBuffer1, vgaBuffer);
    	unpackGray(writeBuffer1, vgaBuffer);

    	xil_printf("Data at mem location: 0x%08x is 0x%08x\r\n", &(writeBuffer1[400]), writeBuffer1[400]);
//    	memcpy(vgaBuffer, writeBuffer1, 640*480*4);
//    	printf("unpacked and printed!\n");
    }

    cleanup_platform();
    return 0;
}
