#include <image.h>


Image::Image(void)
{
	height = 0;
	width = 0;
	maxVal = 0;
	pixelData = (aPixel*) malloc(width * height * sizeof(aPixel));
}

Image::Image(int h,int w,int mV, aPixel *pD)
{
	height = h;
	width = w;
	maxVal = mV;
	pixelData = pD;
}

Image::Image(const Image &aImage)
{
	height = aImage.height;
	width = aImage.width;
	maxVal = aImage.maxVal; 
	pixelData = aImage.pixelData;
	
}
