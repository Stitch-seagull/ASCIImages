#include <criterion/criterion.h>
#include <criterion/parameterized.h>

#include <unistd.h>
#include <linux/limits.h>

#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/stb_image.h"
#include "../libraries/cwalk.h"
#include "../include/resize.h"

// ========= Code coverage =========
// 
// Verify code coverage with gcovr : https://github.com/gcovr/gcovr
// bash: gcovr -f src/
//
// =================================

// ========= areaAveragingDownscale =========

struct intTuple {
    int x;
    int y;
};

struct imgData {
    unsigned char* data;
    int height, witdh;
};

ParameterizedTestParameters(areaAveragingDownscale, invalidOutput){
    static struct intTuple params[] = {
        {100, -6},
        {-6, 100},
        {-6, -6},
    };

    return cr_make_param_array(struct intTuple, params, sizeof(params) / sizeof(struct intTuple));
}

ParameterizedTest(struct intTuple *tuple, areaAveragingDownscale, invalidOutput){
    ImageBuffer source = pxl_initEmptyBuffer(10, 10);
    ImageBuffer output = rsz_areaAveragingDownscale(source, tuple->y, tuple->x);

    cr_assert_null(output);

    pxl_freeBuffer(output);
}

Test(areaAveragingDownscale, bufferNULL){
    ImageBuffer output = rsz_areaAveragingDownscale(NULL, 100, 100);
    cr_assert_null(output);
}

Test(areaAveragingDownscale, dataNULL){
    struct sImageBuffer sbuffer = {1, 1, NULL}; 
    ImageBuffer source = &sbuffer;

    ImageBuffer output = rsz_areaAveragingDownscale(source, 100, 100);
    cr_assert_null(output);
}


struct imgData column3x3;

void setupColumn(void){
    char filePath[FILENAME_MAX]; strcpy(filePath, __FILE__);
    char imgPath[FILENAME_MAX];

    cwk_path_join(filePath, "../images/3x3BlackColumn.png", imgPath, sizeof(imgPath));

    int height, width, n;
    unsigned char *img = stbi_load(imgPath, &height, &width, &n, 3);
    
    cr_assert_not_null(img);
    column3x3.data = img;
    column3x3.height = height;
    column3x3.witdh = width;
}

void teardownColumn(void){
    stbi_image_free(column3x3.data);
}

Test(areaAveragingDownscale, blackColumn3x3to2x2, .init = setupColumn, .fini = teardownColumn){
    ImageBuffer source = pxl_initBuffer(column3x3.data, column3x3.height, column3x3.witdh);

    ImageBuffer output = rsz_areaAveragingDownscale(source, 2, 2);

    for(int x = 0; x < 2; x++){
        for(int y = 0; y < 2; y++){
            cr_assert(pxl_cmpPixel(pxl_getPixel(output, x, y),(struct sPixel){170, 170, 170}) == true);
        }
    }
}

