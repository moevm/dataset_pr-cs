#ifndef ERRORS_H
#define ERRORS_H

#include <pixels.h>

#define OPTION_ERR 40

#define CALL_FLAG_ERR 41

#define FILE_OPEN_ERR 42

#define FILE_TYPE_ERR 43

#define READ_VALUE_ERR 44

#define POINT_ERR 45

#define THICKNESS_ERR 46

#define COLOR_ERR 47

void raise_error(const char* message, int error_code);

void check_sscanf(int result, int expected);

void check_crop_params(unsigned int w, unsigned int h, point_t* left_up, point_t* right_down);

void check_thickness(int thickness);

#endif