#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define INITIAL_CAPACITY 8

char *read_line()
{
    char *line = (char*)malloc(sizeof(char) * INITIAL_CAPACITY);
    if (line == NULL)
        return NULL;

    size_t line_size = 0;
    size_t line_capacity = INITIAL_CAPACITY;
    char c;

    c = getchar();
    while (c != EOF && c != '\n') {
        if (line_size + 1 == line_capacity) {
            line_capacity *= 2;
            line = (char*)realloc(line, sizeof(char) * line_capacity);
            if (line == NULL)
                return NULL;
        }

        line[line_size++] = c;
        c = getchar();
    }

    line[line_size] = '\0';
    return line;
}

int main()
{
    regex_t regex;
    if (regcomp(&regex, "(\\w+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)", REG_EXTENDED) != 0) {
        puts("Failed to compile regular expression");
        return EXIT_FAILURE;  
    }
  
    while (1) {
        char *str = read_line();
        if (str == NULL) {
            puts("Failed to read line from stdin");
            return EXIT_FAILURE;
        }

        if (strcmp(str, "Fin.") == 0 || str[0] == '\0') {
            free(str);
            break;
        }

        regmatch_t match[3];
        if (regexec(&regex, str, 3, match, 0) == 0) {
            str[match[1].rm_eo] = '\0';
            str[match[2].rm_eo] = '\0';
            printf("%s - %s\n", str + match[1].rm_so, str + match[2].rm_so);
        }
    
        free(str);
    }

    regfree(&regex);
    return 0;
}
