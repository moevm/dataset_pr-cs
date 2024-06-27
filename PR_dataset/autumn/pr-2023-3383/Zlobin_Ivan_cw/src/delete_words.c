#include "delete_words.h"
#include "len_of_word.h"

void del_words(struct Text *text){
    len_count(text);
    for(int i=0;i<text->num_of_sent; ++i){
        if(text->sentences[i]->cnt<2 || text->sentences[i]->cnt>5){
            free(text->sentences[i]->str);
            text->sentences[i]->str=NULL;
        }
    }
}
