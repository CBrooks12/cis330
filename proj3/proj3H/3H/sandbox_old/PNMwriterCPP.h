#ifndef PNMwriter_H
#define PNMwriter_H
#include <iostream>
#include <fstream>
#include "image.h"
#include "sink.h"
using namespace std;
void WriteImage(char *filename, Image &img);
class PNMwriterCPP : public sink
{

public:
	PNMwriterCPP();
	void Write(char*);


};


#endif
