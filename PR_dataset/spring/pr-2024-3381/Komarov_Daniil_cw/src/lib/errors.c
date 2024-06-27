#include "../include/errors.h"
#include <stdio.h>

int handle_error(int status_code)
{
    switch(status_code) {
    case RETCODE_ARG_ERROR:
        // There is no message for argument error
        // because getopt will show this message
        break;
    case RETCODE_IO_ERROR:
        fprintf(stderr, READ_IO_ERR);
        break;
    case RETCODE_FILE_ERROR:
        fprintf(stderr, READ_FILE_ERR);
        break;
    case RETCODE_MEMORY_ERROR:
        fprintf(stderr, MALLOC_ERROR);
        break;
    }
    return status_code;
}
