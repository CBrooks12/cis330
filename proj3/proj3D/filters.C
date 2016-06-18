#include "functions.h"

void HalveInSize(Image &input, Image &output){
	aPixel *locPixel = (aPixel*) malloc(input.getWidth() * input.getHeight() * sizeof(aPixel));
	for(int i = 0;i< input.getHeight()/2 ;i++)
	{
		for(int j = 0;j<input.getWidth()/2	;j++)
		{
			locPixel[i*input.getWidth()/2 + j].red = input.getPixelData()[2*i*input.getWidth() + 2*j].red;
			locPixel[i*input.getWidth()/2 + j].green = input.getPixelData()[2*i*input.getWidth() + 2*j].green;
			locPixel[i*input.getWidth()/2 + j].blue = input.getPixelData()[2*i*input.getWidth() + 2*j].blue;
		}
		//i+=output.getWidth();
	}
	output = Image(input.getHeight()/2,input.getWidth()/2,255,locPixel);
}

void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output){
	aPixel *locPixel = (aPixel*) malloc(leftInput.getWidth() *2 * leftInput.getHeight() * sizeof(aPixel));
	int locGetWidth = leftInput.getWidth()*2;
	int locGetHeight = leftInput.getHeight();

	int amv = (locGetWidth* locGetHeight);
	for (int i = 0; i< locGetHeight; i++)
	{
		int j = 0;
		for(j = 0; j<leftInput.getWidth(); j++){
			locPixel[(i*locGetWidth) + j].red = leftInput.getPixelData()[i*leftInput.getWidth() + j].red;
			locPixel[(i*locGetWidth) + j].green = leftInput.getPixelData()[i*leftInput.getWidth() + j].green;
			locPixel[(i*locGetWidth) + j].blue = leftInput.getPixelData()[i*leftInput.getWidth() + j].blue;
		}
		for(int k = 0;k<rightinput.getWidth(); k++){
			locPixel[(i*locGetWidth) + leftInput.getWidth() + k].red = rightinput.getPixelData()[i*rightinput.getWidth() + k].red;
			locPixel[(i*locGetWidth) + leftInput.getWidth() + k].green = rightinput.getPixelData()[i*rightinput.getWidth() + k].green;
			locPixel[(i*locGetWidth) + leftInput.getWidth() + k].blue = rightinput.getPixelData()[i*rightinput.getWidth() + k].blue;
		}
	}
	output = Image(locGetHeight, locGetWidth, 255, locPixel);
}
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
	aPixel *locPixel = (aPixel*) malloc(topInput.getWidth() * 2 * topInput.getHeight() * sizeof(aPixel));
	int locGetWidth = topInput.getWidth();
	int locGetHeight = topInput.getHeight() * 2;
	int amv = topInput.getWidth()*topInput.getHeight();
	for(int i = 0; i<amv;i++)
	{
		locPixel[i].red = topInput.getPixelData()[i].red;
		locPixel[i].green = topInput.getPixelData()[i].green;
		locPixel[i].blue = topInput.getPixelData()[i].blue;
	}
	for(int i = 0; i<amv;i++)
	{
		locPixel[amv+i].red = bottomInput.getPixelData()[i].red;
		locPixel[amv+i].green = bottomInput.getPixelData()[i].green;
		locPixel[amv+i].blue = bottomInput.getPixelData()[i].blue;
	}
	output = Image(locGetHeight, locGetWidth, 255, locPixel);
}
void Blend(Image &input1, Image &input2, float factor, Image &output){
	aPixel *locPixel = (aPixel*) malloc(input2.getWidth() * input2.getHeight() * sizeof(aPixel));
	int amv = input1.getWidth() * input1.getHeight();
	for(int i = 0;i<amv;i++)
	{
		locPixel[i].red = ((input1.getPixelData()[i].red*factor)+(input2.getPixelData()[i].red*(1-factor)));
		locPixel[i].green = (input1.getPixelData()[i].green*factor+input2.getPixelData()[i].green*(1-factor));
		locPixel[i].blue = (input1.getPixelData()[i].blue*factor+input2.getPixelData()[i].blue*(1-factor));
	}
	output = Image(input2.getHeight(),input2.getWidth(),255,locPixel);
}

