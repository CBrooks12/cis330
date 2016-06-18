#include "filters.h"
#include <stddef.h>
#include <fstream>
#include <iostream>
using namespace std;
void Filter::Update() {
	char msg[128];
	if (img2 != NULL){
		sprintf(msg, "%s: about to update input2", FilterName());
		Logger::LogEvent(msg);
		img2->Update(); //lol wtf
		sprintf(msg, "%s: done updating input2", FilterName());
		Logger::LogEvent(msg);
	}
	if (img1 != NULL){
		sprintf(msg, "%s: about to update input1", FilterName());
		Logger::LogEvent(msg);
		img1->Update();
		sprintf(msg, "%s: done updating input1", FilterName());
		Logger::LogEvent(msg);
	}
	if (sImg.getMaxVal() == 0){
		sprintf(msg, "%s: about to execute", FilterName());
		Logger::LogEvent(msg);
		Execute();
		sprintf(msg, "%s: done executing", FilterName());
		Logger::LogEvent(msg);
	}
}

void HalveInSize(Image &input, Image &output){
	//aPixel *locPixel = (aPixel*) malloc(.5*input.getWidth() * input.getHeight() * sizeof(aPixel));
	int width = input.getWidth();
	int halfWidth = width/2;
	int height = input.getHeight();
	int halfHeight = height/2;
	aPixel *locPixel = new Pixel[halfWidth*halfHeight];
	for(int i = 0;i<halfHeight;i++)
	{
		for(int j = 0;j<halfWidth;j++)
		{
			int x = i*2*width+j*2;
			int y = i*halfWidth+j;
			locPixel[y].red = input.getPixelData()[x].red;
			locPixel[y].green = input.getPixelData()[x].green;
			locPixel[y].blue = input.getPixelData()[x].blue;
		}
	}
	output = Image(halfHeight,halfWidth,255,locPixel, output.getSource());
}

void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output){
	aPixel *locPixel = (aPixel*) malloc((leftInput.getWidth() + rightinput.getWidth()) * leftInput.getHeight() * sizeof(aPixel));
	int locGetWidth = leftInput.getWidth()+ rightinput.getWidth();
	int locGetHeight = leftInput.getHeight();

	int amv = (locGetWidth* locGetHeight);
	for (int i = 0; i< locGetHeight; i++)
	{
		for(int j = 0; j<leftInput.getWidth(); j++){
			locPixel[(i*locGetWidth) + j].red = leftInput.getPixelData()[i*leftInput.getWidth() + j].red;
			locPixel[(i*locGetWidth) + j].green = leftInput.getPixelData()[i*leftInput.getWidth() + j].green;
			locPixel[(i*locGetWidth) + j].blue = leftInput.getPixelData()[i*leftInput.getWidth() + j].blue;
		}
		for(int k = 0;k<rightinput.getWidth(); k++){
			int x = (i*locGetWidth) + leftInput.getWidth() + k;
			locPixel[x].red = rightinput.getPixelData()[i*rightinput.getWidth() + k].red;
			locPixel[x].green = rightinput.getPixelData()[i*rightinput.getWidth() + k].green;
			locPixel[x].blue = rightinput.getPixelData()[i*rightinput.getWidth() + k].blue;
		}
	}
	output = Image(locGetHeight, locGetWidth, 255, locPixel, output.getSource());
}
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
	aPixel *locPixel = (aPixel*) malloc(topInput.getWidth() * (topInput.getHeight() + bottomInput.getHeight())* sizeof(aPixel));
	int locGetWidth = topInput.getWidth();
	int locGetHeight = topInput.getHeight() + bottomInput.getHeight();
	int amv = topInput.getWidth()*topInput.getHeight();
	for(int i = 0; i<amv;i++)
	{
		locPixel[i].red = topInput.getPixelData()[i].red;
		locPixel[i].green = topInput.getPixelData()[i].green;
		locPixel[i].blue = topInput.getPixelData()[i].blue;
	}
	int amv2 = bottomInput.getWidth()*bottomInput.getHeight();
	for(int i = 0; i<amv2;i++)
	{
		locPixel[amv+i].red = bottomInput.getPixelData()[i].red;
		locPixel[amv+i].green = bottomInput.getPixelData()[i].green;
		locPixel[amv+i].blue = bottomInput.getPixelData()[i].blue;
	}
	output = Image(locGetHeight, locGetWidth, 255, locPixel, output.getSource());
}

void Blend(Image &input1, Image &input2, float factor, Image &output){
	aPixel *locPixel = (aPixel*) malloc(input2.getWidth() * input2.getHeight() * sizeof(aPixel));
	int amv = input1.getWidth() * input1.getHeight();
	for(int i = 0;i<amv;i++)
	{
		locPixel[i].red = (unsigned char)((input1.getPixelData()[i].red*factor)+(input2.getPixelData()[i].red*(1-factor)));
		locPixel[i].green = (unsigned char)((input1.getPixelData()[i].green*factor)+input2.getPixelData()[i].green*(1-factor));
		locPixel[i].blue = (unsigned char)((input1.getPixelData()[i].blue*factor)+input2.getPixelData()[i].blue*(1-factor));
	}
	output = Image(input2.getHeight(), input2.getWidth(), 255, locPixel, output.getSource());
}

void Crop::Execute(void)
{
    if (Istart < 0 || Istop < 0 || Jstart < 0 || Jstop < 0)
    {
        char msg[1024];
        sprintf(msg, "%s: uninitialized region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istart >= img1->getWidth() || Istop >= img1->getWidth())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image width", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Jstart >= img1->getHeight() || Jstop >= img1->getHeight())
    {
        char msg[1024];
        sprintf(msg, "%s: region outside image height", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }
    if (Istop < Istart || Jstop < Jstart)
    {
        char msg[1024];
        sprintf(msg, "%s: invalid region", FilterName());
        DataFlowException e(FilterName(), msg);
        throw e;
    }

    int height = Jstop-Jstart+1;
    int width  = Istop-Istart+1;
    int inputWidth = img1->getWidth();
    sImg.setSize(width, height);
    aPixel *buffer = sImg.getPixelData();
    aPixel *buffer1 = img1->getPixelData();
    for (int i = Istart ; i <= Istop ; i++)
        for (int j = Jstart ; j <= Jstop ; j++)
        {
            int idx1 = j*inputWidth+i;
            int idx  = (j-Jstart)*width+(i-Istart);
            buffer[idx].red = buffer1[idx1].red;
			buffer[idx].green = buffer1[idx1].green;
			buffer[idx].blue = buffer1[idx1].blue;
        }
}
void Transpose::Execute() {
	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width = img1->getWidth();
	int height = img1->getHeight();
	int newWidth = height;
	int newHeight = width;

	sImg.setSize(newWidth, newHeight);

    aPixel * temp = new Pixel[newWidth*newHeight];
	for(int i=0; i<newHeight; i++) {
		for(int j=0; j<newWidth; j++) {
			int in = j*width+i;
			int out = i*newWidth+j;
			temp[out].red = img1->getPixelData()[in].red;
			temp[out].green = img1->getPixelData()[in].green;
			temp[out].blue = img1->getPixelData()[in].blue;
		}
	}
    
	sImg.setPixelData(temp);
	//free(temp);
}


Color::Color(int w, int h, unsigned char r, unsigned char g, unsigned char b) {
    width = w;
    height = h;
    aPixel * pData = new Pixel;
    pData->red = r;
    pData->green = g;
    pData->blue = b;
    colPixel = pData;
    //colPixel->display();
	sImg.setSize(width, height);
}

Color::~Color() {}

void Color::Execute() {
	
    if (colPixel->red > 255 || colPixel->red < 0) {
        char msg[1024];
        sprintf(msg, "%s: red value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (colPixel->green > 255 || colPixel->green < 0) {
        char msg[1024];
        sprintf(msg, "%s: green value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }
    if (colPixel->blue > 255 || colPixel->blue < 0) {
        char msg[1024];
        sprintf(msg, "%s: blue value is out of bounds", SourceName());
        DataFlowException e(SourceName(), msg);
        throw e;
    }

	aPixel * temp = new Pixel[width*height];

    for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            int index = i*width + j;
            temp[index].red = colPixel->red;
            temp[index].green = colPixel->green;
            temp[index].blue = colPixel->blue;
        }
    } 
	
	sImg.setPixelData(temp);
	//free(temp);
}


void Invert::Execute() {

	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width = img1->getWidth();
	int height = img1->getHeight();
	sImg.setSize(width, height);
    
	aPixel * temp = new Pixel[width*height];
    
	for(int i=0; i<height; i++) {
		for(int j=0; j<width; j++) {
			int x = i*width+j;
			temp[x].red = 255 - img1->getPixelData()[x].red;
			temp[x].green = 255 - img1->getPixelData()[x].green;
			temp[x].blue = 255 - img1->getPixelData()[x].blue;
		}
	}
    
	sImg.setPixelData(temp);
	//free(temp);
}
void Checkerboard::Execute(){
	if (img1 == NULL){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: No input set for image1!", filtername);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (img2 == NULL){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: No input set for image2!", filtername);
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (img1->getHeight() != img2->getHeight()){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: Heights must match %d, %d", filtername, img1->getHeight(),img2->getHeight());
		DataFlowException e(filtername, msg);
		throw e;
	}
	if (img1->getWidth() != img2->getWidth()){
		char msg[1024];
		const char* filtername = FilterName();
		sprintf(msg, "%s: Widths must match %d, %d", filtername, img1->getWidth(),img2->getWidth());
		DataFlowException e(filtername, msg);
		throw e;
	}
	sImg.setSize(img1->getWidth(),img1->getHeight());
	for(int i=0; i<img1->getHeight();i++){
		for(int j=0; j<img1->getWidth();j++){
			int x = i*img1->getWidth()+j;
			if ((i/10+j/10)%2 ==0){
				sImg.setPixel(x,img1->getPixel(x));
			} else {
				sImg.setPixel(x,img2->getPixel(x));
			}
		}
	}
}


void CheckSum::OutputCheckSum(const char *filename) {
	// sums the total value in each rgb channel and outputs to file 

	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	int width = img1->getWidth();
	int height = img1->getHeight();
	int red = 0; 
	int green = 0; 
	int blue = 0;

	ofstream f;
	
	f.open(filename, ios::out);

	for(int i=0; i<height; i++) {
        for(int j=0; j<width; j++) {
            int index = i*width + j;
            red += img1->getPixelData()[index].red;
            green += img1->getPixelData()[index].green;
            blue += img1->getPixelData()[index].blue;
			red %= 256;
			green %= 256;
			blue %= 256;
        }
    } 
	f << "CHECKSUM: " << red << ", " << green << ", " << blue << endl;
	f.close();
}

