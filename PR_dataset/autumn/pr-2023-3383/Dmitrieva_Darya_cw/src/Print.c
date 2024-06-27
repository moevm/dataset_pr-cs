#include "structs.h"
#include "Print.h"

void printText(struct Text txt){
    for (size_t i = 0; i < txt.n; i++) {
        struct Sentence* current_sentence = txt.sents[i];
        for (size_t j = 0; j < current_sentence->size; j++)
            putwc(current_sentence->str[j], stdout);
        putwc(L'\n', stdout);
    }
}
