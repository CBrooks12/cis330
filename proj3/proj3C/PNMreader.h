#ifndef PNMreader_H
#define PNMreader_H
#include <iostream>
#include "image.h"
#include "source.h"
//#include "functions.h"
using namespace std;
void ReadImage(char *filename, Image &output);
class PNMreader : public Source
{

public:
	PNMreader();
	PNMreader(char* aFilename);
	~PNMreader();

	//virtual void Execute();
	void Execute();

private:
	char* filename;


};
#endif
