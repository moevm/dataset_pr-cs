#ifndef ERRORS_H
#define ERRORS_H

#include <stdio.h>
#include <stdlib.h>
#include "structs.h"


#define ERROR_INCORRECT_FILE_FORMAT 40

#define ERROR_FILE_READ_FAILURE 41

#define ERROR_FILE_WRITE_FAILURE 42

#define ERROR_INVALID_ARGUMENT 43

#define ERROR_MULTIPLE_FUCTION_REQUEST 44

#define ERROR_MISSING_REQUIRED_ARGUMENT 45

#define ERROR_MISSING_REQUIRED_OPTION 46

#define ERROR_UNEXPECTED_OPTION 47

#define ERROR_UNKNOWN_OPTION 48


extern const char* input_file_not_found;

extern const char* same_input_and_output_files;

extern const char* incorrect_file_format;

extern const char* can_not_read_the_file;

extern const char* can_not_write_to_the_file;

extern const char* invalid_argument;

extern const char* missing_required_argument;

extern const char* missing_required_option;

extern const char* unexpected_option;

extern const char* multiple_function_request;

extern const char* unknown_option;

extern const char* incorrect_rgb_format;

extern const char* invalid_rgb_component_value;

extern const char* invalid_rgb_component_name;

extern const char* invalid_parts_number;

extern const char* invalid_thickness;

extern const char* invalid_threshold;

extern const char* hello_message;


void raiseError(const char* statement, int exit_code);


#endif
