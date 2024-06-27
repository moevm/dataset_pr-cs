#include "palindromes.h"

bool check_no_words(Sentence *sentence){
    if (sentence->len == 0 || sentence->data[0]==L'.')
        return true;
    if (sentence->data[0] == L','){
        for(size_t i = 0; i<sentence->len;i++){
            if (!(wcschr(L", .",sentence->data[i])))
                return false;
        }
        return true;
    }
    return false;
}   

void print_palindrome_status(Sentence *sentence, bool all_palindromes, bool is_palindrome){
    if (all_palindromes)
        wprintf(L"%ls %ls\n", sentence->data, ALL);
    else{
        if (is_palindrome)
             wprintf(L"%ls %ls\n", sentence->data, SOME);
        else
             wprintf(L"%ls %ls\n", sentence->data, NO);
        }
}

void is_palindrome(Sentence *sentence){
    if (check_no_words(sentence))
        wprintf(L"%ls %ls\n", sentence->data, NO_WORDS);
    else{
        size_t len = sentence->len-1;
        bool all_palindromes = true;
        bool is_palindrome = false;
        bool cur_flag = true;
        wchar_t *str = (wchar_t*)malloc(sizeof(wchar_t)*(1+sentence->len));
        if (str == NULL)
            leave(MEM_ERROR);
        wcscpy(str, sentence->data);
        wchar_t *token, *state;
        for (token = wcstok(str, L" ,.",&state);
            token != NULL;
            token = wcstok(NULL, L" ,.", &state)){
                len = wcslen(token);
                for(size_t i = 0; i <=(len/2); i++){
                    if (token[i] != token[len-i-1]){
                        cur_flag = false;
                        break; 
                    }
                }
                if(cur_flag == true){
                    is_palindrome = true;
                }else{
                    all_palindromes=false;
                }
                cur_flag = true;
            }
        free(str);
        print_palindrome_status(sentence, all_palindromes, is_palindrome);
    }
}

void print_palindromes(Text *text){
    for(size_t i = 0; i<(text->len); i++){
        is_palindrome(text->data[i]);
    }
}
