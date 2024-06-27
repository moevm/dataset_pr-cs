#include "../include/print_words_count.h"
  
void print_words_count(Text text){
    int words_array_buffer = 1;
    Word* words_array = malloc(sizeof(Word));
    int words_array_size = 0;
    for (int i = 0; i < text.size; i++){
        Sentence current_sentence = text.sentences[i];
        wchar_t* tok_buffer = malloc(sizeof(wchar_t) * wcslen(current_sentence.chars));
        Word current_word;
        current_word.chars = wcstok(current_sentence.chars, L" .,", &tok_buffer);
        while (current_word.chars != NULL){
            int count_flag = 0;
            int word_index;
            for (int j = 0; j < words_array_size; j++){
                if (wcscmp(current_word.chars, words_array[j].chars) == 0){
                    count_flag = 1;
                    word_index = j;
                    break;
                }
            }
            if (words_array_size == words_array_buffer){
                words_array_buffer *= 2;
                words_array = realloc(words_array, sizeof(Word) * words_array_buffer);
            }
            if (count_flag){
                words_array[word_index].count++;
            } else{
                words_array[words_array_size].count = 1;
                words_array[words_array_size].chars = current_word.chars;
                words_array_size++;
            }
            current_word.chars = wcstok(NULL, L" .,", &tok_buffer);
        }
        free(tok_buffer);
    }
    for (int k = 0; k < words_array_size; k++){
        if (words_array[k].count >= 3){
            wprintf(L"%ls: %d\n", words_array[k].chars, words_array[k].count);
        }
    }
    wprintf(L"\n");
    free(words_array);
}
