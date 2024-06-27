#include "../headers/get-option.h"
int get_option(){
    wchar_t ch = getwchar();
    return ch - L'0';
}