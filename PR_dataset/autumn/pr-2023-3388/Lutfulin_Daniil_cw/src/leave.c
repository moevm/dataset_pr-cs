#include "leave.h"

void leave(wchar_t *message){
    wprintf(L"%ls", message);
    exit(0);
}

void free_text(Text *text){
    for(size_t i = 0; i<text->len;i++){
        free(text->data[i]->data);
        free(text->data[i]);
    }
    free(text);
}
