#include <stdio.h>
#include <math.h>
#include <xparameters.h>
#include "xCCLabel.h"
#include "xaxidma.h"
#include "platform.h"
#include "AxiTimerHelper.h"
#include "Image.h"

unsigned int float_to_u32(float val) {
	unsigned int result;
	union float_bytes {
		float v;
		unsigned char bytes[4];
	} data;

	data.v = val;
	result = (data.bytes[3] << 24) + (data.bytes[2] << 16) + (data.bytes[1] << 8) + (data.bytes[0]);
	return result;
}

/********************************************** HARDWARE ****************************************************************/
XCclabel cCLabel;
XCclabel_Config *cCLabel_cfg;
XAxiDma axiDMA;
XAxiDma_Config *axiDMA_cfg;

//BRAM addresses
int *XHW = (int *)0x40000000;
int *YHW = (int *)0x40010000;

//DMA addresses
#define MEM_BASE_ADDR 0x01000000
#define TX_BUFFER_BASE (MEM_BASE_ADDR + 0x00100000)


void init_core() {
	int status = 0;

	// init CC core
	cCLabel_cfg = XCclabel_LookupConfig(XPAR_CCLABEL_0_DEVICE_ID);
	if (!cCLabel_cfg) {
		xil_printf("Error loading config\r\n");
	}
	else {
		status = XCclabel_CfgInitialize(&cCLabel,cCLabel_cfg);
		if (status != XST_SUCCESS) {
			xil_printf("Error initializing CC core\r\n");
		}
	}

	//init DMA
	axiDMA_cfg = XAxiDma_LookupConfig(XPAR_AXIDMA_0_DEVICE_ID);
	if(axiDMA_cfg) {
		status = XAxiDma_CfgInitialize(&axiDMA, axiDMA_cfg);
		if(status != XST_SUCCESS) {
			xil_printf("Error initializing DMA\r\n");
		}
	}

	//Disable Interrupts
	XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DEVICE_TO_DMA);
	XAxiDma_IntrDisable(&axiDMA, XAXIDMA_IRQ_ALL_MASK, XAXIDMA_DMA_TO_DEVICE);
}


/********************************************** SOFTWARE ****************************************************************/
#define THRESHOLD 70
#define MAX 999
#define MAX_STAR_DATA_SIZE 40
#define MAX_SET_SIZE 40
#define MAX_CENTROID_DATA 40

unsigned lbImage[IMG_HEIGHT * IMG_WIDTH];
unsigned set[MAX_SET_SIZE];

bool status[MAX_STAR_DATA_SIZE];
unsigned totalIntensity[MAX_STAR_DATA_SIZE];
unsigned x[MAX_STAR_DATA_SIZE];
unsigned y[MAX_STAR_DATA_SIZE];

unsigned int XSW[MAX_CENTROID_DATA];
unsigned int YSW[MAX_CENTROID_DATA];

void preProcess(unsigned Image[IMG_HEIGHT*IMG_WIDTH]) {
	unsigned i = 0,j = 0;
	for (i = 0; i < IMG_HEIGHT; ++i) {
		for (j = 0; j < IMG_WIDTH; ++j) {
			if (Image[i*IMG_HEIGHT + j] < THRESHOLD)
				lbImage[i*IMG_HEIGHT + j] = 0;
			else
				lbImage[i*IMG_HEIGHT + j] = 1;
		}
	}
}

unsigned find(unsigned id) {
	unsigned temp = id;
	while (temp != set[temp]) {
		temp = set[temp];
	}
	return temp;
}

unsigned firstPass(unsigned Image[IMG_HEIGHT*IMG_WIDTH]) {
	unsigned i = 0, j = 0;
	unsigned label = 0;
	unsigned prevAbove = 0;
	unsigned prevLeft = 0;
	unsigned setCount = 1;
	unsigned min = 0;
	unsigned max = MAX;
	for (i = 0; i < IMG_HEIGHT; ++i) {
		for (j = 0; j < IMG_WIDTH; ++j) {
			if (lbImage[i*IMG_HEIGHT + j] != 0) {
				if(i != 0 && lbImage[(i - 1)*IMG_HEIGHT + j] != 0) {
					prevAbove = lbImage[(i - 1)*IMG_HEIGHT + j];
				}
				else {
					prevAbove = MAX;
				}
				if(j != 0 && lbImage[i*IMG_HEIGHT + j - 1] != 0) {
					prevLeft = lbImage[i*IMG_HEIGHT + j - 1];
				}
				else {
					prevLeft = MAX;
				}

				if (prevAbove == MAX && prevLeft == MAX) {
					lbImage[i*IMG_HEIGHT + j] = ++label;
					set[setCount] = label;

					//
					status[setCount] = true;
					totalIntensity[setCount] = Image[i*IMG_HEIGHT + j];
					x[setCount] = i * Image[i*IMG_HEIGHT + j];
					y[setCount] = j * Image[i*IMG_HEIGHT + j];

					++setCount;
				}
				else {
					//Joint Set
					if(prevAbove < prevLeft) {
						min = prevAbove;
					}
					else {
						min = prevLeft;
					}
					if(prevAbove > prevLeft) {
						max = prevAbove;
					}
					else {
						max = prevLeft;
					}

					if (max != MAX) {
						set[max] = find(min);
					}
					else {
						set[min] = find(min);
					}
					lbImage[i*IMG_HEIGHT + j] = min;

					//Update data
					totalIntensity[min] += Image[i*IMG_HEIGHT + j];
					x[min] += i * Image[i*IMG_HEIGHT + j];
					y[min] += j * Image[i*IMG_HEIGHT + j];
				}
			}
		}
	}
	return setCount;
}

unsigned calCentroid(unsigned setCount, unsigned X[MAX_CENTROID_DATA], unsigned Y[MAX_CENTROID_DATA]) {
	unsigned i = 0;
	unsigned root = 0;
	unsigned centroidDataCount = 0;

	for (i = 1; i < setCount; ++i) {
		if (set[i] != i) {
			root = find(i);
			totalIntensity[root] += totalIntensity[i];
			x[root] += x[i];
			y[root] += y[i];
			status[i] = false;
		}
	}

	//cal
	for (i = 1; i < setCount; ++i) {
		if (status[i] == true) {
			X[centroidDataCount] = round((float)x[i] / totalIntensity[i]);
			Y[centroidDataCount] = round((float)y[i] / totalIntensity[i]);

			++centroidDataCount;
		}
	}
	return centroidDataCount;
}

void secondPass() {
	unsigned i = 0, j = 0;
	//unsigned root = 0;
	for (i = 0; i < IMG_HEIGHT; ++i) {
		for (j = 0; j < IMG_WIDTH; ++j) {
			if (lbImage[i*IMG_HEIGHT + j] != 0) {
				//root = find(lbImage[i*IMG_HEIGHT + j]);
				lbImage[i*IMG_HEIGHT + j] = find(lbImage[i*IMG_HEIGHT + j]);
			}
		}
	}
}

unsigned softwareCCLabel(unsigned swImage[IMG_HEIGHT * IMG_WIDTH], unsigned swX[MAX_CENTROID_DATA], unsigned swY[MAX_CENTROID_DATA]) {
	preProcess(swImage);
	unsigned setCount = firstPass(swImage);
	unsigned centroidDataCount = calCentroid(setCount, swX, swY);

	return centroidDataCount;
}


int main() {
	init_platform();
	//Initialize
	init_core();
	XCclabel_EnableAutoRestart(&cCLabel);

	//Timer
	AxiTimerHelper timer;

	//Load IMG
	//int *m_dma_buffer_TX = (int *) TX_BUFFER_BASE;

	/********************************************** SOFTWARE ****************************************************************/
	timer.startTimer();
	u32 centroidCountSW = softwareCCLabel(inputIMG, XSW, YSW);
	timer.stopTimer();
	double SWtime = timer.getElapsedTimerInSeconds();

	/********************************************** HARDWARE ****************************************************************/
	//Set parameters
	XCclabel_Set_imgHeight(&cCLabel, IMG_HEIGHT);
	XCclabel_Set_imgWidth(&cCLabel, IMG_WIDTH);

	//Flush the cache of the buffers
	Xil_DCacheFlushRange((u32)inputIMG, IMG_HEIGHT * IMG_WIDTH * sizeof(int));

	//Send data to IP core
	XAxiDma_SimpleTransfer(&axiDMA, (u32)inputIMG, IMG_HEIGHT * IMG_WIDTH * sizeof(int), XAXIDMA_DMA_TO_DEVICE);

	//Start IP core
	XCclabel_Start(&cCLabel);

	// Wait until it's done
	timer.startTimer();
	while(!XCclabel_IsDone(&cCLabel));

	timer.stopTimer();
	double HWtime = timer.getElapsedTimerInSeconds();

	//Output
	u32 centroidCountHW = XCclabel_Get_return(&cCLabel);

	//timer.stopTimer();
	//double HW_elapsed = timer.getElapsedTimerInSeconds();

	/********************************************** STATS ****************************************************************/
	xil_printf("---- SW-HW Comparison ----\r\n");

	xil_printf("SW Results: \r\n");
	xil_printf("	SW runtime: %d ns\r\n", (unsigned int)(SWtime * 1000000000));
	xil_printf("	Number of centroids: %d\r\n", centroidCountSW);
	for(unsigned i = 0; i < centroidCountSW; ++i)
		xil_printf("		Star[%d]: (%d, %d)\r\n", i+1, XSW[i], YSW[i]);

	xil_printf("HW Results: \r\n");
	xil_printf("	HW runtime: %d ns\r\n", (unsigned int)(HWtime * 1000000000));
	xil_printf("	Number of centroids: %d\r\n", centroidCountSW);
	for(unsigned i = 0; i < centroidCountHW; ++i)
		xil_printf("		Star[%d]: (%d, %d)\r\n", i+1, XHW[i], YHW[i]);

	xil_printf("Sucess !!!\r\n");
	cleanup_platform();
	return 0;
}