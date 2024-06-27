#include <stdlib.h>
#include "../header/allocator.h"

void allocator(char* keyword, char* no_split_text, char** split_text, int* sent_num){
    keyword=NULL;
    free(no_split_text);
    for (int i = 0; i < *sent_num; ++i) {
        split_text[i]=NULL;
    }
    free(split_text);
}