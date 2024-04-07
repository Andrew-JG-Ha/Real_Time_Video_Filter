#include "filters.h"

void applyKernelGrey(int* source, int* destination, int* filter) {
	int centreAddress, topLeftAddress, topAddress, topRightAddress, rightAddress, botRightAddress, botAddress, botLeftAddress, leftAddress;
	int centreVal, topLeftVal, topVal, topRightVal, rightVal, botRightVal, botVal, botLeftVal, leftVal, result;
	for (int row = 0; row < 480; row++) {
		for (int column = 0; column < 640; column++) {
			centreAddress = row * 640 + column;
			topLeftAddress = (row - 1) * 640 + (column - 1);
			topAddress = (row - 1) * 640 + column;
			topRightAddress = (row - 1) * 640 + (column + 1);
			rightAddress = row * 640 + (column + 1);
			botRightAddress = (row + 1) * 640 + (column + 1);
			botAddress = (row + 1) * 640 + column;
			botLeftAddress = (row + 1) * 640 + (column - 1);
			leftAddress = row * 640 + (column - 1);

			topLeftVal = 0;
			topVal = 0;
			topRightVal = 0;
			rightVal = 0;
			botRightVal = 0;
			botVal = 0;
			botLeftVal = 0;
			leftVal = 0;

			if (row % 479 == 0) {
				if (column % 639 == 0) {
					// at corners of image
					if (row == 0 && column == 0) {
						// top left corner
						rightVal = source[rightAddress];
						botRightVal = source[botRightAddress];
						botVal = source[botAddress];
					}
					else if (row == 0 && column == 639) {
						// top right corner
						leftVal = source[leftAddress];
						botLeftVal = source[botLeftAddress];
						botVal = source[botAddress];
					}
					else if (row == 479 && column == 639) {
						// bot right corner
						leftVal = source[leftAddress];
						topLeftVal = source[topLeftAddress];
						topVal = source[topAddress];
					}
					else {
						// bot left corner
						rightVal = source[rightAddress];
						topRightVal = source[topRightAddress];
						topVal = source[topAddress];
					}
				}
				else {
					// at horizontal edge of image
					if (row == 0) {
						// at top edge
						leftVal = source[leftAddress];
						botLeftVal = source[botLeftAddress];
						botVal = source[botAddress];
						botRightVal = source[botRightAddress];
						rightVal = source[rightAddress];
					}
					else {
						// at bottom edge
						leftVal = source[leftAddress];
						topLeftVal = source[topLeftAddress];
						topVal = source[topAddress];
						topRightVal = source[topRightAddress];
						rightVal = source[rightAddress];
					}
				}

			}
			else {
				if (column % 639 == 0) {
					// at vertical edge of image
					if (column == 0) {
						// at left most edge
						topVal = source[topAddress];
						topRightVal = source[topRightAddress];
						rightVal = source[rightAddress];
						botRightVal = source[botRightAddress];
						botVal = source[botAddress];
					}
					else {
						// at right most edge
						topVal = source[topAddress];
						topLeftVal = source[topLeftAddress];
						leftVal = source[leftAddress];
						botLeftVal = source[botLeftAddress];
						botVal = source[botAddress];
					}
				}
				else {
					// not at edge or corner of image
					topLeftVal = source[topLeftAddress];
					topVal = source[topAddress];
					topRightVal = source[topRightAddress];
					rightVal = source[rightAddress];
					botRightVal = source[botRightAddress];
					botVal = source[botAddress];
					botLeftVal = source[botLeftAddress];
					leftVal = source[leftAddress];
				}
			}

			centreVal = source[centreAddress] & 0x000000F0;
			topLeftVal = topLeftVal & 0x000000F0;
			topVal = topVal & 0x000000F0;
			topRightVal = topRightVal & 0x000000F0;
			rightVal = rightVal & 0x000000F0;
			botRightVal = botRightVal & 0x000000F0;
			botVal = botVal & 0x000000F0;
			botLeftVal = botLeftVal & 0x000000F0;
			leftVal = leftVal & 0x000000F0;

			result =  (filter[0] * topLeftVal) + (filter[1] * topVal) + (filter[2] * topRightVal)
					+ (filter[3] * leftVal) + (filter[4] * centreVal) + (filter[5] * rightVal)
					+ (filter[6] * botLeftVal) + (filter[7] * botVal) + (filter[8] * botRightVal);

			if (result > 0x000000F0 || -result > 0x000000F0) {
				result = 0x000000F0;
			}
			else {
				if (result < 0x00000000) {
					result = -result;
					result = result & 0x000000F0;
				}
				else {
					result = result & 0x000000F0;
				}
			}
			destination[centreAddress] = result | result << 8 | result << 16;
		}
	}
}


void applyKernelRGB(int* source, int* destination, int* filter, int scalingFactor) {
	int centreAddress, topLeftAddress, topAddress, topRightAddress, rightAddress, botRightAddress, botAddress, botLeftAddress, leftAddress;
	int topLeftVal, topVal, topRightVal, rightVal, botRightVal, botVal, botLeftVal, leftVal;
	int centreValR, topLeftValR, topValR, topRightValR, rightValR, botRightValR, botValR, botLeftValR, leftValR, resultR;
	int centreValG, topLeftValG, topValG, topRightValG, rightValG, botRightValG, botValG, botLeftValG, leftValG, resultG;
	int centreValB, topLeftValB, topValB, topRightValB, rightValB, botRightValB, botValB, botLeftValB, leftValB, resultB;
	for (int row = 0; row < 480; row++) {
		for (int column = 0; column < 640; column++) {
			centreAddress = row * 640 + column;
			topLeftAddress = (row - 1) * 640 + (column - 1);
			topAddress = (row - 1) * 640 + column;
			topRightAddress = (row - 1) * 640 + (column + 1);
			rightAddress = row * 640 + (column + 1);
			botRightAddress = (row + 1) * 640 + (column + 1);
			botAddress = (row + 1) * 640 + column;
			botLeftAddress = (row + 1) * 640 + (column - 1);
			leftAddress = row * 640 + (column - 1);

			topLeftVal = 0;
			topVal = 0;
			topRightVal = 0;
			rightVal = 0;
			botRightVal = 0;
			botVal = 0;
			botLeftVal = 0;
			leftVal = 0;

			if (row % 479 == 0) {
				if (column % 639 == 0) {
					// at corners of image
					if (row == 0 && column == 0) {
						// top left corner
						rightVal = source[rightAddress];
						botRightVal = source[botRightAddress];
						botVal = source[botAddress];
					}
					else if (row == 0 && column == 639) {
						// top right corner
						leftVal = source[leftAddress];
						botLeftVal = source[botLeftAddress];
						botVal = source[botAddress];
					}
					else if (row == 479 && column == 639) {
						// bot right corner
						leftVal = source[leftAddress];
						topLeftVal = source[topLeftAddress];
						topVal = source[topAddress];
					}
					else {
						// bot left corner
						rightVal = source[rightAddress];
						topRightVal = source[topRightAddress];
						topVal = source[topAddress];
					}
				}
				else {
					// at horizontal edge of image
					if (row == 0) {
						// at top edge
						leftVal = source[leftAddress];
						botLeftVal = source[botLeftAddress];
						botVal = source[botAddress];
						botRightVal = source[botRightAddress];
						rightVal = source[rightAddress];
					}
					else {
						// at bottom edge
						leftVal = destination[leftAddress];
						topLeftVal = destination[topLeftAddress];
						topVal = destination[topAddress];
						topRightVal = destination[topRightAddress];
						rightVal = destination[rightAddress];
					}
				}

			}
			else {
				if (column % 639 == 0) {
					// at vertical edge of image
					if (column == 0) {
						// at left most edge
						topVal = destination[topAddress];
						topRightVal = destination[topRightAddress];
						rightVal = destination[rightAddress];
						botRightVal = destination[botRightAddress];
						botVal = destination[botAddress];
					}
					else {
						// at right most edge
						topVal = destination[topAddress];
						topLeftVal = destination[topLeftAddress];
						leftVal = destination[leftAddress];
						botLeftVal = destination[botLeftAddress];
						botVal = destination[botAddress];
					}
				}
				else {
					// not at edge or corner of image
					topLeftVal = source[topLeftAddress];
					topVal = source[topAddress];
					topRightVal = source[topRightAddress];
					rightVal = source[rightAddress];
					botRightVal = source[botRightAddress];
					botVal = source[botAddress];
					botLeftVal = source[botLeftAddress];
					leftVal = source[leftAddress];
				}
			}

			centreValR = source[centreAddress] & 0x000000F0;
			topLeftValR = topLeftVal & 0x000000F0;
			topValR = topVal & 0x000000F0;
			topRightValR = topRightVal & 0x000000F0;
			rightValR = rightVal & 0x000000F0;
			botRightValR = botRightVal & 0x000000F0;
			botValR = botVal & 0x000000F0;
			botLeftValR = botLeftVal & 0x000000F0;
			leftValR = leftVal & 0x000000F0;

			resultR = (filter[0] * topLeftValR) + (filter[1] * topValR) + (filter[2] * topRightValR)
					+ (filter[3] * leftValR) + (filter[4] * centreValR) + (filter[5] * rightValR)
					+ (filter[6] * botLeftValR) + (filter[7] * botValR) + (filter[8] * botRightValR);
			resultR = (resultR >> scalingFactor) & 0x000000F0;

			centreValG = (source[centreAddress] & 0x0000F000) >> 8;
			topLeftValG = (topLeftVal & 0x0000F000) >> 8;
			topValG = (topVal & 0x0000F000) >> 8;
			topRightValG = (topRightVal & 0x0000F000) >> 8;
			rightValG = (rightVal & 0x0000F000) >> 8;
			botRightValG = (botRightVal & 0x0000F000) >> 8;
			botValG = (botVal & 0x0000F000) >> 8;
			botLeftValG = (botLeftVal & 0x0000F000) >> 8;
			leftValG = (leftVal & 0x0000F000) >> 8;

			resultG = (filter[0] * topLeftValG) + (filter[1] * topValG) + (filter[2] * topRightValG)
					+ (filter[3] * leftValG) + (filter[4] * centreValG) + (filter[5] * rightValG)
					+ (filter[6] * botLeftValG) + (filter[7] * botValG) + (filter[8] * botRightValG);
			resultG = (resultG >> scalingFactor) & 0x000000F0;

			centreValB = (source[centreAddress] & 0x00F00000) >> 16;
			topLeftValB = (topLeftVal & 0x00F00000) >> 16;
			topValB = (topVal & 0x00F00000) >> 16;
			topRightValB = (topRightVal & 0x00F00000) >> 16;
			rightValB = (rightVal & 0x00F00000) >> 16;
			botRightValB = (botRightVal & 0x00F00000) >> 16;
			botValB = (botVal & 0x00F00000) >> 16;
			botLeftValB = (botLeftVal & 0x00F00000) >> 16;
			leftValB = (leftVal & 0x00F00000) >> 16;

			resultB = (filter[0] * topLeftValB) + (filter[1] * topValB) + (filter[2] * topRightValB)
					+ (filter[3] * leftValB) + (filter[4] * centreValB) + (filter[5] * rightValB)
					+ (filter[6] * botLeftValB) + (filter[7] * botValB) + (filter[8] * botRightValB);
			resultB = (resultB >> scalingFactor) & 0x000000F0;

			destination[centreAddress] = resultR | resultG << 8 | resultB << 16;
		}
	}
}



