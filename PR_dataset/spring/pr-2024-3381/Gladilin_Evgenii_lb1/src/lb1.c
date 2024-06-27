#include <regex.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void print_group(int j, int end, char* buffer){
    for(; j < end; j++)
        printf("%c",buffer[j]);
}

int main(){
    regex_t regex;
    int value = 0;
    char buffer[100];
    int max_group = 8;
    regmatch_t groups[max_group];
    
    value = regcomp(&regex, "((\\w+:\\/\\/)?(www\\.)?((\\w+\\.)+\\w+)(\\/\\w+)*\\/(\\w+\\.\\w+))\n", REG_EXTENDED);
        if (value) {
            fprintf(stderr, "Could not compile regex\n");
            exit(1);
        }
        
    while(!strstr(buffer,"Fin.")){
        fgets(buffer, 100, stdin);
        value = regexec(&regex, buffer, max_group, groups, 0);
        if (!value) {
            print_group(groups[4].rm_so, groups[4].rm_eo, buffer);
            printf(" - ");
            print_group(groups[7].rm_so, groups[7].rm_eo, buffer);
            printf("\n");
        }
    }
    regfree(&regex);
    return 0;
}
