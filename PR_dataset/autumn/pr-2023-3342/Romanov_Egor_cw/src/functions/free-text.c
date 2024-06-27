#include "../headers/free-text.h"

void free_text(struct Text text){
    for (size_t i=0;i<text.quantity_of_sentences;i++){
        // free_sentence(text.sentence);
        free(text.sentences[i].sentence);
        for (size_t y =0;y<text.sentences[i].quantity_of_words;y++){
            free(text.sentences[i].words[y].word);
        }
    }
    free(text.sentences);
}