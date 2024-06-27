#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define COUNT_GROUPS 9
#define SITE_NAME_GROUP 3
#define FILE_NAME_GROUP 7
#define BUFFER_SIZE 1024
#define REGULAR_EXPRESSION "([A-z0-9]+[A-z0-9_]*:\\/\\/)?(www.)?(([A-z0-9]+[A-z0-9_]*\\.)+([A-z]+))\\/([A-z0-9_]+\\/)*([A-z0-9_]+\\.[A-z0-9_]+)"

char** input_and_divide_text(int* count_of_sentences) {
    char** sentences = (char**)calloc(BUFFER_SIZE, sizeof(char*));
    int buf = BUFFER_SIZE;
    char symbol;
    int symbol_counter = 0;
    int sentence_counter = 0;

    char* text = (char*)calloc(BUFFER_SIZE, sizeof(char));

    while (1) {
        symbol = getchar();
        if (symbol == '\n' && symbol_counter == 0) {
            continue;
        }
        text[symbol_counter++] = symbol;
        if (symbol_counter == buf - 1) {
            buf += BUFFER_SIZE;
            text = realloc(text, sizeof(char) * buf);
        }

        if (symbol == '\n') {
            text[symbol_counter - 1] = '\0';
            sentences[sentence_counter++] = strdup(text);
            symbol_counter = 0;
        }

        if (strstr(text, "Fin.")) {
            break;
        }
    }

    *count_of_sentences = sentence_counter;
    free(text);
    return sentences;
}

void found_url_and_print_results() {
    regex_t regex;
    regcomp(&regex, REGULAR_EXPRESSION, REG_EXTENDED);

    int count_of_sentences = 0;
    char** sentences = input_and_divide_text(&count_of_sentences);

    regmatch_t group[COUNT_GROUPS];

    for (int i = 0; i < count_of_sentences; i++) {
        if (regexec(&regex, sentences[i], COUNT_GROUPS, group, 0) == 0) {
            printf("%.*s - %.*s\n",
                (int)(group[SITE_NAME_GROUP].rm_eo - group[SITE_NAME_GROUP].rm_so), 
                sentences[i] + group[SITE_NAME_GROUP].rm_so,
                (int)(group[FILE_NAME_GROUP].rm_eo - group[FILE_NAME_GROUP].rm_so), 
                sentences[i] + group[FILE_NAME_GROUP].rm_so);
        }
    }
    regfree(&regex);

    free(sentences[0]);
    free(sentences);
}


int main() {
    found_url_and_print_results();
    return 0;
}