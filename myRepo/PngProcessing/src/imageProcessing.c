#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include "structs.h"
#include "defines.h"
#include "imageProcessing.h"


void drawRect(struct Png* image, int x, int y, int height, int width, struct Color* color){
    int rect_h  = y + height;
    int rect_w = x + width;

    for(;y<rect_h;y++){
        png_byte* row = image->row_pointers[y];
        for(int i = x;i<rect_w;i++) {
            png_byte *pxl = &(row[i * 4]);
            if(!color){
                pxl[0] = 0;
                pxl[1] = 0;
                pxl[2] = 0;
            }
            else{
                pxl[0] = color->r;
                pxl[1] = color->g;
                pxl[2] = color->b;
            }
        }
    }
}


void changeColor(struct Png* image, struct Color* new_color){
    int len = 0, k = 1;
    struct CountColor* list = (struct CountColor*)calloc(REALLOC_SIZE, sizeof(struct CountColor));
    for(int y = 0;y<image->height;y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *pxl = &(row[x * 4]);
            long long int num = pxl[0]*pow(256, 2) + pxl[1]*256 + pxl[2];
            int flag = 0;
            for(int i = 0;i<len;i++){
                if(num == list[i].num){
                    flag = 1;
                    list[i].count++;
                }
            }
            if(!flag){
                len++;
                if(len == k*REALLOC_SIZE){
                    k++;
                    list = (struct CountColor*)realloc(list, k*REALLOC_SIZE*sizeof(struct CountColor));
                }
                list[len-1].count = 0;
                list[len-1].num = num;
            }
        }
    }

    long long int max = 0, color = 0;
    for(int i = 0;i<len;i++){
        if(list[i].count > max && list[i].num != 0){
            max = list[i].count;
            color = list[i].num;
        }
    }

    int r, g, b;
    b = color%256;
    color = color / 256;
    g = color % 256;
    color = color / 256;
    r = color % 256;

    for (int  y = 0; y < image->height; y++) {
        png_byte *row = image->row_pointers[y];
        for (int x = 0; x < image->width; x++) {
            png_byte *pxl = &(row[x * 4]);
            if(pxl[0] == r && pxl[1] == g && pxl[2] == b){
                pxl[0] = new_color->r;
                pxl[1] = new_color->g;
                pxl[2] = new_color->b;
            }
        }
    }

    free(list);
}


void fillSquare(struct Png* image, int x_begin, int y_begin, int x_end, int y_end, struct Color* color){
    for(;y_begin<y_end;y_begin++){
        png_byte* row = image->row_pointers[y_begin];
        for(int i = x_begin;i<x_end;i++){
            png_byte* pxl = &(row[i*4]);
            pxl[0] = color->r;
            pxl[1] = color->g;
            pxl[2] = color->b;
        }
    }
}


void drawSquare(struct Png* image, struct Coordinates leftAngle, int side, int depth, struct Color* lineColor, struct Color* fillColor){
    int x,y;
    x = leftAngle.x; y = leftAngle.y;

    if( x>= 0 &&  x<(image->width - side) && y >= 0 && y<(image->height - side)){
        int x_begin = x+depth, x_end = x+side-depth;
        int y_begin = y+depth, y_end = y+side-depth;
        drawRect(image, x, y, depth, side, lineColor);
        drawRect(image, x, y, side, depth, lineColor);
        drawRect(image, x, y+(side-depth), depth, side, lineColor);
        drawRect(image, x+(side-depth), y, side, depth, lineColor);
        if(!fillColor)
            return;
        fillSquare(image, x_begin, y_begin, x_end, y_end, fillColor);
    }
    else{
        printf(COORDINATES_ERROR);
        exit(COORDINATES_ERROR_CODE);
    }
}


void invertColors(struct Png* image, struct Coordinates leftAngle, struct Coordinates rightAngle){
    int xl, yl;
    int xr, yr;

    xl = leftAngle.x;  yl = leftAngle.y;
    xr = rightAngle.x; yr = rightAngle.y;

    if(-1 == leftAngle.x && -1 == leftAngle.y && -1 == rightAngle.x && -1 == rightAngle.y){
        xl = 0; yl = 0;
        xr = image->width; yr = image->height;
    }

    if(xl>=0 && yl>=0 && xr>=0 && yr>=0  && xr>xl && yr>yl && xl<=image->width && xr<=image->width && yl<=image->height && yr<=image->height){
        for (int y = yl; y < yr; y++) {
            png_byte *row = image->row_pointers[y];
            for (int x = xl; x < xr; x++) {
                png_byte *pxl = &(row[x * 4]);
                pxl[0] = (0xFFFFFF - pxl[0])%256;
                pxl[1] = (0xFFFFFF - pxl[1])%256;
                pxl[2] = (0xFFFFFF - pxl[2])%256;
            }
        }
    }
    else{
        printf(COORDINATES_ERROR);
        exit(COORDINATES_ERROR_CODE);
    }
}


void swap(struct Png* image, struct Coordinates leftAngle, struct Coordinates rightAngle,  char* mode) {
    int xl, yl;
    int xr, yr;

    xl = leftAngle.x; yl = leftAngle.y;
    xr = rightAngle.x; yr = rightAngle.y;


    if(xl%2!=0) xl--;
    if(yl%2!=0) yl--;
    if(xr%2!=0) xr--;
    if(yr%2!=0) yr--;

    if(xl>=0 && yl>=0 && xr>=0 && yr>=0  && xr>xl && yr>yl && xl<=image->width && xr<=image->width && yl<=image->height && yr<=image->height){
        png_bytep *image_cpy = (png_bytep *) malloc(sizeof(png_bytep) * image->height);
        if (!image_cpy) {
            printf(NO_ENOUGH_SPACE);
            exit(NO_ENOUGH_SPACE_CODE);
        }
        for (int y = 0; y < image->height; y++) {
            image_cpy[y] = (png_byte *) malloc(png_get_rowbytes(image->png_ptr, image->info_ptr));
            if (!image_cpy[y]) {
                printf(NO_ENOUGH_SPACE);
                for (int i = 0; i < y; i++)
                    free(image_cpy[i]);
                free(image_cpy);
                exit(NO_ENOUGH_SPACE_CODE);
            }
        }

        int xh, yh;
        xh = (xl+xr)/2;
        yh = (yl+yr)/2;

        for (int y = 0; y < image->height; y++) {
            png_byte *row = image->row_pointers[y];
            png_byte *row1 = image_cpy[y];
            for (int x = 0; x < image->width; x++) {
                png_byte *ptr = &(row[x * 4]);
                png_byte *ptr1 = &(row1[x * 4]);
                memcpy(ptr1, ptr, 4);
            }
        }
        if(0 == strcmp(mode, "circle")){
            for (int y1 = yl, y2 = yh; y1 < yh && y2 < yr; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y1];
                png_byte *row2 = image_cpy[y2];
                for (int x1 = xl, x2 = xl; x1 < xh && x2 < xh; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }

            for (int y1 = yl, y2 = yl; y1 < yh && y2 < yh; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y1];
                png_byte *row2 = image_cpy[y2];
                for (int x1 = xh, x2 = xl; x1 < xr && x2 < xh; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }

            for (int y1 = yh, y2 = yl; y1 < yr && y2 < yh; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y1];
                png_byte *row2 = image_cpy[y2];
                for (int x1 = xh, x2 = xh; x1 < xr && x2 < xr; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }

            for (int y1 = yh, y2 = yh; y1 < yr && y2 < yr; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y1];
                png_byte *row2 = image_cpy[y2];
                for (int x1 = xl, x2 = xh; x1 < xh && x2 < xr; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }
        }
        else if(0 == strcmp(mode, "diagonal")){
            for (int y1 = yl, y2 = yh; y1 < yh && y2 < yr; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y1];
                png_byte *row2 = image_cpy[y2];
                for (int x1 = xl, x2 = xh; x1 < xh && x2 < xr; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                    pxl1 = &(row1[x2 * 4]);
                    pxl2 = &(row2[x1 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }

            for (int y1 = yl, y2 = yh; y1 < yh && y2 < yr; y1++, y2++) {
                png_byte *row1 = image->row_pointers[y2];
                png_byte *row2 = image_cpy[y1];
                for (int x1 = xl, x2 = xh; x1 < xh && x2 < xr; x1++, x2++) {
                    png_byte *pxl1 = &(row1[x1 * 4]);
                    png_byte *pxl2 = &(row2[x2 * 4]);
                    memcpy(pxl1, pxl2, 4);
                    pxl1 = &(row1[x2 * 4]);
                    pxl2 = &(row2[x1 * 4]);
                    memcpy(pxl1, pxl2, 4);
                }
            }
        }

        for (int i = 0; i < image->height; i++)
            free(image_cpy[i]);
        free(image_cpy);
        return;
    }

    else{
        printf(COORDINATES_ERROR);
        exit(COORDINATES_ERROR_CODE);
    }
}