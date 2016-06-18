#include <PNMreader.h>
#include <PNMwriter.h>
#include <filters.h>
#include <cstdlib>

int main(int argc, char *argv[])
{
	//PNMreader reader(argv[1]);
    int size = atoi(argv[2]);
    
    Color red(size,size,255,0,0);
    Color blue(size,size,0,0,255);
    
    Blender blend;
    blend.SetInput(red.GetOutput());
    blend.SetInput2(blue.GetOutput());

    blend.GetOutput()->Update();

    PNMwriter writer;
    writer.SetInput(blend.GetOutput());
    writer.Write(argv[1]);
}
