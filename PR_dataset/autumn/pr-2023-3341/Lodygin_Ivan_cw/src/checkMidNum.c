#include <wchar.h>
#include <wctype.h>

int checkMidNum(wchar_t* word) {
    int posNum = 0; 
    int checkbox = 0; 
    posNum = wcslen(word); 
    if(posNum % 2 != 0) { 
        posNum = (posNum / 2); 
        if(iswdigit(word[posNum])) checkbox = 1; 
    } 
    return checkbox; 
}