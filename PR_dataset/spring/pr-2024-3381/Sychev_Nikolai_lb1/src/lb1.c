#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 1024
#define FILE_GROUP 7
#define SITE_GROUP 3
#define REGEX_STRING "([a-z]+:\\/\\/)?(www\\.)?(([a-z0-9]+\\.)+[a-z]+)\\/((\\w+\\/)+)?(\\w+\\.\\w+)"


int main() 
{
    size_t maxGroups = 8;
    regex_t regex;
    regmatch_t groupArray[maxGroups];

    if (regcomp(&regex, REGEX_STRING, REG_EXTENDED)) {
        return 1;
    };
    
    char input_string[SIZE];
    while (!strstr(input_string, "Fin.")) {
        (fgets(input_string, SIZE, stdin));
        
        if (!regexec(&regex, input_string, maxGroups, groupArray, 0)) {
                for(int j=groupArray[SITE_GROUP].rm_so; j < groupArray[SITE_GROUP].rm_eo; j++)
                    printf("%c",input_string[j]);
                printf(" - ");

                for(int j=groupArray[FILE_GROUP].rm_so; j < groupArray[FILE_GROUP].rm_eo;j++)
                    printf("%c",input_string[j]);
                printf("\n");
        }
    }
    regfree(&regex);
    return 0;
}