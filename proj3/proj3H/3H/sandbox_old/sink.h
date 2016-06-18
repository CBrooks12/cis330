#ifndef sink_H
#define sink_H
#include <iostream>
#include "image.h"
using namespace std;
class sink
{
public:
	sink();
	~sink();
	void SetInput(Image *img){ img1 = img; };
	void SetInput2(Image* img){ img2 = img; };
	Image* GetImage(){ return img1; };
	Image* GetImage2(){ return img2; };
	virtual const char *SinkName() = 0;
protected:
	Image *img1;
	Image *img2;

};
#endif
