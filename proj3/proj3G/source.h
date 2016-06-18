#ifndef Source_H
#define Source_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"
#include "logging.h"

using namespace std;
class Source
{
protected:
	Image sImg;
public:
	Source(){sImg.setSource(this);};
	Image* GetOutput(){
		return &sImg;
	};
	void setImg(Image aImg){ sImg = aImg; };
	virtual void Execute() = 0;
	virtual void Update();
	virtual const char *SourceName() = 0;


};
#endif
