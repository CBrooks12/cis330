#include "image.h"
#include <iostream>

Image::Image(void)
{
	height = 0;
	width = 0;
	maxVal = 0;
	//pixelData = (aPixel*) malloc(width * height * sizeof(aPixel));
	pixelData = new aPixel[width*height];
}

Image::Image(int h, int w, int mV, aPixel *pD)
{
	height = h;
	width = w;
	maxVal = mV;
	pixelData = pD;
}

Image::~Image()
{
	//delete [] pixelData;
}

void Image::display()
{
	std::cout << height << " " << width << " " << maxVal;
}

/*Image::Image(const Image &aImage)
{
height = aImage.height;
width = aImage.width;
maxVal = aImage.maxVal;
pixelData = aImage.pixelData;

}*/

