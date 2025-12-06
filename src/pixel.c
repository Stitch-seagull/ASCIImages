#include "../include/pixel.h"

ImageBuffer pxl_initEmptyBuffer(int height, int width){

    if(height <=0 || width <= 0){
        return NULL;
    }

    ImageBuffer buffer = malloc(sizeof(struct sImageBuffer));
    buffer->height = height;
    buffer->width = width;
    buffer->data = malloc(sizeof(struct sPixel) * height * width);
    return buffer;
}

ImageBuffer pxl_initBuffer(unsigned char *data, int height, int width){

    ImageBuffer buffer = pxl_initEmptyBuffer(height, width);
    
    if(buffer == NULL){
        return NULL;
    } else if(data == NULL){
        return NULL;
    }

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

void pxl_freeBuffer(ImageBuffer buffer){
    if(buffer == NULL){
        return;
    } else {
        free(buffer->data);
        free(buffer);
    }
};

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

