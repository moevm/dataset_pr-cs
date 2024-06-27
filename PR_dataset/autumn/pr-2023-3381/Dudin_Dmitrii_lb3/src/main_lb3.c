#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char* read_stdin(int* output_len) {
    char* result = malloc(50), ending[18] = {0};
    if (!result) { perror("Unable to allocate memory!"); exit(1); }

    int len = 0, allocated_memory_size = 50;

    while (!(len >= 17 && strcmp(ending, "Dragon flew away!") == 0)) {
        result[len] = getchar();
        if (len >= 17) memcpy(ending, &result[len - 17], 17);
        if (++len == allocated_memory_size - 1) {
            char* new_ptr = realloc(result, allocated_memory_size + 50);
            if (new_ptr) { result = new_ptr; allocated_memory_size += 50; }
            else { perror("Unable to allocate memory!"); exit(1); }
        }
    }

    char* output = malloc(len);
    if (!output) { perror("Unable to allocate memory!"); exit(1); }

    memcpy(output, result, len);
    free(result);
    *output_len = len;
    return output;
}

int capital_letters_count(char* str) {
    int count = 0;
    for (int i = 0; i < strlen(str); i++)
        if (isupper(str[i])) count++;
    return count;
}

int main() {
    char* input;
    int input_len;
    input = read_stdin(&input_len);

    char* ptr_ending = &input[input_len];
    char* ptr_current = &input[0];

    char* sentence = malloc(50), * ptr_sentence = &sentence[0];
    int allocated_memory_size = 50, saved_sentences = 0, all_sentences = 0;

    while (ptr_current != ptr_ending) {
        if (*ptr_current == '\n') ptr_current++;
        else if ((*ptr_current == ' ' && ptr_sentence == sentence) || (*(ptr_sentence - 1) == ' ' && *ptr_current == ' ')) ptr_current++;
        else if (*ptr_current == '.' || *ptr_current == ';' || *ptr_current == '?') {
            int sentence_len = ptr_sentence - sentence;
            char* new_ptr_sentence = malloc(sentence_len + 2);
            if (!new_ptr_sentence) { perror("Unable to allocate memory!"); exit(1); }
            memcpy(new_ptr_sentence, sentence, sentence_len);
            new_ptr_sentence[sentence_len] = *(ptr_current++);
            new_ptr_sentence[sentence_len + 1] = '\0';

            int c = capital_letters_count(new_ptr_sentence);
            all_sentences++;
            if (c <= 1) { printf("%s\n", new_ptr_sentence); saved_sentences++; }

            free(sentence);
            sentence = malloc(50);
            if (!sentence) { perror("Unable to allocate memory!"); exit(1); }
            ptr_sentence = &sentence[0];
            allocated_memory_size = 50;
        } else {
            int sentence_len = ptr_sentence - sentence - 1;
            if (sentence_len == allocated_memory_size) {
                sentence = realloc(sentence, allocated_memory_size + 50);
                if (!sentence) { perror("Unable to allocate memory!"); exit(1); }
                ptr_sentence = &sentence[sentence_len + 1];
                allocated_memory_size += 50;
            }
            *(ptr_sentence++) = *(ptr_current++);
        }
    }

    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", all_sentences, saved_sentences);

    free(input);
    free(sentence);
    return 0;
}
