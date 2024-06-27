#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define REGEX_STRING "([A-Za-z]+:\\/\\/)?(w{3}\\.)?(([A-Za-z0-9\\-]+\\.)+[A-Za-z0-9\\-]+)\\/([A-Za-z0-9\\-]+\\/)*([A-Za-z0-9\\-]+\\.[A-Za-z0-9\\-]+)"


char *readLine(){
    size_t cnt = 0, capacity = 1;
    char *line = (char *)malloc(sizeof(char) * capacity);
    char ch;

    while((ch = getchar()) != '\n'){
        line[cnt++] = ch;
        if(cnt == capacity){
            capacity += 1;
            line = (char *)realloc(line, sizeof(char) * capacity);
        }
        if(strcmp(line, "Fin.") == 0)
            return line;
    }

    return line;
}


int main(){
    char *line;
    char *regexString = REGEX_STRING;
    size_t maxGroups = 7;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];

    regcomp(&regexCompiled, regexString, REG_EXTENDED);
        
    while(strcmp((line = readLine()), "Fin.") != 0){
        if(regexec(&regexCompiled, line, maxGroups, groupArray, 0) == 0){
            for(size_t i = groupArray[3].rm_so; i < groupArray[3].rm_eo; i++)
                printf("%c", line[i]);
            printf(" - ");
            for(size_t i = groupArray[6].rm_so; i < groupArray[6].rm_eo; i++)
                printf("%c", line[i]);
            printf("\n");
        }
        free(line);
    }

    regfree(&regexCompiled);
    return 0;
}
