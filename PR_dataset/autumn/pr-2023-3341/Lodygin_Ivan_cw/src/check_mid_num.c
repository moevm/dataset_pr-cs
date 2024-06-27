#include <wchar.h>
#include <wctype.h>

int check_mid_num(wchar_t* word) {
    int pos_num = 0; 
    int checkbox = 0; 
    pos_num = wcslen(word); 
    if(pos_num % 2 != 0) { 
        pos_num = (pos_num / 2); 
        if(iswdigit(word[pos_num])) checkbox = 1; 
    } 
    return checkbox; 
}