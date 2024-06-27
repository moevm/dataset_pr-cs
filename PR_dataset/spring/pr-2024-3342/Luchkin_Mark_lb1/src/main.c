#include <stdio.h>
#include <string.h>
#include <regex.h>
#define STRING_SIZE 100

int main(){
    regex_t reg;
    regmatch_t groups[7];
    char string[STRING_SIZE];
    regcomp(&reg, "(.*:\\/*)*(w*\\.)*(([a-z]+\\.)+[a-z]+)\\/(.*\\/)*(.*\\..*)\n", REG_EXTENDED);

    while (strcmp(string, "Fin.") != 0){
        fgets(string, STRING_SIZE, stdin);

        if (!regexec(&reg, string, 7, groups, 0)){
            for (int i = groups[3].rm_so; i < groups[3].rm_eo; i++){
              printf("%c", string[i]);
            }

            printf(" - ");
            for (int j = groups[6].rm_so; j < groups[6].rm_eo; j++){
              printf("%c", string[j]);
            }

            printf("%c",'\n');
        }

    }
    regfree(&reg);

    return 0;
}
