#ifndef FAILURE_HEADER
#define FAILURE_HEADER

#include <wchar.h>
#include <stdlib.h>

#define FAILURE_FUNCTION_NUMBER L"Error: Wrong number of function\n"
#define FAILURE_MEMORY L"Error: fail to allocation/reallocation memory\n"
#define FAILURE_INPUT L"Error: wrong input\n"

void failure(wchar_t * message_error);

#endif
