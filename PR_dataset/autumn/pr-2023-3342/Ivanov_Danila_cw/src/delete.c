#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>
#include <locale.h>
#include "delete.h"
#define TEXT_MAX_SIZE 100
#define NUMBER_OF_SENTENCES 10
#define END_OF_INPUT L"\n\n"
#include "structs.h"

// удаление пробельных символов в начале предложения
wchar_t* space(wchar_t* str){
    wchar_t* res = calloc(wcslen(str) + 1, sizeof(wchar_t));
    int start = 0;
    while (str[start] == '\t' || str[start] == ' ' || str[start] == '\n'){
        start++;
    }
    for (int i = 0; i < wcslen(str) - start; i++){
        res[i] = str[start + i];
    }
    res[wcslen(str) - start] = '\0';
    return res;
}

// сравнение предложений
int equal_sentences(wchar_t* str_first, wchar_t* str_second){
    int ind1 = 0;
    int ind2 = 0;
    if (wcslen(str_first) != wcslen(str_second))
        return 1;
    while (str_first[ind1] != L'\0' || str_second[ind2] != L'\0'){
        if (towlower(str_first[ind1]) != towlower(str_second[ind2]))
            return 1;
        ind1++;
        ind2++;
    }
    return 0;
}

// удаление повторяющихся предложений
struct Text delete_sentences(struct Text text){
    struct Text text_res;
    struct Sentence str, str_low;
    struct Sentence str_new, str_new_low;
    text_res.list_of_sentences = malloc(sizeof(struct Sentence));
    int index = 0;
    for (int i = 0; i < text.count_of_sentences; i++){
        str = text.list_of_sentences[i];
        int flag = 1;
        for (int x = 0; x < index; x++){
            str_new = text.list_of_sentences[x];
            if (equal_sentences(str.sentence, str_new.sentence) == 0){
                flag = 0;
                break;
            }
        }
        if (flag){
            text_res.list_of_sentences[index++] = str;
            text_res.list_of_sentences = realloc(text_res.list_of_sentences, (index + 1) * sizeof(struct Sentence));
        }
    }
    text_res.count_of_sentences = index;
    return text_res;
}