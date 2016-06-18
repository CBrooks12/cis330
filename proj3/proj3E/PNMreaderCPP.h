#ifndef PNMreader_H
#define PNMreader_H
#include <iostream>
#include <fstream>
#include <string>
#include "image.h"
#include "source.h"
using namespace std;
void ReadImage(char *filename, Image &output);
class PNMreaderCPP : public Source
{

public:
	PNMreaderCPP();
	PNMreaderCPP(char* aFilename);
	~PNMreaderCPP();

	virtual void Execute();

private:
	char* filename;


};
#endif
