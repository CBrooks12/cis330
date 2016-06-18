#ifndef Filters_H
#define Filters_H
#include <iostream>
#include "image.h"
//#include "functions.h"
#include "source.h"
#include "sink.h"
using namespace std;
void HalveInSize(Image &input, Image &output);
void LeftRightConcatenate(Image &leftInput, Image &rightinput, Image &output);
void TopBottomConcatenate(Image &topInput, Image &bottomInput, Image &output);
void Blend(Image &input1, Image &input2, float factor, Image &output);

class Filter : public Source, public sink
{

public:
	Filter(){};
	//void SetInput(Image &aImg){fImg = aImg;};
	virtual void Execute() = 0;

};

class Shrinker:public Filter
{
public:
	Shrinker(){};
	virtual void Execute(){HalveInSize(*GetImage(), *GetOutput());};
};

class LRConcat: public Filter
{
public:
	LRConcat(){};
	virtual void Execute(){ LeftRightConcatenate(*GetImage(), *GetImage2(), *GetOutput()); };

};

class TBConcat: public Filter
{
public:
	TBConcat(){};
	virtual void Execute(){ TopBottomConcatenate(*GetImage(), *GetImage2(), *GetOutput()); };
};

class Blender: public Filter
{
public:
	Blender(){factor = 0.0;};
	void SetFactor(float f){factor = f;};
	virtual void Execute(){ Blend(*GetImage(), *GetImage2(), factor, *GetOutput()); };
private:
	float factor;
};
#endif
