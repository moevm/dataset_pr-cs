#include "../headers/split-sentences-on-words.h"

int check_symbol_to_skip(wchar_t symbol){
    const wchar_t skip_symbols[] = {L' ', L':', L'\n', L'\t', L',', L'.', L'-', L';'};
    for (size_t i =0; i<sizeof(skip_symbols)/sizeof(const wchar_t); i++){
        if (symbol == skip_symbols[i]){
            return 1;
        }
    }
    return 0;
}

void split_sentences_on_words(struct Text text){
    for (int i = 0; i < text.quantity_of_sentences; i++){

        struct Sentence current_str = text.sentences[i];
        wchar_t* word = calloc(wcslen(current_str.sentence), sizeof(wchar_t));
        int symbol_index = 0;

        for (int y = 0; y < wcslen(current_str.sentence); y++){
            if (check_symbol_to_skip(current_str.sentence[y])){
                if (symbol_index > 0){    
                    text.sentences[i].words[text.sentences[i].quantity_of_words++].word = word;
                    text.sentences[i].words = realloc(text.sentences[i].words, (text.sentences[i].quantity_of_words + 1) * sizeof(struct Word*));
                    word = calloc(wcslen(current_str.sentence)+1, sizeof(wchar_t));
                    symbol_index = 0;
                }
            }
            else{
                word[symbol_index++] = current_str.sentence[y];
            }
        }
    }
}