#include "../include/pixel.h"

ImageBuffer pxl_initBuffer(unsigned char *data, int height, int width){
    ImageBuffer buffer = malloc(sizeof(struct sImageBuffer));
    buffer->height = height;
    buffer->width = width;
    buffer->data = malloc(sizeof(struct sPixel) * height * width);

    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++){
            int pixelOffset = y * width + x;
            int dataOffset = pixelOffset * 3; 
            buffer->data[pixelOffset].r = data[dataOffset];
            buffer->data[pixelOffset].g = data[dataOffset + 1];
            buffer->data[pixelOffset].b = data[dataOffset + 2];
        }
    }

    return buffer;
}

struct sPixel pxl_getPixel(ImageBuffer buffer, int x, int y)
{
    struct sPixel error;
        error.r = -1;
        error.g = -1;
        error.b = -1;

    if(buffer == NULL || buffer->data == NULL){
        return error;
    } else if ( x < 0 || y < 0 || x >= buffer->width || y >= buffer->height){
        return error;
    }

    return buffer->data[y * buffer->width + x];
};
