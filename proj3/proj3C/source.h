#ifndef Source_H
#define Source_H
#include <iostream>
#include "image.h"
using namespace std;
class Source
{

public:
	Source(){};
	Image* GetOutput(){
		return &sImg;
	};
	void setImg(Image aImg){ sImg = aImg; };
	virtual void Execute() = 0;

private:
	Image sImg;


};
#endif
