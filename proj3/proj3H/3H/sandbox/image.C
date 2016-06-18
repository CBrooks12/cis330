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

Image::Image(int h, int w, int mV, aPixel *pD, Source *locSource)
{
	height = h;
	width = w;
	maxVal = mV;
	pixelData = pD;
	aSource = locSource;
}

Image::~Image()
{

}

/*void Image::display()
{
	std::cout << height << " " << width << " " << maxVal;
}*/

void aPixel::display()
{
	std::cout << &red << " " << &green << " " << &blue;
}

void Image::Update() {
	if (aSource){
		aSource->Update();
	}
}


void Image::setSource(Source *s) {
	if (s != NULL) {
		aSource = s;
	}
}

aPixel * Image::getPixel(int i) {
	aPixel * temp = new Pixel;
	temp->red = pixelData[i].red;
	temp->green = pixelData[i].green;
	temp->blue = pixelData[i].blue;
	return temp;
}

void Image::setPixel(int i, Pixel* aPix) {
	pixelData[i].red = aPix->red;
	pixelData[i].green = aPix->green;
	pixelData[i].blue = aPix->blue;
}
