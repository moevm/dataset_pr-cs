#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define START_SENTENCE_SIZE 20
#define TEXT_SIZE_STEP 10
#define SENTENCE_SIZE_STEP 10


void free_all_memory(char **text, size_t text_size, size_t excluded_sentence) {
    for (size_t i = 0; i < text_size; i++) {
        if (i == excluded_sentence) continue;
        free(text[i]);
    }
    free(text);
}


char *expand_sentence(char *sentence, size_t *p_sentence_size) {
    size_t new_sentence_size = *p_sentence_size + SENTENCE_SIZE_STEP;
    char *temp = realloc(sentence, new_sentence_size * sizeof(char));

    if (temp == NULL) {
        free(sentence);
        return NULL;
    }

    *p_sentence_size = new_sentence_size;
    return temp;
}

char **expand_text(char **text, size_t *p_text_size) {
    size_t text_size = *p_text_size;
    size_t new_text_size = text_size + TEXT_SIZE_STEP;
    char **temp = realloc(text, new_text_size * sizeof(char **));

    if (temp == NULL) {
        for (size_t i = 0; i < text_size; i++) {
            free(text[i]);
        }
        free(text);
        return NULL;
    }

    for (size_t i = text_size; i < new_text_size; i++) {
        temp[i] = malloc(START_SENTENCE_SIZE * sizeof(char));
        if (temp[i] == NULL) {
            for (size_t j = 0; j < i; j++) {
                free(temp[j]);
            }
            free(temp);
            return NULL;
        }
    }

    *p_text_size = new_text_size;
    return temp;
}

char *add_char(char c, char *sentence, size_t *p_index, size_t *p_sentence_size) {
    if (*p_index + 2 > *p_sentence_size) {
        sentence = expand_sentence(sentence, p_sentence_size);
        if (sentence == NULL) {
            return NULL;
        }
    }
    sentence[*p_index] = c;
    (*p_index)++;
    return sentence;
}


int is_sentence_to_delete(char *sentence, size_t sentence_size) {
    char *string = malloc(sentence_size * sizeof(char));
    strcpy(string, sentence);
    int is_digit;
    size_t lexeme_size;
    int middle_digit, end_digit;
    for (char *lexeme = strtok (string," ,.;?!"); lexeme != NULL; lexeme = strtok(NULL, " ,.;?!")) {
        lexeme_size = strlen(lexeme);
        is_digit = 1;
        middle_digit = 0;
        for (size_t i = 0; i < lexeme_size; i++) {
            if (!isdigit(lexeme[i])) {
                is_digit = 0;
            } else if (middle_digit == 0 && 0 < i && i < (lexeme_size - 1)) {
                middle_digit = 1;
            }
        }

        if (is_digit) continue;

        end_digit = isdigit(lexeme[lexeme_size-1]);

        if (middle_digit && !end_digit) {
            return 1;
        }
    }
    return 0;
}


char **read_text(size_t *p_count_sentences_before, size_t *p_count_sentences_after) {
    char **text = malloc(0);

    size_t sentences_before = 0;
    size_t text_size = 0;
    size_t sentence_size = START_SENTENCE_SIZE;
    size_t sentence = 0;
    size_t index = 0;
    char c;
    do {
        if (sentence + 1 > text_size) {
            text = expand_text(text, &text_size);
            if (text == NULL) {
                return NULL;
            }
        }

        c = (char) getchar();
        if (c == '\n') c = ' ';
        if (isspace(c) && (index == 0 || isspace(text[sentence][index-1]))) continue;


        text[sentence] = add_char(c, text[sentence], &index, &sentence_size);
        if (text[sentence] == NULL) {
            free_all_memory(text, text_size, sentence);
            return NULL;
        }

        if (c == '.' || c == ';' || c == '?' || c == '!') {
            text[sentence] = add_char('\0', text[sentence], &index, &sentence_size);
            if (text[sentence] == NULL) {
                free_all_memory(text, text_size, sentence);
                return NULL;
            }

            sentences_before++;

            if (is_sentence_to_delete(text[sentence], sentence_size)) {
                free(text[sentence]);
                text[sentence] = malloc(START_SENTENCE_SIZE * sizeof(char));
                if (text[sentence] == NULL) {
                    free_all_memory(text, text_size, sentence);
                    return NULL;
                }
            } else {
                sentence++;
            }

            index = 0;
            sentence_size = START_SENTENCE_SIZE;
        }

    } while (c != '!');

    *p_count_sentences_before = sentences_before;
    *p_count_sentences_after = sentence;

    return text;
}


int main(void) {
    size_t *p_count_sentences_before = malloc(sizeof(size_t));
    size_t *p_count_sentences_after = malloc(sizeof(size_t));
    char **text = read_text(p_count_sentences_before, p_count_sentences_after);
    if (text == NULL) {
        fprintf(stderr, "ERROR: Memory allocation error!\n");
        free(text);
        free(p_count_sentences_before);
        free(p_count_sentences_after);
        return 1;
    }

    for (size_t i = 0; i < *p_count_sentences_after; i++) {
        for (size_t j = 0; text[i][j]; j++){
            printf("%c", text[i][j]);
        }
        printf("\n");
    }
    printf("Количество предложений до %zu и количество предложений после %zu\n", *p_count_sentences_before - 1, *p_count_sentences_after - 1);
    return 0;
}

