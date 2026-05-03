#include <criterion/criterion.h>
#include <criterion/parameterized.h>
#include <criterion/logging.h>

#include <unistd.h>
#include <linux/limits.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/stb_image.h"
#include "../libraries/cwalk.h"
#include "../include/pixel.h"

// ========= Code coverage =========
// 
// Verify code coverage with gcovr : https://github.com/gcovr/gcovr
// bash: gcovr -f src/
//
// =================================


// ========= Structures =========

struct intTuple {
    int x;
    int y;
};

struct imgData {
    unsigned char* data;
    int height, witdh;
};

struct pixelColorTuple {
    int x,y;
    struct sPixel p;
};

// ========= initEmptyBuffer =========

ParameterizedTestParameters(initEmptyBuffer, defaultBehavior){
    static struct intTuple params[] = {
        {10000, 10000},
        {50, 100},
        {100, 50},
    };

    return cr_make_param_array(struct intTuple, params, sizeof(params) / sizeof(struct intTuple));
}

ParameterizedTest(struct intTuple *tuple, initEmptyBuffer, defaultBehavior){
    ImageBuffer buffer = pxl_initEmptyBuffer(tuple->x, tuple->y);

    cr_assert_not_null(buffer);
    cr_assert_not_null(buffer->data);

    cr_assert(buffer->height == tuple->x);
    cr_assert(buffer->width == tuple->y);

    pxl_freeBuffer(buffer);
}

ParameterizedTestParameters(initEmptyBuffer, invalidInput){
    static struct intTuple params[] = {
        {-5, 100},
        {100, -5},
        {-5, -5},
    };

    return cr_make_param_array(struct intTuple, params, sizeof(params) / sizeof(struct intTuple));
}

ParameterizedTest(struct intTuple *tuple, initEmptyBuffer, invalidInput){
    ImageBuffer buffer = pxl_initEmptyBuffer(tuple->x, tuple->y);

    cr_assert_null(buffer);

    pxl_freeBuffer(buffer);
}

// ========= initBuffer =========

ParameterizedTestParameters(initBuffer, invalidInput){
    static struct intTuple params[] = {
        {-5, 100},
        {100, -5},
        {-5, -5},
    };

    return cr_make_param_array(struct intTuple, params, sizeof(params) / sizeof(struct intTuple));
}

ParameterizedTest(struct intTuple *tuple, initBuffer, invalidInput){
    unsigned char data = 0;
    ImageBuffer buffer = pxl_initBuffer(&data, tuple->x, tuple->y);
    
    cr_assert_null(buffer);

    pxl_freeBuffer(buffer);
}

Test(initBuffer, dataNULL){
    ImageBuffer buffer = pxl_initBuffer(NULL, 100, 100);

    cr_assert_null(buffer);

    pxl_freeBuffer(buffer);
}

struct imgData checker2x3;

void setupChecker(void){
    char filePath[FILENAME_MAX]; strcpy(filePath, __FILE__);
    char imgPath[FILENAME_MAX];

    cwk_path_join(filePath, "../images/2x3Checkerboard.png", imgPath, sizeof(imgPath));

    int height, width, n;
    unsigned char *img = stbi_load(imgPath, &height, &width, &n, 3);
    
    cr_assert_not_null(img);
    checker2x3.data = img;
    checker2x3.height = height;
    checker2x3.witdh = width;
}

void teardownChecker(void){
    stbi_image_free(checker2x3.data);
}

Test(initBuffer, defaultBehavior, .init= setupChecker, .fini = teardownChecker){
    ImageBuffer buffer = pxl_initBuffer(checker2x3.data, checker2x3.height, checker2x3.witdh);

    for(int x = 0; x < checker2x3.height; x++){
        for(int y = 0; y < checker2x3.witdh; y++){
            struct sPixel p = pxl_getPixel(buffer, y, x);
            if((x*2 + y) % 2 == 1){
                cr_expect(pxl_cmpPixel(p, (struct sPixel){255, 255, 255}) == true);
            } else {
                cr_expect(pxl_cmpPixel(p, (struct sPixel){0, 0, 0}) == true);
            }
        }
    }
}

// ========= getPixel =========


struct imgData primary2x3;

void setupPrimary(void){
    char filePath[FILENAME_MAX]; strcpy(filePath, __FILE__);
    char imgPath[FILENAME_MAX];

    cwk_path_join(filePath, "../images/2x3PrimaryColors.png", imgPath, sizeof(imgPath));

    int height, width, n;
    unsigned char *img = stbi_load(imgPath, &width, &height, &n, 3);

    cr_assert_not_null(img);
    primary2x3.data = img;
    primary2x3.height = height;
    primary2x3.witdh = width;
}

void teardownPrimary(void){
    stbi_image_free(primary2x3.data);
}

ParameterizedTestParameters(getPixel, defaultBehavior){
    static struct pixelColorTuple params[] = {
        {0, 0, {255, 0, 0}},
        {1, 0, {0, 255, 0}},
        {2, 0, {0, 0, 255}},
    };

    return cr_make_param_array(struct pixelColorTuple, params, sizeof(params) / sizeof(struct pixelColorTuple));
}

ParameterizedTest(struct pixelColorTuple *ptuple, getPixel, defaultBehavior, .init= setupPrimary, .fini = teardownPrimary){
    ImageBuffer buffer = pxl_initBuffer(primary2x3.data, primary2x3.height, primary2x3.witdh);

    cr_assert_not_null(buffer);
    cr_assert(pxl_cmpPixel(pxl_getPixel(buffer, ptuple->x, ptuple->y), ptuple->p) == true);

    pxl_freeBuffer(buffer);
}


ParameterizedTestParameters(getPixel, invalidInput){
    static struct intTuple params[] = {
        {-1, 1},
        {1, -1},
        {100, 1},
        {1, 100},
    };

    return cr_make_param_array(struct intTuple, params, sizeof(params) / sizeof(struct intTuple));
}

ParameterizedTest(struct intTuple *tuple, getPixel, invalidInput, .init= setupPrimary, .fini = teardownPrimary){
    ImageBuffer buffer = pxl_initBuffer(primary2x3.data, primary2x3.height, primary2x3.witdh);

    cr_assert(pxl_cmpPixel(pxl_getPixel(buffer, tuple->x, tuple->y), (struct sPixel){-1, -1, -1}) == true);

    pxl_freeBuffer(buffer);
}

Test(getPixel, bufferNULL){
    cr_assert(pxl_cmpPixel(pxl_getPixel(NULL, 1, 1), (struct sPixel){-1, -1, -1}) == true);
}

Test(getPixel, dataNULL){
    struct sImageBuffer sbuffer = {1, 1, NULL}; 
    ImageBuffer buffer = &sbuffer;

    cr_assert(pxl_cmpPixel(pxl_getPixel(buffer, 1, 1), (struct sPixel){-1, -1, -1}) == true);
}

// ========= cmpPixel =========

Test(cmpPixel, true){
    cr_assert(pxl_cmpPixel((struct sPixel){255, 255, 255}, (struct sPixel){255, 255, 255}) == true);
}

Test(cmpPixel, false){
    cr_assert(pxl_cmpPixel((struct sPixel){255, 255, 255}, (struct sPixel){0, 0, 0}) == false);
}