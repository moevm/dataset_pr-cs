#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <locale.h>
#include <wctype.h>

#include "change_text.h"
#include "structures.h"


wchar_t* mask_input(void) {
    int star_count = 0;
    wchar_t* mask = malloc(sizeof(wchar_t));
    if (mask == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }
    wchar_t cur_symb = getwchar();
    if (cur_symb == L'*')
        star_count++;
    int mask_len = 0;
    while (!iswspace(cur_symb))
    {
        mask[mask_len++] = cur_symb;
        mask = realloc(mask, sizeof(wchar_t)*(mask_len+1));
        if (mask == NULL) {
            fwprintf(stderr, L"Error: Ошибка выделения памяти");
            exit(0);
        }
        cur_symb = getwchar();
        if (cur_symb == L'*')
            star_count++;
        if (star_count > 1){
            fwprintf(stderr, L"Error: Слишком много *\n");
            exit(0);
        }
    }

    mask[mask_len] = '\0';
    return mask;
}

int text_input(struct Text* text) {
    text->t = (struct Sentence**)malloc(sizeof(struct Sentence*));
    text->t[0] = malloc(sizeof(struct Sentence));
    wchar_t* cur_sent = (wchar_t*)malloc(sizeof(wchar_t));
    if (text->t == NULL || text->t[0] == NULL || cur_sent == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }
    int sent_index = 0;
    wchar_t delims[5] = L",. \t\n";


    while (1) {
        wchar_t cur_symb = getwchar();
        wchar_t past_symb;

        while (iswspace(cur_symb) || cur_symb == L',' || cur_symb == L'.')
        {
            past_symb = cur_symb;
            cur_symb = getwchar();
            if (cur_symb == L'\n' && past_symb == L'\n')
                break;
        }

        if (cur_symb == L'\n' && past_symb == L'\n')
            break;
        int symb_index = 0;


        for (int i = 0; (cur_symb != L'.'); i++) {
            cur_sent[symb_index] = cur_symb;
            symb_index++;

            past_symb = cur_symb;
            cur_symb = getwchar();
            if (cur_symb == L'\n' && past_symb == L'\n')
                break;

            cur_sent = realloc(cur_sent, (symb_index+1)*sizeof(wchar_t));
            if (cur_sent == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        if (past_symb != L'\n') {
            if (cur_symb == L'.') 
                cur_sent[symb_index] = L'.';
            cur_sent = realloc(cur_sent, sizeof(wchar_t)*(++symb_index+1));
            cur_sent[symb_index] = L'\n';
            if (cur_sent == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        cur_sent = realloc(cur_sent, sizeof(wchar_t)*(++symb_index+1));
        cur_sent[symb_index] = L'\0';



        if (check_repeats(cur_sent, text->t, sent_index)) {
            text->t[sent_index]->s = cur_sent;
            sent_index++;
            text->t = realloc(text->t, (sent_index+1)*sizeof(struct Sentence*));
            text->t[sent_index] = malloc(sizeof(struct Sentence));
            if (text->t == NULL || text->t[sent_index] == NULL) {
                fwprintf(stderr, L"Error: Ошибка выделения памяти");
                exit(0);
            }
        }
        cur_sent = malloc(sizeof(wchar_t));
        if (cur_sent == NULL) {
            fwprintf(stderr, L"Error: Ошибка выделения памяти");
            exit(0);
        }
        if (cur_symb == L'\n')
            break;
    }
    free(cur_sent);
    return sent_index;
}