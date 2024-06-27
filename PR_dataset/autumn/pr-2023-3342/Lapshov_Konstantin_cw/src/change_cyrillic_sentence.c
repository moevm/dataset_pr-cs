#include "change_cyrillic_sentence.h"

void change_sentence(struct Text *text){
    for (int i = 0; i < text->quantity_of_sentences; i++) {
        if(!quantity_of_latin(text->sentences[i])){
            struct Sentence *curr_sen = &text->sentences[i];
            for (int j = 0; j < curr_sen->quantity_of_words/2 ; j++) {
                struct Word tmp = curr_sen->words[j];
                struct Word opposite_tmp = curr_sen->words[curr_sen->quantity_of_words - j - 1];

                curr_sen->words[j].letters = opposite_tmp.letters;
                curr_sen->words[curr_sen->quantity_of_words - j - 1].letters = tmp.letters;
            }
        }
    }
}
