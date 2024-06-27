#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define STR_SIZE 100
#define END_INPUT "Fin."
#define REGEX_PATTERN "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+: ?~ ?# (.*)"

char* input_str();
void check_string(char* string, regex_t regex);
void print_matches(char* string, regmatch_t match);

int main() {
    regex_t regex;
    int check_comp = regcomp(&regex, REGEX_PATTERN, REG_EXTENDED);
    if (check_comp) {
        printf("Couldn't compile");
        return 1;
    }
    char* string = input_str();
    while (strcmp(END_INPUT, string) != 0) {
        check_string(string, regex);
        free(string);
        string = input_str();
    }

    return 0;
}

char* input_str() {
    char* string = (char*)calloc(STR_SIZE, sizeof(char));
    int check = 1;
    int number_of_symbol = 0;
    while (check) {
        if ((number_of_symbol + 1) % 100 == 98) {
            string = (char*)realloc(string, (number_of_symbol + STR_SIZE + 3) * sizeof(char));
        }
        char new_symbol = getchar();
        if (new_symbol == '\n' || strcmp(END_INPUT, string) == 0) {
            check = 0;
        }
        else {
            string[number_of_symbol] = new_symbol;
            number_of_symbol++;
        }
    }
    return string;
}

void check_string(char* string, regex_t regex) {
    regmatch_t matches[3];
    if (regexec(&regex, string, 3, matches, 0) == 0) {
        print_matches(string, matches[1]);
        printf(" - ");
        print_matches(string, matches[2]);
        printf("\n");
    }
}

void print_matches(char* string, regmatch_t match) {
    for (int i = match.rm_so; i < match.rm_eo; i++) {
        printf("%c", string[i]);
    }
}
