#include "change_text.h"

void change_text(struct Text* text, size_t word_first_length){
    for (int i = 0; i < text->quantity_of_sentences; ++i) {
        struct Sentence *current_sen = &text->sentences[i];
        for (int j = 0; j < current_sen->quantity_of_words; j++) {
            struct Word* curr_word = &text->sentences[i].words[j];
            if(curr_word->quantity_of_letters > word_first_length){
                wchar_t *new_str = malloc(sizeof(struct Word) * 16);
                wchar_t *string_default = L"(большое слово)";
                wcscpy(new_str, string_default);

                free(curr_word->letters);

                curr_word->letters = new_str;
            }
        }
    }
}

size_t get_word_length(){
    size_t num = 0;
    getwchar();

    wchar_t symbol = getwchar();
    while (symbol != L'\n'){
        num++;
        symbol = getwchar();
    }

    return num;
}