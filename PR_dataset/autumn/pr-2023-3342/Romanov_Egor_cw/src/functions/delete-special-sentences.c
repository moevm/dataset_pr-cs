#include "../headers/delete-special-sentences.h"

int check_numbers(struct Sentence sentence){
    for (size_t i =0;i<sentence.quantity_of_symbols;i++){
        if (iswdigit(sentence.sentence[i])){
            return 1;
        }
    }
    return 0;
}

int check_special_symbols(struct Sentence sentence){
    for (size_t i =0; i<sentence.quantity_of_symbols;i++){
        if (sentence.sentence[i] == L'#' || sentence.sentence[i] == L'№'){
            return 1;
        }
    }
    return 0;
}

struct Text delete_special_sentences(struct Text text){
    text = return_reworked_text(text);
    struct Text new_text = {malloc(sizeof(struct Sentence)), 0};
    for (size_t i =0; i< text.quantity_of_sentences;i++){
        if (check_special_symbols(text.sentences[i])<= check_numbers(text.sentences[i])){
            new_text.sentences[new_text.quantity_of_sentences++] = text.sentences[i];
            new_text.sentences = realloc(new_text.sentences, sizeof(struct Sentence) *(new_text.quantity_of_sentences+1));
        }
    }
    return new_text;
}