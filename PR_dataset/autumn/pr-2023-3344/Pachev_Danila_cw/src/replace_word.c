#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "structures.h"

wchar_t** split_sentence(const wchar_t* sentence, int* count) {
    // Выделение памяти под массив указателей на слова
    wchar_t** words = malloc(wcslen(sentence) * sizeof(wchar_t*));
    if (words == NULL) {
        wprintf(L"Ошибка выделения памяти!\n");
        *count = 0;
        return NULL;
    }

    int prev_index = 0; // Индекс начала текущего слова
    int word_count = 0; // Количество найденных слов

    // Проход по символам предложения
    for (int i = 0; sentence[i] != L'\0'; i++) {
        // Проверка, является ли текущий символ разделителем
        int is_separator =
            (sentence[i] == L' ' || sentence[i] == L',' || sentence[i] == L'.');

        // Если найден разделитель или достигнут конец строки, добавляем слово в массив
        if (is_separator || sentence[i+1] == L'\0') {
            // Выделение памяти под слово
            words[word_count] = malloc((i - prev_index + 2) * sizeof(wchar_t));
            if (words[word_count] == NULL) {
                wprintf(L"Ошибка выделения памяти!\n");
                *count = 0;
                return NULL;
            }

            // Копирование слова в массив
            wcsncpy(words[word_count], &sentence[prev_index], i - prev_index + 1);
            words[word_count][i - prev_index + 1] = L'\0'; // Добавление завершающего символа

            // Переход к следующему слову
            prev_index = i + 1;
            word_count++;
        }
    }

    *count = word_count;
    return words;
}

void replace_word(struct Text* text,wchar_t* input_word){
    wchar_t* word = input_word;
    int word_len = wcslen(word);
    for (size_t i = 0;i<text->len;i++){
        wchar_t* copy = wcsdup(text->text[i]->sentence);
            if (copy==NULL){
                wprintf(L"Error: failed to allocate memory for copy [function: sort_sentence]\n");
                exit(1);
            }
        size_t len_split_sent = 0;
            wchar_t* ptr;
        wchar_t* token = wcstok(copy, L", \n",&ptr);
        wchar_t** split_sent = malloc(sizeof(wchar_t*));
            if (split_sent==NULL){
                wprintf(L"Error: failed to allocate memory for split_sent [function: sort_sentence]\n");
                exit(1);
            }
        while (token!=NULL) {
            split_sent = realloc(split_sent,(sizeof(wchar_t*)*(1+len_split_sent)));
            if (split_sent==NULL){
                wprintf(L"Error: failed to reallocate memory for split_sent [function: sort_sentence]\n");
                exit(1);
            }
            split_sent[len_split_sent++] = wcsdup(token);
            if (split_sent[len_split_sent-1]==NULL){
                wprintf(L"Error: failed to allocate memory for split_sent[len_split_sent-1] [function: sort_sentence]\n");
                exit(1);
            }
            token = wcstok(NULL, L", \n",&ptr);
        }
        free(copy);
        for (size_t j = 0;j<len_split_sent;j++){
           if (j==len_split_sent-1){
                if (wcslen(split_sent[j])>word_len){
                    wprintf(L"(большое слово).\n");
               }
               else{
                wprintf(L"%ls.\n",split_sent[j]);
               }
           }
           else{
            if (wcslen(split_sent[j])>word_len){
                wprintf(L"(большое слово) ");
               }
            else{
                wprintf(L"%ls ",split_sent[j]);
            }
           }
    }
    }
    // for (size_t i = 0;i<text->len;i++){
    //     int count_len_word = 0;
    //     wchar_t* word_for_print = malloc(sizeof(wchar_t));
    //     for (size_t j = 0;j<wcslen(text->text[i]->sentence);j++){
    //         if (text->text[i]->sentence[j]==L' ' || text->text[i]->sentence[j]==L',' || text->text[i]->sentence[j]==L'\n' || text->text[i]->sentence[j]==L'\t'){
    //             if (text->text[i]->sentence[j-1]!=L' ' || text->text[i]->sentence[j-1]!=L',' || text->text[i]->sentence[j-1]!=L'\n' || text->text[i]->sentence[j-1]!=L'\t'){
    //                 word_for_print[count_len_word] = L'\0';
    //                 count_len_word = 0;
    //                 word_for_print = realloc(word_for_print,sizeof(wchar_t));
    //                 wprintf(L"%ls",word_for_print);
    //             }
    //             else{
    //                 count_len_word = 0;
    //                 word_for_print = realloc(word_for_print,sizeof(wchar_t));
    //                 wprintf(L"%lc",text->text[i]->sentence[j]);
    //             }

    //         }
    //         else{
    //             word_for_print = realloc(word_for_print,sizeof(wchar_t)*(count_len_word+2));
    //             word_for_print[count_len_word++] = text->text[i]->sentence[j];
    //         }
    //     }
    // }
}