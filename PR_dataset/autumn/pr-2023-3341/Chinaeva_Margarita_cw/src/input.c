#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
#include <locale.h>

#define STR_SIZE 100

#include "errors.h"
#include "structs.h"

enum error_list { OPTION_ERROR, END_DOT, VOID_STR, VOID_TEXT };

Sentence* input_sentence(int* check_error) {
    Sentence* new_sentence = (Sentence*)malloc(sizeof(Sentence));
    new_sentence->str = (wchar_t*)calloc(STR_SIZE, sizeof(wchar_t));
    new_sentence->size_str = 0;
    int check_input = 1;
    int count_bsn = 0;
    do {
        wchar_t new_symbol = getwchar();
        if ((new_sentence->size_str % STR_SIZE) == STR_SIZE - 2) {
            new_sentence->str = (wchar_t*)realloc(new_sentence->str, (new_sentence->size_str + STR_SIZE) * sizeof(wchar_t));
        } 
        if (new_symbol == L'\n') {
            count_bsn++;
        }
        else {
            count_bsn = 0;
        }
        if ((new_symbol == L' ' || new_symbol == L'\t' || new_symbol == L'\n') && new_sentence->size_str == 0 && count_bsn < 2) {
            continue; 
        }
        if (new_symbol == L'.' && new_sentence->size_str == 0) {
            error(VOID_STR); 
            check_input = 0;
            *check_error = 0;
        }
        if (count_bsn == 2 && new_sentence->size_str != 0) {
            error(END_DOT);
            check_input = 0;
            *check_error = 0; 
        }
        if (count_bsn == 2 && new_sentence->size_str == 0) {
            check_input = 0;
            new_sentence->str = NULL;
        }
        if (check_input == 1) {
            new_sentence->str[new_sentence->size_str] = new_symbol;
            new_sentence->size_str++;
            if (new_symbol == L'.') {
                check_input = 0;
            }
        }

    } while (check_input == 1);
    if (new_sentence->str != NULL) {
        new_sentence->str[new_sentence->size_str] = L'\0';
    }
    return new_sentence;
}

void input_text(Text* text) {
    int check_error = 1;
    int check_end = 1;
    text->size_text = 0;
    while (check_end != 0) {
        Sentence* check_input_sentence = input_sentence(&check_error);
        if (check_input_sentence->str == NULL && check_error == 1) {
            check_end = 0;
            if (text->size_text == 0) {
                error(VOID_TEXT);
            }
        }
        if (check_error == 0) {
            text->size_text = 0; //!!!!!!!!!!!!!!!!!!!!!!!
            check_end = 0;
        }
        if (check_input_sentence->str != NULL && check_error == 1) {
            int replay_check = 1;
            if (text->size_text) {
                for (int i = 0; i < text->size_text; i++) { 
                    if (wcscasecmp(text->sentences[i].str, check_input_sentence->str) == 0) { 
                        replay_check = 0; 
                    }
                }
            }
            if (replay_check && check_input_sentence != NULL) {
                text->size_text++;
                text->sentences[text->size_text - 1].str = (wchar_t*)malloc((check_input_sentence->size_str + 1) * sizeof(wchar_t));
                text->sentences = (Sentence*)realloc(text->sentences, text->size_text * sizeof(Sentence));
                text->sentences[text->size_text - 1] = *check_input_sentence;
            }
        }
    }
}

