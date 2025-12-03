/*
    @file pixel.h
*/

#include <stdio.h>
#include <stdlib.h>

typedef struct sPixel
{
    int r;
    int g;
    int b;
} *Pixel;

typedef struct sImageBuffer
{
    int height;
    int width;
    Pixel data;
} *ImageBuffer;

/*
    @brief Initialize an empty buffer
    @param height Height of the image in pixels
    @param width Width of the image in pixels
    @return Return a pointer to the buffer
*/

ImageBuffer pxl_initEmptyBuffer(int height, int width);

/*
    @brief Initialize a buffer storing image height, width, and every pixels's RGB values as a sPixel structure.
    @param *data Pointer to the first pixel, returned by stbi_load()
    @param height Height of the image in pixels
    @param width Width of the image in pixels
    @return Return a pointer to the buffer

    @note Height and width must be correctly match the actual size of data. Passing incorrect values may lead to out-of-bounds access and segmentation faults.
*/

ImageBuffer pxl_initBuffer(unsigned char *data, int height, int width);

/*
    @brief Return the pixel at the coordinates (x, y)
    @param buffer Pointer to the buffer you want the pixel from
    @param x Coordinate x
    @param y Coordinate y
    @return Return the pixel's RGB values as a sPixel structure
    
    @see pxl_initBuffer
*/
struct sPixel pxl_getPixel(ImageBuffer buffer, int x, int y);
