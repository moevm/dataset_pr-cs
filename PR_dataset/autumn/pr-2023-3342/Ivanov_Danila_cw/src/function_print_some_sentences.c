#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "reading.h"
#include "delete.h"
#include "memory.h"
#include "function_sum_of_minutes.h"
#include "function_sort.h"
#include "function_of_replace_symbols.h"
#include "function_of_delete_sentences.h"
#include "reference.h"
#include "structs.h"

wchar_t** massive(wchar_t* str, int* ptr_lent){
    wchar_t** words = malloc(sizeof(wchar_t*));
    wchar_t* word = calloc(wcslen(str), sizeof(wchar_t));
    int index = 0;
    int len = 0;
    for (int x = 0; x < wcslen(str); x++){
        if (str[x] == L' '){
            if (index > 0){
                words[len++] = word;
                word = calloc(wcslen(str), sizeof(wchar_t));
                index = 0;
                words = realloc(words, (len + 1) * sizeof(wchar_t*));
            }
        }
        else{
            word[index++] = str[x];
        }
    }
    words[len++] = word;
    *ptr_lent = len;
    return words;
}

struct Text func_print_some_sentences(struct Text text, wchar_t** mas, int* ptr_lent){
    struct Text text_res;
    struct Sentence str, str_low;
    struct Sentence str_0, str_0_low;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    int flag = 0;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        flag = 0;
        for (int x = 0; x < str.count_of_words; x++){
            wchar_t* w1 = str.list_of_words[x];
            int f = 0;
            for (int y = 0; y < (*ptr_lent); y++){
                wchar_t* w2 = mas[y];
                if (equal_sentences(w1, w2) == 0){
                    f = 1;
                    break;
                }
            }
            if (f == 0){
                flag = 1;
                break;
            }
        }
        if (flag == 0){
            text_res.list_of_sentences[index++] = str;
            text_res.list_of_sentences = realloc(text_res.list_of_sentences, (index + 1) * sizeof(struct Sentence));
        }
    }
    text_res.count_of_sentences = index;
    return text_res;
}

wchar_t* input_of_ninth_function(wchar_t* first_str){
    getwchar();
    wchar_t c = getwchar();
    int ind = 0;
    while (c != L'\n')
    {
        first_str[ind++] = c;
        first_str = realloc(first_str, (ind + 1) * sizeof(wchar_t));
        c = getwchar();
    }
    first_str[ind++] = L'\0';
    return first_str;
}