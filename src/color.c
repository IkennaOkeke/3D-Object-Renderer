#include "color.h"
#include "vector.h"
#include <stdio.h>

Vec3 unpackRGB(unsigned int packedRGB) {

    // get red colour by dividing by 16^4 (to get the first two components of hex value)
    unsigned int red = packedRGB / 65536;

    //get green colour by dividing by 16^2 and modding by 16^2(to get second two components of hex value)
    unsigned int green = (packedRGB / 256) % 256;

    //get blue colour by modding by 16^2 (to get third component of hex value)
    unsigned int blue = packedRGB % 256;   


    Vec3 colour = {red / 255.0, green / 255.0, blue / 255.0};
    return colour;
}



void writeColour(FILE *ppmFile, Vec3 color) {

}



int compareColor(const void *a, const void *b) {

}
