#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define TERMINATING_CHAR '!'

#define EXTRA_SIZE 20

void format_text(char *input_text, int input_length) {
    int sentences_before = 0;
    int sentences_after = 0;
    int sentence_start_index = 0;
    int sentence_end_index = 0;
    int current_index;
    int is_word;
    int delete = 0;
    
    for (int i = 0; input_text[i] != '\0'; i++) {
        if (isspace(input_text[i]) && (input_text[i - 1] == '.' || input_text[i - 1] == ';' || input_text[i - 1] == '?')) {
            input_text[i] = '\n';
            sentence_start_index = i + 1;
            sentences_before += 1;
            sentences_after += 1;
        } else if (isdigit(input_text[i])) {
            if (isspace(input_text[i - 1]) || i == 0) {
                current_index = i;
                is_word = 0;
                while (!isspace(input_text[current_index])) {
                    if (isalpha(input_text[current_index])) {
                        is_word = 1;
                    }
                    current_index++;
                }
                if (is_word == 1) {
                    for (int g = i + 1; g < current_index - 1; g++) {
                        if (isdigit(input_text[g])) {
                            delete = 1;
                            break;
                        }
                    }
                } else {
                    i = current_index - 1;
                    continue;
                }
            } else if (!isspace(input_text[i + 1]) && input_text[i + 1] != '.' &&
                       input_text[i + 1] != ';' && input_text[i + 1] != '?' && input_text[i + 1] != ',') {
                delete = 1;
            }
            if (delete) {
                sentences_before += 1;
                sentence_end_index = sentence_start_index;
                int j = 0;
                do {
                    sentence_end_index += 1;
                    j++;
                } while (input_text[sentence_start_index + j] != '.' &&
                         input_text[sentence_start_index + j] != ';' && input_text[sentence_start_index + j] != '?');
                memmove(input_text + sentence_start_index, input_text + sentence_end_index + 2, input_length - sentence_start_index);
                i = sentence_start_index;
                delete = 0;
            }
            int is_word = 0;
        }
    }
    printf("%s\n", input_text);
    printf("Количество предложений до %d и количество предложений после %d\n", sentences_before, sentences_after);
}

void process_text() {
    int text_size = 100;
    int actual_Text_size = text_size;
    char *user_input = (char *) malloc(sizeof(char) * text_size);
    char *test_memory = user_input;
    int char_count = 0;
    char current_char;
    
    do {
        current_char = getchar();
        if (char_count >= actual_Text_size) {
            actual_Text_size += EXTRA_SIZE;
            test_memory = (char *) realloc(user_input, sizeof(char) * actual_Text_size);
            if (test_memory != NULL) {
                user_input = test_memory;
            } else {
                puts("Ошибка выделения памяти!");
                free(user_input);
                return;
            }
        }
        user_input[char_count] = current_char;
        char_count++;
    } while (current_char != TERMINATING_CHAR);
    user_input[char_count] = '\0';
    format_text(user_input, char_count);
    free(user_input);
}

int main() {
    process_text();
    return 0;
}