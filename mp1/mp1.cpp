#include <string>
#include "cs225/PNG.h"

using namespace cs225;

void rotate(std::string inputFile, std::string outputFile) {
    PNG pngobject;
    if (pngobject.readFromFile(inputFile)==0) return;
    unsigned int width = pngobject.width();
    unsigned int height= pngobject.height();
    PNG output = pngobject  ;
    for (unsigned int i=0; i< width;i++){
        for (unsigned int j=0; j<height;j++){
            HSLAPixel *pixel = pngobject.getPixel(i,j);
            HSLAPixel *pixelout = output.getPixel(width-1-i,height-1-j);
            pixelout->h = pixel->h;
            pixelout->a = pixel->a;
            pixelout->l = pixel->l;
            pixelout->s = pixel->s;
        }
    }    
    if (output.writeToFile(outputFile)==0) return;

    
}
