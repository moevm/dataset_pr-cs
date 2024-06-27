#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define END_OF_STRING '\0'
#define INVALID_WORD "555"

int is_valid(char* sentence) {
    int len = sizeof(sentence);
    char * token = strtok(sentence, " .,!?;");
    while( token != NULL ) {
        if (strcmp(token, INVALID_WORD)==0){
            return 0;
        }
        token = strtok(NULL, " .,!?;");
    }
    return 1;
}

char* read_sentence() {
    char* curr_sentence_ptr = malloc(16);
    int curr_buffer_size = 16;
    int curr_sentence_len = 0;
    while (curr_sentence_len <= curr_buffer_size){
        char c = getchar();
        if ((c == ' ' || c == '\t') && curr_sentence_len == 0){
            continue;
        }
        curr_sentence_ptr[curr_sentence_len++] = c;
        if (curr_sentence_len == curr_buffer_size - 1){
            curr_buffer_size += 16;
            curr_sentence_ptr = realloc(curr_sentence_ptr, curr_buffer_size);
        }
        if (c == '.' || c == ';' || c == '?' || c == '!'){
            curr_sentence_ptr[curr_sentence_len] = END_OF_STRING;
            curr_sentence_ptr = realloc(curr_sentence_ptr, curr_sentence_len+1);
            return curr_sentence_ptr;
        }
    }
}

char** read_text(int *size_of_text, int *invalid_counter) {
    char* curr_sentence;
    char* curr_sentence_copy;
    char** text = malloc(16 * sizeof(char*));
    int curr_sentences_counter = 0;
    int curr_text_buffer_size = 16;
    while (curr_sentences_counter <= curr_text_buffer_size){
        curr_sentence = read_sentence();
        curr_sentence_copy = malloc(strlen(curr_sentence)+1);
        strcpy(curr_sentence_copy, curr_sentence);
        if (!is_valid(curr_sentence_copy)){
            (*invalid_counter)++;
            continue;
        }
        if (curr_sentences_counter == curr_text_buffer_size - 1){
            curr_text_buffer_size += 16;
            text = realloc(text, curr_text_buffer_size * sizeof(char*));
        }
        if (strcmp(curr_sentence, "Dragon flew away!") != 0){
            text[curr_sentences_counter++] = curr_sentence;
        }
        else{
            text[curr_sentences_counter++] = curr_sentence;
            text = realloc(text, (curr_sentences_counter+1)*sizeof(char*));
            *size_of_text = curr_sentences_counter;
            return text;
        }
    }
}

int main() {
    int size_of_text = 0;
    int invalid_counter = 0;
    char** text_ptr = read_text(&size_of_text, &invalid_counter);
    for (int i = 0; i < (size_of_text); i++){
        printf("%s\n", text_ptr[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", size_of_text+invalid_counter-1, size_of_text-1);
}
