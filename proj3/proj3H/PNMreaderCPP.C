#include "PNMreaderCPP.h"


PNMreaderCPP::PNMreaderCPP()
{

}

PNMreaderCPP::PNMreaderCPP(char* aFilename)
{
	filename = aFilename;
};

void PNMreaderCPP::Execute(){
	ReadImage(filename, *GetOutput());
}

PNMreaderCPP::~PNMreaderCPP()
{
	
}


void ReadImage(char *filename, Image &output) {
    
    ifstream aFile;
	aFile.open(filename, ios::binary);

	char x[10];
	int aWidth, aHeight, aMaxVal;
	
	if(!aFile)
		cerr <<  "Unable to open file " << filename << endl;

	aFile >> x >> aWidth >> aHeight >> aMaxVal;
	
	output.setWidth(aWidth);
	output.setHeight(aHeight);
	output.setMaxVal(aMaxVal);
    //output.setPixelData(new aPixel[aWidth * aHeight]);
    aFile.ignore(256, '\n');
    aPixel *pixelData = new aPixel[aWidth * aHeight];
	unsigned char locPixel[3];
    for (int i = 0; i < aWidth * aHeight; i++) {
        aFile.read((char *)(locPixel),3);
        pixelData[i].red = locPixel[0];
        pixelData[i].green = locPixel[1];
        pixelData[i].blue = locPixel[2];
    }
    output.setPixelData(pixelData);

    aFile.close();
}

const char *PNMreader::SourceName() {
	return "PNMreader";
}
