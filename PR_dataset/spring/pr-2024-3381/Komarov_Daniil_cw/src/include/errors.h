#ifndef ERRORS_H
#define ERRORS_H
#include <stdio.h>
// --------------------------------------------------------
// ARGPARSE ERRORS (MSG STRINGS)
// --------------------------------------------------------
#define MODE_ERR_MSG "Please select only one function at time.\n"
#define MULTIPLE_FILES_DETECTED "Multiple input files or bad options found!\n"
#define NO_INPUT_FILE "No input file! Run with -h to show help.\n"
#define ARG_ERR_MSG "Unknown argument: -%s\n"


#define MISSING_ARG "Missing \"%s\" argument!\n"
#define WRONG_ARG   "Argument \"%s\" must have format \"%s\"!\n"

// Used directly in tasks.c
#define TASK_RECT_WRONG_COLOR "Unable to find rectangle of selected color!\n"

// --------------------------------------------------------
// GLOBAL ERRORS (RETCODES)
// --------------------------------------------------------
#define RETCODE_OK            0
#define RETCODE_ARG_ERROR    40
#define RETCODE_IO_ERROR     41
#define RETCODE_FILE_ERROR   42
#define RETCODE_MEMORY_ERROR 43

// --------------------------------------------------------
// GLOBAL ERRORS (MSG STRINGS)
// --------------------------------------------------------
#define MALLOC_ERROR "An error occured during memory (re)allocation!\n"
#define READ_IO_ERR "File not found or inaccessible!\n"
#define READ_FILE_ERR "Unknown file type or file is corrupted!\n"
#define SAME_FILES_ERR "Input and output are the same file!\n"

int handle_error(int status_code);

#endif
