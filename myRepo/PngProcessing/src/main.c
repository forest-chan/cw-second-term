#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <ctype.h>
#include <png.h>
#include <unistd.h>
#include <getopt.h>
#include "structs.h"
#include "defines.h"


int main(int argc, char* argv[]) {
    struct Png image;
    struct Coordinates leftAngle = {-1, -1};
    struct Coordinates rightAngle = {-1, -1};
    struct Color* color = NULL;
    struct Color* lineColor;
    char* opts = "f:s:e:l:o:C:D:IS:h?";
    char* outputFile = NULL;
    char* mode;
    char flag = 'a';
    int opt, longIndex;
    int side = -1, depth = -1;
    struct Color colors_list [10] ={
            {"red",255,0,0}, {"orange",255,103,0}, {"yellow",255,255,53},
            {"green",0,255,0}, {"lightblue",102,179,255},{"blue",0,0,255}, {"violet",128,0,255},
            {"gray", 169,169,169}, {"black",0,0,0}, {"white",255,255,255}
    };
    struct option longOpts[]={
            {"help", no_argument, NULL, 'h'},
            {"out", required_argument, NULL, 'o'},
            {"start", required_argument, NULL, 's'},
            {"end", required_argument, NULL, 'e'},
            {"fill-color", required_argument, NULL, 'f'},
            {"line-color", required_argument, NULL, 'l'},
            {"change-most-frequent-color", required_argument, NULL, 'C'},
            {"draw-square", required_argument, NULL, 'D'},
            {"invert-colors", no_argument, NULL, 'I'},
            {"swap-parts", required_argument, NULL, 'S'},
            {NULL, 0, NULL, 0}
    };
    opterr = 0;
    opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    while(opt != -1){
        switch (opt) {
            case '?':
            case 'h':
                printHelp();
                return 0;
            case 'o':
                if(!strstr(optarg, ".png")){
                    printf(FILE_FORMAT_ERROR);
                    exit(FILE_FORMAT_ERROR_CODE);
                }
                outputFile = calloc(strlen(optarg)+1, sizeof(char));
                strcpy(outputFile, optarg);
                break;
            case 's':
                if(2 != sscanf(optarg, "%d,%d", &leftAngle.x, &leftAngle.y)){
                    printf(WRITE_COORDINATES_ERROR);
                    exit(WRITE_COORDINATES_ERROR_CODE);
                }
                break;
            case 'e':
                if(2 != sscanf(optarg, "%d,%d", &rightAngle.x, &rightAngle.y)){
                    printf(WRITE_COORDINATES_ERROR);
                    exit(WRITE_COORDINATES_ERROR_CODE);
                }
                break;
            case 'f':
                for(int i = 0;i<10;i++){
                    if(0 == strcmp(optarg, colors_list[i].name)){
                        color = &colors_list[i];
                        break;
                    }
                }
                break;
            case 'l':
                for(int i = 0;i<10;i++){
                    if(0 == strcmp(optarg, colors_list[i].name)){
                        lineColor = &colors_list[i];
                        break;
                    }
                }
                break;
            case 'C':
                for(int i = 0;i<10;i++){
                    if(0 == strcmp(optarg, colors_list[i].name)){
                        color = &colors_list[i];
                        break;
                    }
                }
                if(!color){
                    printf(WRITE_COLOR_TO_CHANGE_ERROR);
                    exit(WRITE_COLOR_TO_CHANGE_ERROR_CODE);
                }
                flag = 'c';
                break;
            case 'D':
                if(2 != sscanf(optarg, "%d,%d", &side, &depth)){
                    printf(WRITE_SQUARE_PARAMS_ERROR);
                    exit(WRITE_SQUARE_PARAMS_ERROR_CODE);
                }
                flag = 'd';
                break;
            case 'I':
                flag = 'i';
                break;
            case 'S':
                if(0 != strcmp(optarg, "diagonal") && 0 != strcmp(optarg, "circle")){
                    printf(INCORRECT_MODE_ERROR);
                    exit(INCORRECT_MODE_ERROR_CODE);
                }
                mode = calloc(strlen(optarg)+1, sizeof(char));
                strcpy(mode, optarg);
                flag = 's';
                break;
            default:
                printHelp();
                return 0;
        }
        opt = getopt_long(argc, argv, opts, longOpts, &longIndex);
    }

    argc -= optind;
    argv += optind;

    if(argc != 1){
        printf(WRONG_ARGS_ERROR);
        exit(WRONG_ARGS_ERROR_CODE);
    }

    if(!strstr(argv[0], ".png")){
        printf(FILE_FORMAT_ERROR);
        exit(FILE_FORMAT_ERROR_CODE);
    }

    if(-1 == side && -1 == depth){
        side = depth = 0;
    }

    if('a' == flag){
        printf(NO_FUNCTION_SELECTED_ERROR);
        exit(NO_FUNCTION_SELECTED_ERROR_CODE);
    }
    
    readPngFile(argv[0], &image);

    if(png_get_color_type(image.png_ptr, image.info_ptr) != PNG_COLOR_TYPE_RGBA){
        printf(PNG_COLOR_TYPE_ERROR);
        exit(PNG_COLOR_TYPE_ERROR_CODE);
    }

    if(depth > side || side < 0 || depth < 0
       || side > image.height || side > image.width){
        printf(SQUARE_PARAMS_ERROR);
        exit(SQUARE_PARAMS_ERROR_CODE);
    }

    switch(flag){
        case 'c':
            changeColor(&image, color);
            break;
        case 'd':
            drawSquare(&image, leftAngle, side, depth, lineColor, color);
            break;
        case 'i':
            invertColors(&image, leftAngle, rightAngle);
            break;
        case 's':
            swap(&image, leftAngle, rightAngle, mode);
            break;
    }

    if(!outputFile){
        outputFile = calloc(FILE_SIZE, sizeof(char));
        strcpy(outputFile, "out.png");
    }
    
    writePngFile(outputFile, &image);
    return 0;
}

