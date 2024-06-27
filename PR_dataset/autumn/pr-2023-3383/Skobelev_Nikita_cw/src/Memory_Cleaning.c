#include "my_lib.h"

void memory_cleaning(struct Text* text){
    for(int i=0;i<(text->cnt_sen);++i){
        free(text->txt[i].snt);
    }
    free(text->txt);
}
