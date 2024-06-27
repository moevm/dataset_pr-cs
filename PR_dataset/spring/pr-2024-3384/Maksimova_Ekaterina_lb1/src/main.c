#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define MEMORY_STEP 8

char *readSentence(){
    int size = MEMORY_STEP;
    int len = 0;
    char *chars = malloc(size*sizeof(char));
    char symbol = ' ';

    if (symbol == ' ')
        symbol = getchar();

    while(symbol!='\n' && symbol != EOF){
        chars[len++] = symbol;
        if(len == size){
            size += MEMORY_STEP;
            chars = realloc(chars, size*sizeof(char));
        }
        symbol = getchar();
    }

    chars[len] = '\0';
    return chars;
}

void printGroups(char *str, size_t maxGroups, regmatch_t *groupArray) {
    for (int i = 1; i < maxGroups; i++) {
        if (groupArray[i].rm_so == -1)
            break;
        for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; j++)
            printf("%c", str[j]);
        if (i < 2)
            printf(" - ");
    }
    printf("\n");
}

int main() {
    char *str = readSentence();
    char * regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# (.*)+";
    size_t maxGroups = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)) {
        printf("Wowm no - can't compile regular expression\n");
        return 0;
    }

    do {
        if (regexec(&regexCompiled, str, maxGroups, groupArray, 0) == 0)
            printGroups(str, maxGroups, groupArray);
        free(str);
        str = readSentence();
    }while(strcmp(str, "Fin.") != 0);
    regfree(&regexCompiled);
    return 0;
}
