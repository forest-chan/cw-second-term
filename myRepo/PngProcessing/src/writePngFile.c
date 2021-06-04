#include <stdio.h>
#include <stdlib.h>
#include <png.h>
#include "structs.h"
#include "defines.h"


void writePngFile(char *file_name, struct Png *image) {
    int x,y;

    FILE *fp = fopen(file_name, "wb");
    if (!fp){
        printf(OPEN_FILE_ERROR);
        exit(OPEN_FILE_ERROR_CODE);
    }


    image->png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

    if (!image->png_ptr){
        printf(PNG_CREATE_WRITE_STRUCT_ERROR);
        exit(PNG_CREATE_WRITE_STRUCT_ERROR_CODE);
    }

    image->info_ptr = png_create_info_struct(image->png_ptr);
    if (!image->info_ptr){
        printf(PNG_CREATE_INFO_STRUCT_ERROR);
        exit(PNG_CREATE_INFO_STRUCT_ERROR_CODE);
    }

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf(INIT_IO_ERROR);
        exit(INIT_IO_ERROR_CODE);
    }

    png_init_io(image->png_ptr, fp);

    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf(WRITE_IMAGE_ERROR);
        exit(WRITE_IMAGE_ERROR_CODE);
    }

    png_set_IHDR(image->png_ptr, image->info_ptr, image->width, image->height,
                 image->bit_depth, image->color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_BASE, PNG_FILTER_TYPE_BASE);

    png_write_info(image->png_ptr, image->info_ptr);



    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf(WRITE_IMAGE_ERROR);
        exit(WRITE_IMAGE_ERROR_CODE);
    }

    png_write_image(image->png_ptr, image->row_pointers);



    if (setjmp(png_jmpbuf(image->png_ptr))){
        printf(WRITE_IMAGE_ERROR);
        exit(WRITE_IMAGE_ERROR_CODE);
    }

    png_write_end(image->png_ptr, NULL);


    for (y = 0; y < image->height; y++)
        free(image->row_pointers[y]);
    free(image->row_pointers);

    fclose(fp);
}