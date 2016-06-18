#include "PNMwriter.h"
//#include "functions.h"

PNMwriter::PNMwriter()
{

}

void PNMwriter::Write(char* filename){
	WriteImage(filename, *GetImage());
}

void WriteImage(char *filename, Image &img){
	FILE *aFile = fopen(filename, "w");
	fprintf(aFile, "%s\n", "P6");
	fprintf(aFile, "%d %d\n", img.getWidth(), img.getHeight());
	fprintf(aFile, "%d\n", img.getMaxVal());
	fwrite(img.getPixelData(), sizeof(aPixel), img.getWidth() * img.getHeight(), aFile);
	fclose(aFile);
}
