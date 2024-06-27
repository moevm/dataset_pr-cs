#include <stdlib.h>
#include <wchar.h>
#include <wctype.h>
#include <stdio.h>
#include "sort_sentence.h"
#include "structures.h"
#include "check_cyrillic.h"
int sort_compare(const void* a, const void*b){
    const wchar_t *word1 = *(const wchar_t **)a;
    const wchar_t *word2 = *(const wchar_t **)b;

    int count1 = 0, count2 = 0;
    for (size_t i = 0; i<wcslen(word1); i++) {
        if ((word1[i] >= 'a' && word1[i] <= 'z') || (word1[i] >= 'A' && word1[i] <= 'Z')) {
            count1++;
        }
    }

    for (size_t i = 0;i<wcslen(word2); i++) {
        if ((word2[i] >= 'a' && word2[i] <= 'z') || (word2[i] >= 'A' && word2[i] <= 'Z')) {
            count2++;
        }
    }
    return count2-count1;
}
void sort_sentence(struct Text* text){
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
        qsort(split_sent, len_split_sent, sizeof(wchar_t*), sort_compare);
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




}