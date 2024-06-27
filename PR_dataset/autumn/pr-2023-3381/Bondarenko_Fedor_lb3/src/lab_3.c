#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOCK_SIZE 10
#define END_OF_SENTENCES ".;?"

int is_the_end_of_sentence(char element);

void string_text(char** text, size_t* size) {

    char* string_text = (char*)malloc(*size * sizeof(char));
    size_t size_of_string_text = 0;
    char point = '.';

    for (size_t i = 0; (*text)[i]; i++) {
        if (is_the_end_of_sentence(point)) {
            if(!isspace((*text)[i])) {
                string_text[size_of_string_text++] = (*text)[i];
                point = (*text)[i];
            } else {
                point = '.';
            }
        } else {
            string_text[size_of_string_text++] = (*text)[i];
            point = (*text)[i];
        }
    }

    string_text[size_of_string_text] = '\0';
    free(*text);
    *text = string_text;
    *size = size_of_string_text;
}

void splitted_text(char** text, size_t* size, size_t count_of_sentences) {

    char* splitted_text = (char*)malloc((*size + count_of_sentences + 1) * sizeof(char));
    size_t size_of_splitted_text = 0;

    for (size_t i = 0; (*text)[i]; i++) {
        splitted_text[size_of_splitted_text++] = (*text)[i];
        if (is_the_end_of_sentence((*text)[i])) {
            splitted_text[size_of_splitted_text++] = '\n';
        }
    }
    
    splitted_text[size_of_splitted_text] = '\0';
    free(*text);
    *text = splitted_text;
    *size = size_of_splitted_text;
}

void formated_text(char** text, size_t* size, size_t count_of_sentences) {
    
    char* formated_text = (char*)malloc((*size + count_of_sentences + 1) * sizeof(char));
    size_t size_of_formated_text = 0;
    size_t start = 0;
    size_t stop = 0;

    for (size_t i = 0; (*text)[i]; i++) {
        if (is_the_end_of_sentence((*text)[i])) {
            start = stop;
            stop = i+1;

            if (start != 0) {
                for (size_t j = start+1; j < stop-1; j++) {
                    if ((*text)[j] == '5' && (*text)[j+1] == '5' && (*text)[j+2] == '5') {
                        if (isalnum((*text)[j-1]) == 0 && isalnum((*text)[j+3]) == 0) {
                            for (size_t k = start+1; k < stop+1; k++) {
                                (*text)[k] = -1;
                            }
                        }
                    }
                }
            } else {
                for (size_t j = start; j < stop-1; j++) {
                    if ((*text)[j] == '5' && (*text)[j+1] == '5' && (*text)[j+2] == '5') {
                        if (isalnum((*text)[j-1]) == 0 && isalnum((*text)[j+3]) == 0) {
                            for (size_t k = start; k < stop+1; k++) {
                                (*text)[k] = -1;
                            }
                        }
                    }
                }
            }
        }
    }

    for (size_t i = 0; (*text)[i]; i++) {
        if ((*text)[i] != -1) {
            formated_text[size_of_formated_text++] = (*text)[i];
        }
    }

    formated_text[size_of_formated_text] = '\0';
    free(*text);
    *text = formated_text;
    *size = size_of_formated_text;
}

int count_of_sentences(char** text) {

    int count = 0;
    for (size_t i = 0; (*text)[i]; i++) {
        if (is_the_end_of_sentence((*text)[i])) {
            count += 1;
        }
    }

    return count;
}

int is_the_end_of_sentence(char symbol) {

    for (size_t i = 0; END_OF_SENTENCES[i]; i++) {
        if (symbol == END_OF_SENTENCES[i]) {
            return 1;
        }
    }

    return 0;
}

int main() {
    
    size_t size = 0;
    size_t capacity = BLOCK_SIZE;
    char* text = (char*)malloc(capacity * sizeof(char));
    char ch = getchar();

    while (ch != '!') {
        text[size++] = ch;
        if (size == capacity - 1) {
            capacity += BLOCK_SIZE;
            text = (char*)realloc(text, capacity * sizeof(char));
            if (text == NULL) {
                break;
            }
        }

        ch = getchar();
    }

    text[size++] = '!';
    text[size] = '\0';

    string_text(&text, &size);
    size_t initional_count_of_sentences = count_of_sentences(&text);
    splitted_text(&text, &size, initional_count_of_sentences);
    formated_text(&text, &size, initional_count_of_sentences);
    size_t final_count_of_sentences = count_of_sentences(&text);
    printf("%s\n", text);
    printf("Количество предложений до %ld и количество предложений после %ld", initional_count_of_sentences, final_count_of_sentences);
    free(text);

    return 0;
}
