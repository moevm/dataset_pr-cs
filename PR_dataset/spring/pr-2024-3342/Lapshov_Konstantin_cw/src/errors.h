#pragma once
#include <stdlib.h>
#include <stdio.h>

#define FILE_OPEN_FAILURE 40
#define FILE_READ_FAILURE 41
#define FILE_WRITE_FAILURE 42
#define MEMORY_ALLOCATION_FAILURE 43
#define ARGUMENTS_FAILURE 44
#define DATA_FAILURE 45

void showError(char* message, int errorType);