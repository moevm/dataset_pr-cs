#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

#define INPUT_BUFFER_SIZE 100

void compile_regex(regex_t* compiled_regex, const char* pattern) {
    if (regcomp(compiled_regex, pattern, REG_EXTENDED)) {
        printf("Error compiling regular expression\n");
        exit(1);
    }
}

void process_input(regex_t* compiled_regex, regmatch_t* group_array, int max_groups) {
    char* input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
    char* end_signal = "Fin.";
    char current_char = ' ';
    int count = 1, index = 0;

    while (strcmp(input_buffer, end_signal) != 0) {
        current_char = getchar();
        if (current_char == '\n') {
            if (regexec(compiled_regex, input_buffer, max_groups, group_array, 0) == 0) {
                for (int i = group_array[1].rm_so; i < group_array[1].rm_eo; i++) {
                    printf("%c", input_buffer[i]);
                }
                printf(" - ");
                for (int i = group_array[2].rm_so; i < group_array[2].rm_eo; i++) {
                    printf("%c", input_buffer[i]);
                }
                printf("\n");
            }
            free(input_buffer);
            input_buffer = calloc(INPUT_BUFFER_SIZE, sizeof(char));
            count = 1, index = 0;
        } else {
            input_buffer[index] = current_char;
            if (index + 1 >= INPUT_BUFFER_SIZE * count) {
                input_buffer = realloc(input_buffer, INPUT_BUFFER_SIZE * (count + 1));
                count++;
            }
            index++;
        }
    }
}

int main() {
    char* regex_pattern = "([0-9a-zA-Z_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";
    int max_groups = 3;
    regex_t compiled_regex;
    regmatch_t group_array[max_groups];

    compile_regex(&compiled_regex, regex_pattern);
    process_input(&compiled_regex, group_array, max_groups);

    regfree(&compiled_regex);
    return 0;
}
