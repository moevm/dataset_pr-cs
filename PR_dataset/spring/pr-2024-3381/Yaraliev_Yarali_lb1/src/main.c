#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SIZE 100

int main(){
    regex_t regex;
    int value = 0;
    char text[SIZE];
    int max_group = 8;
    regmatch_t groups[max_group];
    value = regcomp(&regex, "((\\w+:\\/\\/)?(www\\.)?((\\w+\\.)+\\w+)(\\/\\w+)*\\/(\\w+\\.\\w+))", REG_EXTENDED);
    if (value) {
        fprintf(stderr, "Could not compile regex\n");
        exit(1);
    }
    
    while(1){
        fgets(text, SIZE, stdin);
        if (strstr(text, "Fin.")) {
            break;
        }
        value = regexec(&regex, text, max_group, groups, 0);
        if (!value) {
            printf("%.*s - %.*s\n", (int)(groups[4].rm_eo - groups[4].rm_so), text + groups[4].rm_so,
                                     (int)(groups[7].rm_eo - groups[7].rm_so), text + groups[7].rm_so);
        }
    }
    regfree(&regex);
    return 0;
}
