#ifndef CWERROR_H
#define CWERROR_H

#include <stdio.h>
#include <stdlib.h>

#define MEMORY_ERROR_RET_VAL 40
#define MEMORY_ERROR_MSG "Cannot allocate of free dynamic memory on heap."
#define FILE_ERROR_RET_VAL 41
#define FILE_ERROR_MSG "File cannot be opened. Perhaps, this file does not exits."
#define BMP_DATA_ERROR_RET_VAL 42
#define BMP_DATA_ERROR_MSG "Header cannot be read or written."
#define NOT_A_BMP_ERROR_RET_VAL 43
#define NOT_A_BMP_ERROR_MESSAGE "Input is either not a BMP file or incorrect BMP file format. This program only accepts 24-bit BMP files with no compression."
#define INVALID_COORDINATE_ERROR_RET_VAL 44
#define INVALID_COORDINATE_ERROR_MSG "Invalid pixel coordinate."
#define INVALID_RGB_ERROR_RET_VAL 45
#define INVALID_RGB_ERROR_MSG "Invalid pixel color."
#define INVALID_DRAWING_COORDINATES_RET_VAL 46
#define INVALID_DRAWING_COORDINATES_MSG "Invalid coordinates for a figure (e.g. start, end, center, etc.)"
#define INVALID_OPTION_ARGUMENT_ERROR_RET_VAL 47
#define INVALID_OPTION_ARGUMENT_ERROR_MSG "Option has an invalid argument."
#define OPTION_ERROR_RET_VAL 48
#define OPTION_ERROR_MSG "Unknown option, invalid option, invalid argument, missing argument, etc."
#define CONFIG_ERROR_RET_VAL 49
#define CONFIG_ERROR_MSG "Invalid configuration."


void throw_error(const char *text, int return_value);


#endif