#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <string.h>

#include "cmps.h"
#include "structures.h"


int check_repeats(wchar_t* cur_sent, struct Sentence **text, int sent_count) {
    for (int i = 0; i < sent_count; i++) {
        int f = 0;
        for (int j = 0; j < wcslen(cur_sent); j++) {
            if (towlower(cur_sent[j]) != towlower(text[i]->s[j])) {
                f = 1;
                break;
            }
        }
        if (f == 0) {
            return 0;
        }
    }
    return 1;
}

int mask_approved(wchar_t* sent, wchar_t* mask) {
    int star_len = 0;
    wchar_t delimiters[5] = L" ,.\t\n";
    wchar_t cur_sent[wcslen(sent)+1];
    wcscpy(cur_sent, sent);
    wchar_t* buffer;
    wchar_t* word = wcstok(cur_sent, delimiters, &buffer);
    while (word != NULL)
    {
        star_len = 0;
        if (wcschr(mask, L'*') != NULL) {
            if (wcslen(mask) <= wcslen(word))
                star_len = wcslen(word) - wcslen(mask);
            else
                star_len -= 1;
        }
        
        wint_t cur_wsymb = 0;
        wint_t cur_msymb = 0;
        if (wcslen(mask) != wcslen(word)-star_len) {
            return 0;
        }
        while (cur_wsymb < wcslen(word)) {
            if (mask[cur_msymb] == L'?') {
                cur_wsymb++;
                cur_msymb++;
                continue;
            }
            else if (mask[cur_msymb] == L'*')
            {
                cur_wsymb += star_len+1;
                cur_msymb++;
                continue;
            }
            else {
                if (mask[cur_msymb] == word[cur_wsymb]) {
                    cur_wsymb++;
                    cur_msymb++;
                    continue;
                }
                else {
                    return 0;
                }
            }
        }
        word = wcstok(NULL, delimiters, &buffer);
       // wprintf(L"%ls", word);
    }
    return 1;
}


void words_sort(wchar_t* sent) {
    wchar_t* sent_cp = malloc(sizeof(wchar_t)*(wcslen(sent)+1));
    memcpy(sent_cp, sent, (wcslen(sent)+1)*sizeof(wchar_t));
    wchar_t** words = malloc(sizeof(wchar_t*));
    if (words == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }

    int f = 0;
    int words_count = 0;
    wchar_t *buffer = NULL;
    wchar_t* word = wcstok(sent_cp, L" \t\n,.", &buffer);
    while (word != NULL) {
        words[words_count] = malloc(sizeof(wchar_t)*(wcslen(word)+1));
        wcscpy(words[words_count], word);
        words = realloc(words, sizeof(wchar_t*)*(++words_count+1));
        if (words == NULL) {
            fwprintf(stderr, L"Error: Ошибка выделения памяти");
            exit(0);
        }
        word = wcstok(NULL, L" \t\n,.", &buffer);
    }


    qsort(words, words_count, sizeof(wchar_t*), cmpw);
    wchar_t* sorted_sent = malloc(wcslen(sent)*sizeof(wchar_t));
    if (sorted_sent == NULL) {
        fwprintf(stderr, L"Error: Ошибка выделения памяти");
        exit(0);
    }
    int ss_index = 0;
    int words_index = 0;
    int let_index = 0;

    for(int i = 0; i < wcslen(sent); i++) {
        if (wcschr(L" \t\n,.", sent[i])) {
            f = 0;
            sorted_sent[ss_index++] = sent[i];
        }
        else if (f == 0) {
            f = 1;
            for (int j = 0; j < wcslen(words[words_index]); j++) {
                sorted_sent[ss_index++] = words[words_index][j];

            }
            words_index++;

        }
    }

    wcsncpy(sent, sorted_sent, wcslen(sent));
    
    for (int i = 0; i < words_count; i++)
        free(words[i]);
    free(words);
}

int delete_sent(wchar_t* sent) {
    wchar_t sent_cp[wcslen(sent)];
    wcscpy(sent_cp, sent);
    wchar_t* buffer;
    wchar_t* word = wcstok(sent_cp, L" ,.\n", &buffer);
    int words_count = 0;
    while (word != NULL)
    {
        words_count++;
        word = wcstok(NULL, L" ,.\n", &buffer);
    }

    if (words_count > 5 || words_count < 2)
        return 1;
    else
        return 0;
    
}