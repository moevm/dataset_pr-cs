#include "../headers/return-reworked-text.h"

int check_empty(struct Sentence researching_sentence){
    if (wcslen(researching_sentence.sentence) < 2 || (researching_sentence.sentence[0] == L'.')){
        return 0;
    }
    return 1;
}

int check_peer_of_sentences(struct Sentence first_sentence, struct Sentence second_sentence){
    if (first_sentence.quantity_of_symbols != second_sentence.quantity_of_symbols){
        return 0;
    }
    for (size_t i = 0; i< first_sentence.quantity_of_symbols;i++){
        if (towlower(first_sentence.sentence[i]) != towlower(second_sentence.sentence[i])){
            return 0;
        }
    }
    return 1;
}

struct Text remove_equial_sentences(struct Text old_text){
    struct Text new_text = {malloc(sizeof(struct Sentence)), 0};
    for (size_t i = 0; i<old_text.quantity_of_sentences;i++){
        int flag = 1;
        for (size_t y=0;y<new_text.quantity_of_sentences;y++){
            if (check_peer_of_sentences(old_text.sentences[i], old_text.sentences[y])){
                flag = 0;
                break;
            }
        }
        if (flag){
            new_text.sentences[new_text.quantity_of_sentences++] = old_text.sentences[i];
            new_text.sentences = realloc(new_text.sentences, sizeof(struct Sentence) * (new_text.quantity_of_sentences+1));

        }
    }
    return new_text;
}

struct Text return_reworked_text(struct Text old_text){
    struct Text new_text;
    new_text.sentences = malloc(sizeof(struct Sentence));
    new_text.quantity_of_sentences = 0;
    for (size_t i = 0; i<old_text.quantity_of_sentences;i++){
        if (check_empty(old_text.sentences[i])){
            new_text.sentences[new_text.quantity_of_sentences++] = old_text.sentences[i];
            new_text.sentences = realloc(new_text.sentences, sizeof(struct Sentence)*(new_text.quantity_of_sentences+1));
        }
    }
    new_text = remove_equial_sentences(new_text);
    return new_text;

}