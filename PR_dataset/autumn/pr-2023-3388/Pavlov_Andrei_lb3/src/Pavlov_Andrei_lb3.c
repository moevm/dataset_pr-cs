#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#define START_SENTENCE_LEN 2

void init_sentences(char*** sentences, size_t** max_size, size_t** num_of_char) {
    for (size_t i = 0; i < START_SENTENCE_LEN; i++) {
        (*sentences)[i] = malloc(sizeof(char) * START_SENTENCE_LEN);
        memset((*sentences)[i], 0, START_SENTENCE_LEN);
        (*max_size)[i] = START_SENTENCE_LEN;
        (*num_of_char)[i] = 0;
    }
}

void realloc_sentences(char*** sentences, size_t** max_size, size_t** num_of_char, size_t aoss) {
    (*sentences) = realloc((*sentences), 2*aoss*sizeof(char*));
    (*num_of_char) = realloc((*num_of_char), 2*aoss*sizeof(size_t));
    *max_size = realloc(*max_size, 2*aoss*sizeof(size_t));

    for (size_t i = aoss; i < aoss*2; i++) {
        (*sentences)[i] = malloc(sizeof(char) * START_SENTENCE_LEN);
        memset((*sentences)[i], 0, START_SENTENCE_LEN);
        (*max_size)[i] = START_SENTENCE_LEN;
        (*num_of_char)[i] = 0;
    }
}

void realloc_one_sentence(char*** sentences, size_t* current_sentence, size_t** max_size, size_t smax) {
    (*sentences)[(*current_sentence)] = realloc((*sentences)[(*current_sentence)], 2*smax*sizeof(char));
    memset((*sentences)[(*current_sentence)]+smax, 0, smax);
    (*max_size)[(*current_sentence)] *= 2;
    smax *= 2;
}

void read_text(char*** sentences, size_t* current_sentence, size_t** num_of_char) {
    size_t aoss = START_SENTENCE_LEN;
    (*sentences) = malloc(sizeof(char*) * aoss);
    (*num_of_char) = malloc(sizeof(size_t) * aoss);
    size_t* max_size = malloc(sizeof(size_t) * aoss);

    init_sentences(sentences, &max_size, num_of_char);

    (*current_sentence) = 0;
    char input = getchar();

    while (true) {
        if ((*current_sentence) == aoss) {
            realloc_sentences(sentences, &max_size, num_of_char, aoss);
            aoss *= 2;
        }

        size_t snum = (*num_of_char)[(*current_sentence)];
        size_t smax = max_size[(*current_sentence)];

        if (snum == smax)
            realloc_one_sentence(sentences, current_sentence, &max_size, smax);

        (*sentences)[(*current_sentence)][snum] = input;
        (*num_of_char)[(*current_sentence)] += 1;

        if ((input == '.') || (input == ';') || (input == '?')) {
            (*current_sentence) += 1;
            input = getchar();
            input = getchar();
            continue;
        }

        if (input == '!') break;

        input = getchar();
    }

    (*current_sentence) += 1;
}

void delete_tabs(char** sentence, size_t* length) {
    bool* mask = malloc(sizeof(bool) * (*length) + 1);
    memset(mask, 1, *length);

    size_t new_length = *length;
    for (size_t i = 0; i < *length; i++) {
        char current = (*sentence)[i];
        if ((current == '\t')) {
            mask[i] = 0;
            new_length -= 1;
        } else if (current == '\n') {
            mask[i] = 0;
            mask[i+1] = 0;
            new_length -= 1;
        }
    }

    char* new_ptr = malloc(sizeof(char) * new_length + 1);
    size_t j = 0;
    for (size_t i = 0; i < *length; i++) {
        if (mask[i]) {
            new_ptr[j] = (*sentence)[i];
            j += 1;
        }
    }
    new_ptr[j] = 0;

    (*length) = new_length;
    (*sentence) = new_ptr;
}

void strip(char** sentence, size_t* length) {
    size_t start_index = 0;
    while ((*sentence)[start_index] == ' ') start_index++;

    char* new_ptr = malloc(sizeof(char) * (*length - start_index) + 1);
    for (size_t j = start_index; j < *length; j++)
        new_ptr[j-start_index] = (*sentence)[j];
    
    new_ptr[(*length - start_index)] = 0;

    (*length) -= start_index;
    (*sentence) = new_ptr;
}

bool have_one_capital(char* sentence, size_t length) {
    int capitals_count = 0;
    for (size_t i = 0; i < length; i++) {
        if ((sentence[i] >= 'A') && (sentence[i] <= 'Z')) capitals_count += 1;
        if (capitals_count > 1) return false;
    }
    return true;
}

int main() {
    char** sentences = 0;
    size_t* num_of_char = 0;
    size_t text_len = 0;

    read_text(&sentences, &text_len, &num_of_char);

    size_t deleted = 1;
    for (size_t i = 0; i < text_len; i++) {
        delete_tabs(&(sentences[i]), &(num_of_char[i]));
        strip(&(sentences[i]), &(num_of_char[i]));

        if (have_one_capital(sentences[i], num_of_char[i]))
            printf("%s\n", sentences[i]);
        else deleted += 1;
    }

    printf("Количество предложений до %ld и количество предложений после %ld\n", text_len-1, text_len-deleted);
}
