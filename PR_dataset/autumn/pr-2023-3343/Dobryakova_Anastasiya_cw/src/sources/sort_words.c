#include "../include/sort_words.h"

int compare(const void* a, const void* b){
    const Word* first = (const Word*)a;
    const Word* second = (const Word*)b;
    return (second->letters_count - first->letters_count);
}

Text sort_words(Text text){
    for (int i = 0; i < text.size; i++){
        Sentence current_sentence = text.sentences[i];
        wchar_t* tok_buffer = malloc(sizeof(wchar_t) * (current_sentence.size + 10));
        Word current_word;
        int words_array_buffer = 1;
        Word* words_array = malloc(sizeof(Word) * 2);
        int words_array_size = 0;
        current_word.chars = wcstok(current_sentence.chars, L" .,", &tok_buffer);
        while (current_word.chars != NULL){
            current_word.letters_count = 0;
            for (int k = 0; k < wcslen(current_word.chars); k++){
                if ((current_word.chars[k] >= L'A' && current_word.chars[k] <= L'Z') || (current_word.chars[k] >= L'a' && current_word.chars[k] <= L'z')){
                    current_word.letters_count++;
                }
            }
            if (words_array_size == words_array_buffer){
                words_array_buffer *= 2;
                words_array = realloc(words_array, sizeof(Word) * (words_array_buffer + 10));
            }
            words_array[words_array_size] = current_word;
            words_array_size++;
            current_word.chars = wcstok(NULL, L" .,", &tok_buffer);
        }
        qsort(words_array, words_array_size, sizeof(Word), compare);
        wchar_t* current_str = malloc(sizeof(wchar_t) * (current_sentence.size + 10));
        current_str[0] = L'\0';
        for (int u = 0; u < words_array_size; u++){
            wcscat(current_str, words_array[u].chars);
            wcscat(current_str, L" ");
        }
        current_str[wcslen(current_str) - 1] = L'.';
        text.sentences[i].chars = current_str;
        free(words_array);
        free(tok_buffer);
    }
    return text;
}
