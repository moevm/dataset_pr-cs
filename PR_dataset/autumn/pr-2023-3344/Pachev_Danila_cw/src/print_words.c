#include "print_words.h"
#include "structures.h"
#include <wchar.h>
#include <wctype.h>
#include <stdlib.h>
void print_words(struct Text* text){
    //wprintf(L"%d\n",text->count_all_words);
    wchar_t** words = malloc(sizeof(wchar_t*)*text->count_all_words); //массив для хранения слов
    if (words==NULL){
        wprintf(L"Error: failed to allocate memory for words [function: print_words]\n");
        exit(1);
    }
    size_t *counts = malloc((text->count_all_words)*sizeof(size_t));// массив для храния числа вхождений каждого слова в текст
    if (counts==NULL){
        wprintf(L"Error: failed to allocate memory for counts [function: print_words]\n");
        exit(1);
    }
    size_t num_words = 0; //для индексов массивов


    for (size_t j = 0; j < text->len; j++) {
        wchar_t* ptr;
        wchar_t* copy = wcsdup(text->text[j]->sentence);
        if (copy==NULL){
            wprintf(L"Error: failed to allocate memory for copy [function: print_words]\n");
            exit(1);
        }
        size_t words_count = 0;
        wchar_t* token = wcstok(copy, L", \n", &ptr);
        wchar_t** split_sent = malloc(sizeof(wchar_t*));
        if (split_sent==NULL){
            wprintf(L"Error: failed to allocate memory for split_sent [function: print_words]\n");
            exit(1);
        }

        while (token) {
            split_sent = realloc(split_sent,(sizeof(wchar_t*)*(1+words_count)));
            if (split_sent==NULL){
                wprintf(L"Error: failed to reallocate memory for split_sent [function: print_words]\n");
                exit(1);
            }
            split_sent[words_count++] = wcsdup(token);
            if (split_sent[words_count-1]==NULL){
                wprintf(L"Error: failed to allocate memory for split_sent[words_count-1] [function: print_words]\n");
                exit(1);
            }
            token = wcstok(NULL, L", \n", &ptr);
        }
        free(copy);


        for (size_t i = 0;i<words_count;i++){
            int flag = 0;
            size_t k;
            for (k = 0;k<num_words;k++){
                if (wcscmp(split_sent[i], words[k])==0){
                    flag = 1;
                    break;
                }
            }
            if (flag!=1){
                words[k]=wcsdup(split_sent[i]);
                if (words[k]==NULL){
                    wprintf(L"Error: failed to allocate memory for words[] [function: print_words]\n");
                    exit(1);
                }
                free(split_sent[i]);
                counts[k]=1;
                num_words++;
            }
            else{
                counts[k]++;
            }

        }
        free(split_sent);

    }
    int count_flag = 0;
    for (size_t i = 0; i < num_words; i++) {
        if (counts[i]>=3){
            count_flag = 1;
            wprintf(L"Количество вхождений слова '%ls' в текст: %ld\n", words[i], counts[i]);
        }
        free(words[i]);
    }
    if (count_flag==0){
        wprintf(L"Error: Не найдено слов, которые встречаются больше 3 раз в тексте\n");
    }
    free(counts);
    free(words);

}