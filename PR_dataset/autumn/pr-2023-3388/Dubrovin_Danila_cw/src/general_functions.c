#include "general_functions.h"


void do_basic_processing(struct Sentence *sentences_array, size_t sentences_count)
{
    for(size_t i = 0; i < sentences_count; i++){
        wprintf(L"%ls\n", sentences_array[i].sentence);
    }
}


void convert_to_date(struct Sentence *sentences_array, size_t sentences_count)
{
    for(size_t i = 0; i < sentences_count; i++){
        wprintf(L"%02ld-%02ld-%02ld\n", sentences_array[i].count_of_words, sentences_array[i].max_word_size, sentences_array[i].count_of_words + 1900);
    }
}


void reverse_sentence(struct Sentence *sentences_array,size_t sentences_count){
    for(size_t i = 0; i < sentences_count; i++){
        for(size_t j = sentences_array[i].count_of_words - 1; j > 0; j--){
            wprintf(L"%ls ", sentences_array[i].words[j]);
        }
        wprintf(L"%ls.\n", sentences_array[i].words[0]);
    }
}


void sort_by_first_word(struct Sentence *sentences_array,size_t sentences_count)
{
    qsort(sentences_array, sentences_count, sizeof(struct Sentence), compare);
    for(size_t i = 0; i < sentences_count; i++){
        wprintf(L"%ls\n", sentences_array[i].sentence);
    }
}


void delete_short_words(struct Sentence *sentences_array,size_t sentences_count)
{
    for(size_t i = 0; i < sentences_count; i++){
        size_t flag = 0;  
        for(size_t j = 0; j < sentences_array[i].count_of_words; j++){
            if(wcslen(sentences_array[i].words[j]) > 3){
                flag = 1;
                break;
            }
        }
        if(flag){
            for(size_t j = 0; j < sentences_array[i].count_of_words - 1; j++){
                wprintf(L"%ls ", sentences_array[i].words[j]);
            }
            wprintf(L"%ls.\n", sentences_array[i].words[sentences_array[i].count_of_words - 1]);
        }
    }
}


void replace(struct Sentence *sentences_array,size_t sentences_count){
    wchar_t * big_word = L"(большое слово)";
    wchar_t * slovo = malloc(sizeof(wchar_t) * 10);
    swscanf(sentences_array[0].words[0] ,L"%ls\n", slovo);
    size_t big_word_len = wcslen(slovo);
    for (size_t i = 0; i < sentences_count; i++){
        wchar_t *sentence_for_token = wcsdup(sentences_array[i].sentence);
        wchar_t *empty;
        size_t counter = 0;
        wchar_t *token = wcstok(sentence_for_token, L" .", &empty);
        while (token != NULL) {
            if (counter == sentences_array[i].count_of_words - 1){
                if(token[wcslen(token) - 1] == L','){
                    if ((wcslen(token)-1) > big_word_len){
                        wprintf(L"%ls,", big_word);
                    }
                    else{
                        wprintf(L"%ls", token);
                    }
                }
                else{
                    if (wcslen(token) > big_word_len){
                        wprintf(L"%ls", big_word);
                    }
                    else{
                        wprintf(L"%ls", token);
                    }
                }
                break;
            }

            if(token[wcslen(token) - 1] == L','){
                if ((wcslen(token)-1) > big_word_len){
                    wprintf(L"%ls, ", big_word);
                }
                else{
                    wprintf(L"%ls ", token);
                }
            }
            else{
                if (wcslen(token) > big_word_len){
                    wprintf(L"%ls ", big_word);
                }
                else{
                    wprintf(L"%ls ", token);
                }
            }
            token = wcstok(NULL, L" .", &empty);
            counter++;
        }
        wprintf(L".\n");
    }
    wprintf(sentences_array[0].words[0]);
}
