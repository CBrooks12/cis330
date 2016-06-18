#include "filters.h"

void Filter::Update() {
	if(img1 != NULL){
		//fprintf(stderr,"in first area\n");
		img1->Update();
        //fprintf(stderr, "in filter::update, img1->Update filters.C\n");
    }
	if(img2 != NULL){
		//fprintf(stderr,"in second area\n");
		//img2->Update();
		//img2->display();
        //fprintf(stderr, "in filter::update, img2->Update filters.C\n");
    }
    //fprintf(stderr, "in filter::update, calling execute filters.C\n");
	Execute();	
}

void HalveInSize(Image &input, Image &output){
	//aPixel *locPixel = (aPixel*) malloc(input.getWidth() * input.getHeight() * sizeof(aPixel));
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
	output.setHeight(input.getHeight()/2);
	output.setWidth(input.getWidth()/2);
	output.setMaxVal(255);
	output.setPixelData(locPixel);
	//output = Image(input.getHeight()/2,input.getWidth()/2,255,locPixel);
	delete [] locPixel;
}

void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output){
	//aPixel *locPixel = (aPixel*) malloc(leftInput.getWidth() *2 * leftInput.getHeight() * sizeof(aPixel));
	aPixel *locPixel = new Pixel[(leftInput.getWidth()+rightinput.getWidth()) * leftInput.getHeight()];
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
	output.setHeight(locGetHeight);
	output.setWidth(locGetWidth);
	output.setMaxVal(255);
	output.setPixelData(locPixel);
	//output = Image(locGetHeight, locGetWidth, 255, locPixel);
	delete [] locPixel;
}
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output){
	//aPixel *locPixel = (aPixel*) malloc(topInput.getWidth() * 2 * topInput.getHeight() * sizeof(aPixel));
	aPixel* locPixel = new Pixel[topInput.getWidth() * (topInput.getHeight() + bottomInput.getHeight())];
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
	output.setHeight(locGetHeight);
	output.setWidth(locGetWidth);
	output.setMaxVal(255);
	output.setPixelData(locPixel);
	//output = Image(locGetHeight, locGetWidth, 255, locPixel);
	delete [] locPixel;
}
void Blend(Image &input1, Image &input2, float factor, Image &output){
	//aPixel *locPixel = (aPixel*) malloc(input2.getWidth() * input2.getHeight() * sizeof(aPixel));
	aPixel * locPixel = new Pixel[input2.getWidth() * input2.getHeight() * sizeof(aPixel)];
	int amv = input1.getWidth() * input1.getHeight();
	for(int i = 0;i<amv;i++)
	{
		locPixel[i].red = ((input1.getPixelData()[i].red*factor)+(input2.getPixelData()[i].red*(1-factor)));
		locPixel[i].green = (input1.getPixelData()[i].green*factor+input2.getPixelData()[i].green*(1-factor));
		locPixel[i].blue = (input1.getPixelData()[i].blue*factor+input2.getPixelData()[i].blue*(1-factor));
	}
	output.setHeight(input2.getHeight());
	output.setWidth(input2.getWidth());
	output.setMaxVal(255);
	output.setPixelData(locPixel);
	//output = Image(input2.getHeight(),input2.getWidth(),255,locPixel);
	delete [] locPixel;
}

