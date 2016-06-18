#ifndef IMAGE_H
#define IMAGE_H
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

class Source;

typedef struct aPixel{
	unsigned char red, green, blue;
}Pixel;
class Image{

private:

	int height, width, maxVal;
	aPixel * pixelData;
	Source * aSource;

public:
	Image();
	Image(int h, int w, int mV, aPixel *pD);
	~Image();
	void display();
	aPixel * getPixelData(){ return pixelData; };
	void setPixelData(aPixel *aPixelData) { pixelData = aPixelData; };

	int getHeight(){ return height; };
	int getWidth(){ return width; };
	int getMaxVal(){ return maxVal; };

	void setHeight(int a){ height = a; };
	void setWidth(int a){ width = a; };
	void setMaxVal(int a){ maxVal = a; };
	
	void Update();
	void setSource(Source*);
	

};
#endif
