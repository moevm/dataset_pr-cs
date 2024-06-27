#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REG "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# (.+)"
#define TEXT_STEP 10
#define COMMAND_STEP 20


void free_text(char **text, size_t length) {
    for (size_t i = 0; i < length; i++) {
        free(text[i]);
    }
    free(text);
}

char *read_command() {
    size_t length = 0;
    size_t size = COMMAND_STEP;
    char *command = (char *) malloc(size * sizeof(char));
    if (!command) {
        return NULL;
    }

    char ch;
    while ((ch = (char) getchar())) {
        if (ch == '\n' || ch == EOF) break;
        if (length + 1 > size) {
            size_t new_size = size + COMMAND_STEP;
            char *temp = (char *) realloc(command, new_size * sizeof(char));
            if (!temp) {
                free(command);
                return NULL;
            }
            command = temp;
            size = new_size;
        }
        command[length++] = ch;
    }
    command[length] = '\0';

    return command;
}

char **read_text(size_t *p_length) {
    size_t length = 0;
    size_t size = TEXT_STEP;
    char **text = (char **) malloc(size * sizeof(char *));
    if (!text) {
        return NULL;
    }

    do {
        if (length + 1 > size) {
            size_t new_size = size + TEXT_STEP;
            char **temp = (char **) realloc(text, new_size * sizeof(char *));
            if (!temp) {
                free_text(text, length);
                return NULL;
            }
            text = temp;
            size = new_size;
        }
        char *new_command = read_command();
        if (!new_command) {
            free_text(text, length);
            return NULL;
        }
        text[length++] = new_command;
    } while (strcmp(text[length - 1], "Fin.") != 0);

    *p_length = length;

    return text;
}

int main(void) {
    size_t text_length = 0;
    char **text = read_text(&text_length);
    if (!text) {
        fprintf(stderr, "\x1b[31mERROR: Memory allocation error.\x1b[0m\n");
        return 1;
    }

    regex_t reg;

    if (regcomp(&reg, REG, REG_EXTENDED)) {
        free_text(text, text_length);
        fprintf(stderr, "\x1b[31mERROR: Regular expression compilation error.\x1b[0m\n");
        return 1;
    }

    for (size_t i = 0; i < text_length; i++) {
        const size_t nmatch = 3;
        regmatch_t pmatch[nmatch];
        if (regexec(&reg, text[i], nmatch, pmatch, 0) == 0) {
            for (int j = pmatch[1].rm_so; j < pmatch[1].rm_eo; j++) {
                printf("%c", text[i][j]);
            }
            printf(" - ");
            for (int j = pmatch[2].rm_so; j < pmatch[2].rm_eo; j++) {
                printf("%c", text[i][j]);
            }
            printf("\n");
        }
    }

    regfree(&reg);
    free_text(text, text_length);

    return 0;
}

