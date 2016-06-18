#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
/* data members go here */
	char magicNum[2];
	int width, height, maxVal;
	struct aPixel
	{
		unsigned char red, green, blue;
	}*pixelData;
} Image;

Image *
ReadImage(char *filename)
{
	FILE *aFile = fopen(filename, "r");
	Image *img = NULL;
	img = (Image *) malloc(sizeof(Image));
	fscanf(aFile, "%s\n%d %d\n%d\n", img->magicNum, &img->width, &img->height, &img->maxVal);

	img -> pixelData = (struct aPixel*) malloc(img->width * img->height * sizeof(struct aPixel));
	fread(img -> pixelData, sizeof(struct aPixel), img->width*img->height, aFile);
	fclose(aFile);
	return img;
}


void WriteImage(Image *img, char *filename)
{
    FILE *aFile = fopen(filename, "w");
    fprintf (aFile, "%s\n", img->magicNum);
    fprintf (aFile, "%d %d\n", img->width, img->height);
    fprintf (aFile, "%d\n", img->maxVal);
    fwrite(img->pixelData, sizeof(struct aPixel), img->width * img->height, aFile);
    fclose(aFile);
}

Image *
YellowDiagonal(Image *input)
{
	int i;
	int maxVal = input->width * input->height;
	for(i = 0;i< maxVal;i++)
	{
		input->pixelData[i].red=255;
		input->pixelData[i].green=255;
		input->pixelData[i].blue=0;
		i += input->width;
	}
	return input;   
}

int main(int argc, char *argv[])
{
   /* Read an image, apply yellow diagonal to it, then write */
	Image *img = ReadImage(argv[1]);
	img = YellowDiagonal(img);
	WriteImage(img, argv[2]);
	free(img);
	return 0;
}
