#include "get_unique_words.h"

void get_unique_words(struct Text text){
    size_t quantity_of_elements = 0;
    struct Unique_Word* result = NULL;

    //Составление списка уникальных слов
    for (int i = 0; i < text.quantity_of_sentences; i++) {
        struct Sentence *current_sen  = &text.sentences[i];
        for (int j = 0; j < current_sen->quantity_of_words; j++) {
            struct Word *current_word = &current_sen->words[j];
            size_t len_of_str = current_word->quantity_of_letters;

            result = realloc(result, (quantity_of_elements + 1) * sizeof(struct Unique_Word));
            if(result == NULL){
                wprintf(L"Error: Ошибка выделения памяти");
                exit(1);
            }

            wchar_t* new_word = malloc((len_of_str+1) * sizeof(wchar_t));
            wcsncpy(new_word, current_word->letters, len_of_str + 1);
            new_word[len_of_str] = '\0';

            if(quantity_of_elements != 0){
                if(check_similar_word(result, quantity_of_elements, new_word)){
                    free(new_word);
                    continue;
                }
            }

            result[quantity_of_elements] = create_unique_word(new_word);
            quantity_of_elements++;
        }
    }

    //Подсчет уникальных слов
    for (int i = 0; i < text.quantity_of_sentences; i++) {
        struct Sentence *current_sen  = &text.sentences[i];

        for (int j = 0; j < current_sen->quantity_of_words; j++) {
            struct Word *current_word = &current_sen->words[j];
            size_t len_of_str = current_word->quantity_of_letters;

            wchar_t* tmp_word = malloc((len_of_str + 1) * sizeof(wchar_t));
            wcsncpy(tmp_word, current_word->letters, len_of_str + 1);
            tmp_word[len_of_str] = '\0';

            for (int k = 0; k < quantity_of_elements; k++) {
                if(wcscmp(result[k].letters, tmp_word) == 0){
                    result[k].word_count++;
                }
            }

            free(tmp_word);
        }
    }
    //Вывод
    for(int i = 0; i < quantity_of_elements; i++){
        if(result[i].word_count >= 3){
            wprintf(L"%ls: %ld\n", result[i].letters, result[i].word_count);
        }
    }
    //Освобождение памяти
    for (int i = 0; i < quantity_of_elements; ++i) {
        free(result[i].letters);
    }
    free(result);
}
int check_similar_word(struct Unique_Word* list, size_t list_len, wchar_t *word){
    int is_similar = 0;

    for (int i = 0; i < list_len; ++i) {
        if(wcscmp(list[i].letters, word) == 0){
            is_similar = 1;
        }
    }

    return is_similar;
}