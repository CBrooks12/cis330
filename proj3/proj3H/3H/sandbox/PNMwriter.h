#ifndef PNMwriter_H
#define PNMwriter_H
#include <iostream>
#include "image.h"
#include "sink.h"
using namespace std;
void WriteImage(char *filename, Image &img);
class PNMwriter : public sink
{

public:
	PNMwriter();
	void Write(char*);
    virtual const char *SinkName();

};


#endif
