#include "../include/resize.h"
#include <math.h>

ImageBuffer rsz_areaAveragingDownscale(ImageBuffer source, int height, int width){

    if(height <= 0 || width <= 0 || source == NULL){
        return NULL;
    } else if(source->data == NULL){
        return NULL;
    }

    ImageBuffer output = pxl_initEmptyBuffer(height, width);

    if(output == NULL){
        return NULL;
    }

    float xRatio =  source->width / (float)width ;
    float yRatio =  source->height / (float)height ;
    
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){

            float amountOfPixel = 0.0f;
            float r = 0, g = 0, b = 0;

            float xStart = x * xRatio; 
            float xEnd = (x + 1) * xRatio;
            float yStart = y * yRatio; 
            float yEnd = (y + 1) * yRatio;

            for(int sy = floorf(yStart); sy < ceilf(yEnd); sy++){
                for(int sx = floorf(xStart); sx < ceilf(xEnd); sx++){

                    float xWeight = fminf(xEnd, sx + 1.0f) - fmaxf(xStart, sx);
                    float yWeight = fminf(yEnd, sy + 1.0f) - fmaxf(yStart, sy);
                    float weight = xWeight * yWeight;
                    
                    struct sPixel pixel = pxl_getPixel(source, sy, sx);
                    r += pixel.r * weight;
                    g += pixel.g * weight;
                    b += pixel.b * weight;
                    amountOfPixel += weight;
                }
            }

            struct sPixel op = {(int)roundf(r / amountOfPixel), (int)roundf(g / amountOfPixel), (int)roundf(b / amountOfPixel)};
            output->data[y * width + x] = op;
        }
    }

    return output;
}