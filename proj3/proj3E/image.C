#include "image.h"
#include <iostream>
#include "source.h"

Image::Image(void)
{
	height = 0;
	width = 0;
	maxVal = 0;

	//pixelData = new aPixel[width*height];
}

Image::Image(int h, int w, int mV, aPixel *pD)
{
	height = h;
	width = w;
	maxVal = mV;
	//delete [] pixelData;
	pixelData = new Pixel[width*height];
	memcpy(pixelData,pD,height*width*sizeof(Pixel));
}

Image::~Image()
{
	delete [] pixelData;
}

void Image::delMem()
{
	//delete [] pixelData;
	//delete [] aSource;
}

void Image::display()
{
	std::cout << height << " " << width << " " << maxVal;
}

void Image::Update() {
	aSource->Update();
}


void Image::setSource(Source *s) {
	if (s != NULL) {
		aSource = s;
	}
}

