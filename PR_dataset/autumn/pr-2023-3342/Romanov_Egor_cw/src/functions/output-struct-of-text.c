#include "../headers/output-struct-of-text.h"

void output(struct Text text){
    for (size_t i =0; i<text.quantity_of_sentences;i++){
        wprintf(L"%ls\n", text.sentences[i].sentence);
    }
}