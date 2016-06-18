#ifndef IMAGE_H
#define IMAGE_H
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
typedef struct aPixel{
	unsigned char red, green, blue;
}aPixel;
typedef struct Image
{
	int height, width, maxVal;
	aPixel * pixelData;
	Image(void);
	Image(int h,int w,int mV, aPixel *pD);
	Image(const Image&);
}Image;

#endif
