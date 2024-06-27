#include <stdio.h>
#include <wchar.h>
#include "header_files/getChoise.h"

int getChoise(){
    int result;
    wscanf(L"%d\n", &result);
    return result;
}