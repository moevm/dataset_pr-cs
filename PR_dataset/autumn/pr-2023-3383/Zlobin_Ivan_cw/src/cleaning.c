#include "cleaning.h"
void cleaning(struct Text *text){
    for(int i=0; i<text->num_of_sent; ++i){
        free(text->sentences[i]->str);
        free(text->sentences[i]);
    }
    free(text->sentences);
}
