#ifndef Filters_H
#define Filters_H
#include <iostream>
#include "image.h"
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
	virtual void Execute() = 0;
    virtual void Update();
    
    virtual const char *FilterName() = 0;
    const char *SourceName(){return FilterName();};
    const char *SinkName(){return FilterName();};
};

class Shrinker:public Filter
{
public:
	Shrinker(){};
	virtual void Execute(){
	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	HalveInSize(*GetImage(), *GetOutput());};
	virtual const char  *FilterName(){return "Shrinker";};
};

class LRConcat: public Filter
{
public:
	LRConcat(){};
	virtual void Execute(){ 
	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if(img1->getHeight() != img2->getHeight()) {
		char msg[1024];
		sprintf(msg, "%s: heights must match: %d, %d", SinkName(), img1->getHeight(), img2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	LeftRightConcatenate(*GetImage(), *GetImage2(), *GetOutput()); };
	virtual const char  *FilterName(){return "LRConcat";};
};

class TBConcat: public Filter
{
public:
	TBConcat(){};
	virtual void Execute(){ 
	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if(img1->getWidth() != img2->getWidth()) {
		char msg[1024];
		sprintf(msg, "%s: Widths must match: %d, %d", SinkName(), img1->getWidth(), img2->getWidth());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	TopBottomConcatenate(*GetImage(), *GetImage2(), *GetOutput()); };
		virtual const char  *FilterName(){return "TBConcat";};
};

class Blender: public Filter
{
public:
	Blender(){factor = 0.0;};
	void SetFactor(float f){factor = f;};
	virtual void Execute(){ 
	if(img1 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input1!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}

	if(img2 == NULL) {
		char msg[1024];
		sprintf(msg, "%s: no input2!", SinkName());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	if(img1->getWidth() != img2->getWidth()||img1->getHeight() != img2->getHeight()) {
		char msg[1024];
		sprintf(msg, "%s: image size must match: %d x %d, %d x %d", SinkName(), img1->getWidth(), img1->getHeight(), img2->getWidth(), img2->getHeight());
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	if(factor > 1.0) {
		char msg[1024];
		sprintf(msg, "%s: Invalid factor for Blender: %f", SinkName(), factor);
		DataFlowException e(SinkName(), msg);
		throw e;
	}
	
	Blend(*GetImage(), *GetImage2(), factor, *GetOutput()); };
	virtual const char  *FilterName(){return "Blender";};
private:
	float factor;
};

/* this should go in filters.h */

class Crop : public Filter
{
    public:
        Crop()  { Istart = Istop = Jstart = Jstop = -1; };
        virtual const char *FilterName() { return "Crop"; };
        virtual void    Execute();
        void    SetRegion(int Istart_, int Istop_, int Jstart_, int Jstop_)
        {
            Istart = Istart_;
            Istop  = Istop_;
            Jstart = Jstart_;
            Jstop  = Jstop_;
        }

    private:
    int Istart, Istop, Jstart, Jstop;
};

class Transpose : public Filter
{
	public:
    	virtual void Execute();
        virtual const char *FilterName() { return "Transpose"; }
};

class Color : public Source {
    protected:
        int width, height;
        aPixel * colPixel;
    
    public:
        Color(int w, int h, unsigned char r, unsigned char g, unsigned char b);
        ~Color();
        virtual void Execute();
        virtual const char *SourceName() { return "Color"; }
};

class Invert : public Filter {
	public:
    	virtual void Execute();
        virtual const char *FilterName() { return "Invert"; }
};

class Checkerboard: public Filter{
	public:
		virtual void Execute();
		virtual const char *FilterName(){return "Checkerboard";};

};


class CheckSum : public sink {
	public:
		void OutputCheckSum(const char *filename);
		const char *SinkName() { return "CheckSum"; }
};

#endif
