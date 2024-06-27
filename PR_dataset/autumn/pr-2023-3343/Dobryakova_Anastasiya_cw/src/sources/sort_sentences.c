#include "../include/sort_sentences.h"

Text sort_sentences(Text text) {
    for (int i = 0; i < text.size; i++) {
        Sentence current_sentence = text.sentences[i];
        int flag = 1;
        for (int k = 0; k < current_sentence.size; k++) {
            wchar_t* sentence = current_sentence.chars;
            if (!((sentence[k] >= L'А' && sentence[k] <= L'Я') || (sentence[k] >= L'а' && sentence[k] <= L'я') || (wcschr(L" .,", sentence[k]) != NULL))) {
                flag = 0;
                break;
            }
        }
    if (flag) {
        wchar_t* tok_buffer = malloc(sizeof(wchar_t) * (wcslen(current_sentence.chars) + 10));
        Word current_word;
        int words_array_buffer = 1;
        Word* words_array = malloc(sizeof(Word) * 2);
        int words_array_size = 0;
        current_word.chars = wcstok(current_sentence.chars, L" .,", &tok_buffer);
        while (current_word.chars != NULL) {
            if (words_array_size == words_array_buffer) {
                words_array_buffer *= 2;
                words_array = realloc(words_array, sizeof(Word) * words_array_buffer);
            }
            words_array[words_array_size] = current_word;
            words_array_size++;
            current_word.chars = wcstok(NULL, L" .,", &tok_buffer);
        }
        Word* reverse_words_array = malloc(sizeof(Word) * words_array_size);
        for (int j = words_array_size - 1; j >= 0; j--) {
            reverse_words_array[words_array_size - j - 1] = words_array[j];
        }
        wchar_t* current_str = malloc(sizeof(wchar_t) * (current_sentence.size + 10));
        current_str[0] = L'\0';
        for (int u = 0; u < words_array_size; u++) {
            wcscat(current_str, reverse_words_array[u].chars);
            wcscat(current_str, L" ");
        }
        current_str[wcslen(current_str) - 1] = L'.';
        text.sentences[i].chars = current_str;
        free(tok_buffer);
        free(words_array);
        free(reverse_words_array);
        }
    }
    return text;
}
