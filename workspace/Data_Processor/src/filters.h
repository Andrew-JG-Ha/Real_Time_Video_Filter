#ifndef FILTERS_H
#define FILTERS_H

#define SOBEL_BASE_ADDR 0x15000000

/* ---------------------------------------------------------------------------- *
 * 							Function Prototypes								*
 * ---------------------------------------------------------------------------- */
void applyKernelGrey(int* source, int* destination, int* filter);
void applyKernelRGB(int* source, int* destination, int* filter, int scalingFactor);

/* ---------------------------------------------------------------------------- *
 * 							External Variable									*
 * ---------------------------------------------------------------------------- */
extern int userDefinedFilter[9];
extern int userDefinedScaling;

static char *filter_settings[10] = {"TOP_LEFT", "TOP", "TOP_RIGHT", "LEFT", "CENTER", "RIGHT", "BOT_LEFT", "BOT", "BOT_RIGHT", "SCALING_FACTOR"};

#endif
