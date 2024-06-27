#include "supporting_functions.h"


void return_error(wchar_t *message)
{
    wprintf(message);
    exit(1);
}


int compare(const void *first_element, const void *second_element)
{
    const size_t first = ((const struct Sentence *)first_element)->size_of_first_word;
    const size_t second = ((const struct Sentence *)second_element)->size_of_first_word;
    if (first < second) {
        return -1;
    }
    if (first > second) {
        return 1;
    }
    return 0;
}


int check_sentence_in_array(struct Sentence *sentences_array, size_t sentences_count, wchar_t *sentence)
{
    for(size_t i = 0; i<sentences_count; i++){
        if(wcslen(sentences_array[i].sentence) == wcslen(sentence)){
            for (size_t j = 0; j < wcslen(sentence); j++){
                if(towlower(sentences_array[i].sentence[j]) != towlower(sentence[j])){
                    return 0;
                }
            }
            return 1;
        }
    }
    return 0;
}
