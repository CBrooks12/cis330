#include "PNMreader.h"
#include <iostream>

PNMreader::PNMreader()
{

}

PNMreader::PNMreader(char* aFilename)
{
	filename = aFilename;
};

void PNMreader::Execute(){
	ReadImage(filename, *GetOutput());
}
PNMreader::~PNMreader()
{

}

void ReadImage(char *filename, Image &output){
	FILE *aFile = fopen(filename, "r");
	char x[10];
	int aWidth, aHeight, aMaxVal;
	fscanf(aFile, "%s\n%d %d\n%d\n", x, &aWidth, &aHeight, &aMaxVal);
	output.setWidth(aWidth);
	output.setHeight(aHeight);
	output.setMaxVal(aMaxVal);
	output.setPixelData(new aPixel[aWidth * aHeight]);
	aPixel *locPixel = (aPixel*)malloc(aWidth * aHeight * sizeof(aPixel));
	fread(locPixel, sizeof(aPixel), aWidth*aHeight, aFile); 
	output.setPixelData(locPixel);
	fclose(aFile);
}

const char *PNMreader::SourceName() {
	return "PNMreader";
}
