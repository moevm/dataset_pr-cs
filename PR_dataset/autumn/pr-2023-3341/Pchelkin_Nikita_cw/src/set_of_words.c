#include "set_of_words.h"
#include <stdio.h>

void set_of_words(struct Text* text){
    int is_present;
    for(int i = 0; i < text->size; i++){
        for(int j = 0; j < text->text[i].num_of_words; j++){
            is_present = 0;

            for(int k = 0; k < text->size; k++){
                for(int t = 0; t < text->text[k].num_of_words; t++){
                    if(!wcscasecmp(text->text[i].words[j], text->text[k].words[t]) && (i != k || j != t)){
                        is_present = 1;
                        break;
                    }
                }
                if(is_present) break;
            }
            if(!is_present){
                wprintf(L"%ls ", text->text[i].words[j]);
            }
        }
    }
    wprintf(L"\n");
}
