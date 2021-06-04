#ifndef IMAGE_PROCESSING_H
#define IMAGE_PROCESSING_H

#include "structs.h"

void printHelp();
void readPngFile(char *file_name, struct Png *image);
void writePngFile(char *file_name, struct Png *image);
void drawRect(struct Png* image, int x, int y, int height, int width, struct Color* color);
void changeColor(struct Png* image, struct Color* new_color);
void fillSquare(struct Png* image, int x_begin, int y_begin, int x_end, int y_end, struct Color* color);
void drawSquare(struct Png* image, struct Coordinates leftAngle, int side, int depth, struct Color* lineColor, struct Color* fillColor);
void invertColors(struct Png* image, struct Coordinates leftAngle, struct Coordinates rightAngle);
void swap(struct Png* image, struct Coordinates leftAngle, struct Coordinates rightAngle,  char* mode);

#endif 