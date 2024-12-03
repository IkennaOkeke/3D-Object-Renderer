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

    // variables to store integer conversions of colour
    int x = (int)color.x; 
    int y = (int)color.y;
    int z = (int)color.z;

    //checks for any outlier RGB values, handles them accordingly
    if (x > 255) {
        x = 255;
    }
    if (y > 255) {
        y = 255;
    }
    if (z > 255) {
        z = 255;
    }

    if (x < 0) {
        x = 0;
    }
    if (y < 0) {
        y = 0;
    }
    if (y < 0) {
        y = 0;
    }

    //prints colour to output file
    fprintf(ppmFile, "%d %d %d\n", x, y, z);

}



int compareColor(const void *a, const void *b);