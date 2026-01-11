#include "../include/resize.h"
#include <math.h>

ImageBuffer rsz_areaAveragingDownscale(ImageBuffer image, int height, int width){
    // This code is probably unsafe. 
    // It also approximate a lot.
    // Will patch it later.
    // No i won't write unit test for now.

    if(height == 0 || width == 0 || image == NULL){
        return NULL;
    } else if(image->data == NULL){
        return NULL;
    }

    ImageBuffer downscaledImage = pxl_initEmptyBuffer(height, width);
    float xRatio = (float)width / image->width;
    float yRatio = (float)height / image->height;

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            struct sPixel downScaledPixel = {0, 0, 0};
            for(int n = floor(y * yRatio); n < ceil((y + 1) * yRatio); n++){
                for(int m = floor(x * xRatio); m < ceil((x + 1)* xRatio); m++){

                    struct sPixel pixel = pxl_getPixel(image, n, m);
                    downScaledPixel.r += pixel.r;
                    downScaledPixel.g += pixel.g;
                    downScaledPixel.b += pixel.b;
                }
            }
            int amountOfPixel =  ceil(xRatio) * ceil(yRatio);
            downScaledPixel.r /= amountOfPixel;
            downScaledPixel.g /= amountOfPixel;
            downScaledPixel.b /= amountOfPixel;
            downscaledImage->data[y * width + x] = downScaledPixel;
        }
    }

    return downscaledImage;
} 