#include "delete_sentences.h"

void delete_sentences(struct Text* text){
    for(int i = 0; i < text->size; i++){
        if(wcschr(text->text[i].sentence, L'#')|| wcschr(text->text[i].sentence, L'№')){
            if(wcspbrk(text->text[i].sentence, L"0123456789")) wprintf(L"%ls\n", text->text[i].sentence);
        } else wprintf(L"%ls\n", text->text[i].sentence);
    }
}