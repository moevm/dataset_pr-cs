#define _CRT_SECURE_NO_WARNINGS 

#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#define STR_SIZE 100

#include "first_info.h"
#include "option.h"
#include "errors.h"

enum error_list { OPTION_ERROR, END_DOT, VOID_STR, VOID_TEXT };

int main(void) {
    setlocale(LC_CTYPE, "");

    first_info(); 
    int option = get_option(); 
    if (option_exsist(option)) {
        running_option(option);
    }
    else {
        error(OPTION_ERROR);
    }
    return 0;
}
