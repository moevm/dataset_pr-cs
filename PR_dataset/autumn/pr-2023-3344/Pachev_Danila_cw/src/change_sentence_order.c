#include "change_sentence_order.h"
#include "structures.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <wctype.h>
#include "check_cyrillic.h"
void reverse_array(wchar_t** arr, size_t start, size_t end) {
    wchar_t* temp;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void change_sentence_order(struct Text* text){
    for (size_t i = 0;i<text->len;i++){
        wchar_t* copy = wcsdup(text->text[i]->sentence);
        if (copy==NULL){
            wprintf(L"Error: failed to allocate memory for copy [function: change_sentence_order]\n");
            exit(1);
        }
        size_t len_split_sent = 0;
        wchar_t* ptr;
        wchar_t* token = wcstok(copy, L", \n",&ptr);
        wchar_t** split_sent = malloc(sizeof(wchar_t*));
        if (split_sent==NULL){
            wprintf(L"Error: failed to allocate memory for split_sent [function: change_sentence_order]\n");
            exit(1);
        }

        while (token!=NULL) {
            split_sent = realloc(split_sent,(sizeof(wchar_t*)*(1+len_split_sent)));
            if (split_sent==NULL){
                wprintf(L"Error: failed to reallocate memory for split_sent [function: change_sentence_order]\n");
                exit(1);
            }
            split_sent[len_split_sent++] = wcsdup(token);
            if (split_sent[len_split_sent-1]==NULL){
                wprintf(L"Error: failed to allocate memory for split_sent[len_split_sent-1] [function: change_sentence_order]\n");
                exit(1);
            }
            token = wcstok(NULL, L", \n",&ptr);
        }
        int is_all_cyrillic = check_cyrillic(split_sent, len_split_sent);
        if (is_all_cyrillic==1){
            free(copy);
            reverse_array(split_sent, 0, len_split_sent-1);
            for (size_t j = 0;j<len_split_sent;j++){
                if (j==len_split_sent-1){
                    wprintf(L"%ls.\n",split_sent[j]);
                }
                else{
                    wprintf(L"%ls ",split_sent[j]);
                }

                free(split_sent[j]);
            }
            free(split_sent);
        }
        else{
            for (size_t j = 0;j<len_split_sent;j++){
                free(split_sent[j]);
            }
            free(split_sent);
        }
    }
}