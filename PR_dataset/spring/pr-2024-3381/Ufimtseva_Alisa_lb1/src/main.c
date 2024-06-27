#include <stdio.h>
#include <regex.h>
#include <string.h>

#define PATTERN "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# ([ -~]+)\n"

int main()
{
    size_t maxGroups = 3;
    
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    char * cursor;
    
    if (regcomp(&regexCompiled, PATTERN, REG_EXTENDED))
    {
        printf("ERROR\n");
        return 1;
    };
    
    char command[100];
    fgets(command, 100, stdin);
    while (!strstr(command, "Fin.")){
        cursor = command;
        if (regexec(&regexCompiled, cursor, maxGroups, groupArray, 0)){
            fgets(command, 100, stdin); 
            continue;  // No more matches
        }
        for (int g = 1; g < maxGroups; g++){
            for (size_t i=groupArray[g].rm_so; i<groupArray[g].rm_eo; i++){
                printf("%c", command[i]);
            }
            switch(g){
                case 1:
                    printf(" - ");
                    break;
                case 2:
                    printf("\n");
                    break;
                default: 
                    break;
            }
        }
        fgets(command, 100, stdin);    
    }  
    regfree(&regexCompiled);
    
    return 0;
}