#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>


void getLine(char* line) {
    int i=0;
    for (i = 0; i < 100; ++i) {
        line[i]=getchar();
        if (line[i]==10){
            break;
        }
    }
    line[i]='\0';
    i=0;
}
void print(char* link, regmatch_t* groups){
    for (int i = groups[3].rm_so; i < groups[3].rm_eo; ++i) {
        printf("%c", link[i]);
    }
    printf(" - ");
    for (int i = groups[8].rm_so; i < groups[8].rm_eo; ++i) {
        printf("%c", link[i]);
    }
    puts("");
}
int main(){
    char* line= malloc(sizeof(char)*100);
    char* str_pat="([a-z]+:\\/\\/)?(www\\.)?((\\w+\\.)(\\w+\\.)*\\w+)\\/((\\w+\\/)*)?(\\w+\\.\\w+)";
    regex_t regex_compiled;
    regcomp(&regex_compiled, str_pat, REG_EXTENDED);
    regmatch_t groups[9];
    do{
        getLine(line);
        if (regexec(&regex_compiled, line, 9, groups, 0) == 0)
            print(line, groups);

    }while (strncmp(line, "Fin.", strlen("Fin."))!=0);
    regfree(&regex_compiled);
    free(line);

    return 0;
}