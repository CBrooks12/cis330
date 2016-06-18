#ifndef IMAGE_H
#define IMAGE_H
#include <cstddef>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>

class Source;

typedef struct aPixel{
	unsigned char red, green, blue;
	void display();
}Pixel;
class Image{

protected:

	int height, width, maxVal;
	aPixel * pixelData;
	Source * aSource;


public:
	Image();
	Image(int h, int w, int mV, aPixel *pD, Source *locSource);
	~Image();
	//void display();
	aPixel * getPixelData(){ return pixelData; };
	void setPixelData(aPixel *aPixelData) { pixelData = aPixelData; };

	int getHeight(){ return height; };
	int getWidth(){ return width; };
	int getMaxVal(){ return maxVal; };
	Source* getSource(){ return aSource; };
	void setHeight(int a){ height = a; };
	void setWidth(int a){ width = a; };
	void setMaxVal(int a){ maxVal = a; };
	void setSize(int a, int b){
		width = a; 
		height = b;
		maxVal = 255;
		delete [] pixelData;
		pixelData=new Pixel[height*width];
		
	};
	
	void Update();
	void setSource(Source*);
	void setPixel(int i, aPixel*);
	aPixel * getPixel(int i);
	

};
#endif
