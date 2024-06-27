#include "begin.h"
#include <wchar.h>
int begin(void){
    wprintf(L"Course work for option 5.17, created by Danila Pachev.\n");
    int option;
    wscanf(L"%d",&option);
    getwchar();

    return option;
}