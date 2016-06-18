#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
#include "image.h"
#include "iostream"
void ReadImage(char *filename, Image &output){
	FILE *aFile = fopen(filename, "r");
	char x[2];
	fscanf(aFile, "%s\n%d %d\n%d\n", x, &output.width, &output.height, &output.maxVal);
	output.pixelData = (aPixel*) malloc(output.width * output.height * sizeof(aPixel));
	std::cout<< sizeof(aPixel);
	fread(output.pixelData, sizeof(aPixel), output.width*output.height, aFile);
	fclose(aFile);
}

void WriteImage(char *filename, Image &img){
	FILE *aFile = fopen(filename, "w");
    fprintf (aFile, "%s\n", "P6");
    fprintf (aFile, "%d %d\n", img.width, img.height);
    fprintf (aFile, "%d\n", img.maxVal);
    fwrite(img.pixelData, sizeof(aPixel), img.width * img.height, aFile);
    fclose(aFile);
}

void HalveInSize(Image &input, Image &output){
	aPixel *locPixel = (aPixel*) malloc(input.width * input.height * sizeof(aPixel));
	for(int i = 0;i< input.height/2 ;i++)
	{
		for(int j = 0;j<input.width/2	;j++)
		{
			locPixel[i*input.width/2 + j].red = input.pixelData[2*i*input.width + 2*j].red;
			locPixel[i*input.width/2 + j].green = input.pixelData[2*i*input.width + 2*j].green;
			locPixel[i*input.width/2 + j].blue = input.pixelData[2*i*input.width + 2*j].blue;
		}
		//i+=output.width;
	}
	output = Image(input.height/2,input.width/2,255,locPixel);
}

void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output){
	aPixel *locPixel = (aPixel*) malloc(leftInput.width *2 * leftInput.height * sizeof(aPixel));
	int locWidth = leftInput.width*2;
	int locHeight = leftInput.height;
	
	int amv = (locWidth * locHeight);
	for(int i = 0;i< locHeight;i++)
	{
		int j = 0;
		for(j = 0; j<leftInput.width; j++){
			locPixel[(i*locWidth)+j].red = leftInput.pixelData[i*leftInput.width+j].red;
			locPixel[(i*locWidth)+j].green = leftInput.pixelData[i*leftInput.width+j].green;
			locPixel[(i*locWidth)+j].blue = leftInput.pixelData[i*leftInput.width+j].blue;
		}
		for(int k = 0;k<rightinput.width; k++){
			locPixel[(i*locWidth)+leftInput.width+k].red = rightinput.pixelData[i*rightinput.width+k].red;
			locPixel[(i*locWidth)+leftInput.width+k].green = rightinput.pixelData[i*rightinput.width+k].green;
			locPixel[(i*locWidth)+leftInput.width+k].blue = rightinput.pixelData[i*rightinput.width+k].blue;
		}
	}
	output = Image(locHeight,locWidth,255,locPixel);
}
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
	aPixel *locPixel = (aPixel*) malloc(topInput.width * 2 * topInput.height * sizeof(aPixel));
	int locWidth = topInput.width;
	int locHeight = topInput.height*2;
	int amv = topInput.width*topInput.height;
	for(int i = 0; i<amv;i++)
	{
		locPixel[i].red = topInput.pixelData[i].red;
		locPixel[i].green = topInput.pixelData[i].green;
		locPixel[i].blue = topInput.pixelData[i].blue;
	}
	for(int i = 0; i<amv;i++)
	{
		locPixel[amv+i].red = bottomInput.pixelData[i].red;
		locPixel[amv+i].green = bottomInput.pixelData[i].green;
		locPixel[amv+i].blue = bottomInput.pixelData[i].blue;
	}
	output = Image(locHeight,locWidth,255,locPixel);
}
void Blend(Image &input1, Image &input2, float factor, Image &output){
	aPixel *locPixel = (aPixel*) malloc(input2.width * input2.height * sizeof(aPixel));
	int amv = input1.width * input1.height;
	for(int i = 0;i<amv;i++)
	{
		locPixel[i].red = ((input1.pixelData[i].red*factor)+(input2.pixelData[i].red*(1-factor)));
		locPixel[i].green = (input1.pixelData[i].green*factor+input2.pixelData[i].green*(1-factor));
		locPixel[i].blue = (input1.pixelData[i].blue*factor+input2.pixelData[i].blue*(1-factor));
	}
		output = Image(input2.height,input2.width,255,locPixel);
}
