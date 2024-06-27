#ifndef stdio
#include <stdio.h>
#endif

#include "getcommand.h"


int getcommand(){
    int command = getchar();
    if (getchar() != '\n') return -1;
    return command - '0';
}
