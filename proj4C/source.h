#ifndef Source_H
#define Source_H
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"
#include "logging.h"
#include <errno.h>
#include <sys/time.h>

using namespace std;
class Source
{
protected:
	Image sImg;
	struct timeval timeStart;
	struct timeval timeEnd;
public:
	Source(){sImg.setSource(this);};
	Image* GetOutput(){
		return &sImg;
	};
	void setImg(Image aImg){ sImg = aImg; };
	virtual void Execute() = 0;
	virtual void Update();
	virtual const char *SourceName() = 0;
	virtual double startTime(){gettimeofday(&timeStart, 0);
	return double(timeStart.tv_usec+timeStart.tv_sec)/ 100000;};
	virtual double endTime();
	virtual double timeDiff();


};
#endif
