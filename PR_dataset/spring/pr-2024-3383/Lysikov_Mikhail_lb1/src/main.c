#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
int main() {
    int a = 0;
    int b = 0;
    int size = 100;
    int count = 0;
    char *line = malloc(size * sizeof(char));
    int linecnt = 0;
    while (count != 4) {
        char input = getchar();
        if ((count == 0) && (input == 'F')) count++;
        else if ((count == 1) && (input == 'i')) count++;
        else if ((count == 2) && (input == 'n')) count++;
        else if ((count == 3) && (input == '.')) count++;
        else count = 0;
        if (input == '\n') linecnt++;
        if (a >= size - 2) {
            size += 100;
            line = realloc(line, size * sizeof(char));
        }
        line[a] = input;
        a++;
    }
    line[a] = '\0';
    char **lines = malloc((linecnt + 1) * sizeof(char*));
    char *slice = strtok(line,"\n");
    while (slice != NULL){
        lines[b] = strdup(slice);
        b++;
        slice = strtok(NULL,"\n");
    }
    free(line);
    regex_t regex;
    char *pattern = "([[:alnum:]_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)";
    int ret = regcomp(&regex, pattern, REG_EXTENDED);
    regmatch_t pmatch[3];
    size_t nmatch = 3;
    if (ret == 0){
        for (int i = 0; i < linecnt; i++){
            ret = regexec(&regex, lines[i], nmatch, pmatch, 0);
            if (ret == 0) {
                for(int j = pmatch[1].rm_so; j < pmatch[1].rm_eo; j++){
                    printf("%c",lines[i][j]);
                }
                printf(" - ");
                for(int j = pmatch[2].rm_so; j < pmatch[2].rm_eo; j++){
                    printf("%c",lines[i][j]);
                }
                printf("\n");
            }
        }
    }else{
        printf("Ошибка: Регулярное выражение некорректно");
    }
    regfree(&regex);
    for (int i = 0; i < linecnt; i++){
        free(lines[i]);
    }
    free(lines);
    return 0;
}