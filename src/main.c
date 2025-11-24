#include <stdio.h>
#include <ncurses.h>
#define STB_IMAGE_IMPLEMENTATION
#include "../libraries/stb_image.h"

int main(int argc, char *argv[]){
    if(argc != 2){
        fprintf(stderr,"Usage : /ASCIImages <imagePath> \n");
    } else {
        char *path = argv[1];
        int height = 0, width = 0, n = 0;

        // Forcing RGB format
        unsigned char *img = stbi_load(path, &height, &width, &n, 3);
        if(img == NULL){
            if(strcmp(stbi_failure_reason(), "can't fopen\n")){
                fprintf(stderr, "Cannot find \x1b[36m%s\x1b[0m or \x1b[36m%s\x1b[0m is not an image\n", path, path);
            } else {
                fprintf(stderr, "%s \n",stbi_failure_reason());
            }
        }
    }

    return 0;
}