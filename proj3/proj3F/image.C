#include "image.h"
#include <iostream>
#include "source.h"

Image::Image(void)
{
	height = 0;
	width = 0;
	maxVal = 0;

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

