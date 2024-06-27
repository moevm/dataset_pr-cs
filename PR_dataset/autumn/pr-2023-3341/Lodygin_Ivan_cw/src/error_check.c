#include <wchar.h>
#include "structures.h"

int error_check(struct Text text){
    int checkbox = 0;
    for(int i = 0; i < text.n; i++){
        if(text.sents[i]->size == -2) checkbox = 1;
    }
    if(checkbox == 1) wprintf(L"Text entered incorrectly.\n");
    return checkbox;
}