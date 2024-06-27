#include "data_processing.h"


int read_number(){
    int chosen_function = -1;
    wchar_t* number_input = malloc(sizeof(wchar_t) * 10);
    if (number_input == NULL){
        return_error(ERROR_MEMORY_ALLOCATION);
    }
    fgetws(number_input, 10, stdin);
    if (swscanf(number_input, L"%d", &chosen_function) != 1){
        return_error(ERROR_read_text);
    }
    free(number_input);
    return chosen_function;
}


void read_text(struct Text *text)
{
    size_t buffer_size = START_BUFFER_SIZE;
    wchar_t *buffer = (wchar_t *)malloc(buffer_size * sizeof(wchar_t));
    if (buffer == NULL)
    {
        return_error(ERROR_MEMORY_ALLOCATION);
    }
    wchar_t c;
    size_t text_length = 0;
    while (((c = getwchar()) != L'\n') || (text_length > 0 && buffer[text_length - 1] != L'\n'))
    {
        if (text_length == buffer_size - 1)
        {
            buffer_size *= 2;
            buffer = (wchar_t *)realloc(buffer, buffer_size * sizeof(wchar_t));
            if (buffer == NULL){
                return_error(ERROR_MEMORY_ALLOCATION);
            }
        }
        buffer[text_length] = c;
        text_length++;
    }
    buffer[text_length] = L'\0';

    text->input = buffer;
    text->length = text_length;
}


void read_sentences(struct Sentence **sentences_array, struct Text *text){
    size_t count = 0;
    size_t array_size = START_SENTENCES_COUNT;
    size_t sentence_buffer_len = START_BUFFER_SIZE;
    size_t sentences_count = 0;
    *sentences_array = (struct Sentence *)malloc(START_SENTENCES_COUNT * sizeof(struct Sentence));
    if(*sentences_array == NULL){
        return_error(ERROR_MEMORY_ALLOCATION);
    }
    wchar_t *sentence_buffer = (wchar_t *)malloc(START_BUFFER_SIZE * sizeof(wchar_t));
    if(sentence_buffer == NULL){
        return_error(ERROR_MEMORY_ALLOCATION);
    }
    for (size_t i = 0; i < text->length; i++)
    {
        if (sentences_count == array_size - 1)
        {
            array_size *= 2;
            *sentences_array = (struct Sentence *)realloc(*sentences_array, array_size * sizeof(struct Sentence));
            if(*sentences_array == NULL){
                return_error(ERROR_MEMORY_ALLOCATION);
            }
        }
        if (count == 0 && iswspace(text->input[i]))
        {
            continue;
        }
        sentence_buffer[count] = text->input[i];
        count++;
        if (count == sentence_buffer_len - 2)
        {
            sentence_buffer_len *= 2;
            sentence_buffer = (wchar_t *)realloc(sentence_buffer, sentence_buffer_len * sizeof(wchar_t));
            if(sentence_buffer == NULL){
                return_error(ERROR_MEMORY_ALLOCATION);
            }
        }
        if (text->input[i] == L'.')
        {
            sentence_buffer[count] = L'\0';
            if (!check_sentence_in_array(*sentences_array, sentences_count, sentence_buffer))
            {
                (*sentences_array)[sentences_count].sentence = (wchar_t *)malloc((count + 1) * sizeof(wchar_t));
                if((*sentences_array)[sentences_count].sentence == NULL){
                    return_error(ERROR_MEMORY_ALLOCATION);
                }
                wcscpy((*sentences_array)[sentences_count].sentence, sentence_buffer);
                sentences_count++;
            }
            count = 0;
        }
    }
    text->sentences_count = sentences_count;
    free(sentence_buffer);
}


void fill_the_structure(struct Sentence *sentences_array, size_t sentences_count)
{
    for (size_t i = 0; i < sentences_count; i++){
        size_t word_count_buffer = START_WORD_COUNT;
        sentences_array[i].words = (wchar_t **)malloc(word_count_buffer * sizeof(wchar_t *));
        if (sentences_array[i].words == NULL){
            return_error(ERROR_MEMORY_ALLOCATION);
        }
        size_t word_count = 0;
        size_t max_word_size = 0;
        wchar_t *sentence_for_token = wcsdup(sentences_array[i].sentence);
        wchar_t *empty;
        wchar_t *token = wcstok(sentence_for_token, L" ,.;:", &empty);
        while (token != NULL && word_count < word_count_buffer) {
            if (word_count == word_count_buffer){
                word_count_buffer *= 2;
                sentences_array[i].words = (wchar_t **)realloc(sentences_array[i].words, word_count_buffer * sizeof(wchar_t *));
                if (sentences_array[i].words == NULL){
                    return_error(ERROR_MEMORY_ALLOCATION);
                }
            }
            sentences_array[i].words[word_count] = malloc((wcslen(token) + 1) * sizeof(wchar_t));
            if (sentences_array[i].words[word_count] == NULL){
                return_error(ERROR_MEMORY_ALLOCATION);
            }
            if (word_count == 0){
                sentences_array[i].size_of_first_word = wcslen(token);
            }
            if (wcslen(token) > max_word_size){
                max_word_size = wcslen(token);
            }
            sentences_array[i].max_word_size = max_word_size;
            sentences_array[i].words[word_count] = wcsdup(token);
            word_count++;
            token = wcstok(NULL, L" ,.;:", &empty);
        }
        sentences_array[i].count_of_words = word_count;
    }
}


void clean_memory(struct Sentence *sentences_array, struct Text *text)
{
    for (size_t i = 0; i < text->sentences_count; i++)
    {
        free(sentences_array[i].sentence);
        for (size_t j = 0; j < sentences_array[i].count_of_words; j++)
        {
            free(sentences_array[i].words[j]);
        }
        free(sentences_array[i].words);
    }
    free(sentences_array);
    free(text->input);
}
