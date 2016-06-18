#include <stdio.h>
#include "PNMwriterCPP.h"
#define _ <<endl;
#define SP <<' '<<
#define X aFile<<
using namespace std;

PNMwriterCPP::PNMwriterCPP()
{

}

void PNMwriterCPP::Write(char* filename){
	WriteImage(filename, *GetImage());
}


void WriteImage(char *filename, Image &img){
	ofstream aFile (filename);
	X "P6"_
	X img.getWidth() SP img.getHeight()_
	X img.getMaxVal()_
	aFile.write((char *)(img.getPixelData()),img.getWidth() * img.getHeight() * 3);
    aFile.close();
}
