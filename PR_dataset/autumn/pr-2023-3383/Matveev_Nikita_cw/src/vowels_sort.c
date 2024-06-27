#include "vowels_sort.h"
#include "sort.h"
void vowels_sort(struct Text* start){
    int count = start->size;
    for (int i =0; i < count; i++){
        wchar_t* sent = wcsdup(start->sentences[i]);
        wchar_t* ptr;
        wchar_t* word;
        wchar_t** words = (wchar_t**)malloc(sizeof(wchar_t*));
        int mem =1;
        int len = 1;
        word = wcstok(sent, L",  .\n", &ptr);
        words[0] = wcsdup(word);
        while (word !=NULL){
            if (len +2>= mem){
                mem *= MEM_STEP;
                words = (wchar_t**)realloc(words, mem*sizeof(wchar_t*));
            }
            word = wcstok(NULL, L",  .\n", &ptr);
            if (word != NULL){
                words[len++] = wcsdup(word);
            }
        }

        qsort(words, len, sizeof(wchar_t*), v_comp);
        wchar_t* my_sentence = wcsdup(start->sentences[i]);
        int len_sent = 0;
        int sum_lens =0;
        int run =0;
        for (int j =0; j<len; j++){
            int len_word =wcslen(words[j]);
            if (len_sent == 0 || len_sent < sum_lens){
                for (int n =0; n<len_word; n++){
                    start->sentences[i][len_sent++] = words[j][n];
                }
                sum_lens += len_word;
            }
            else{
                while(my_sentence[run] != L' ' && my_sentence[run] != L',' && my_sentence[run] != L'\n'){
                    run++;
                }
                while(my_sentence[run] == L' ' || my_sentence[run] == L',' || my_sentence[run] == L'\n' ){
                    start->sentences[i][len_sent++] = my_sentence[run++];
                }
                for (int n =0; n<len_word; n++){
                    start->sentences[i][len_sent++] = words[j][n];
                }
                sum_lens += len_word;

            }
        }
        for (int j =0; j<len; j++){
            free(words[j]);
        }
        free(words);
        free(sent);
        free(my_sentence);
    }
}
