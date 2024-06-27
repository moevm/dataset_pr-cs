#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>

const char* regexPattern = "([a-z]+\\:\\/\\/)?(www\\.)?(([a-z]+\\.)+[a-z]+)\\/([a-z]+\\/)*([a-z]+\\.[a-z0-9]+)";

void printMatchedLinks(char* currentStr, regmatch_t* currentGroups)
{
    for(int i=currentGroups[3].rm_so;i<currentGroups[3].rm_eo;i++)
        printf("%c", currentStr[i]);
    printf(" - ");
    for(int i=currentGroups[6].rm_so;i<currentGroups[6].rm_eo;i++)
            printf("%c", currentStr[i]);
    printf("\n");
}

int main()
{
    regex_t compiledRegex;
    regmatch_t groups[1000];
    regcomp(&compiledRegex, regexPattern, REG_EXTENDED);
    char buffer[1000];
    do
    {
        fgets(buffer, 1000, stdin);
        if(regexec(&compiledRegex, buffer, 7, groups, 0)==0)
        {
            printMatchedLinks(buffer, groups);
        }
    }
    while(strncmp(buffer, "Fin.", 1000));
    regfree(&compiledRegex);
    return 0;
}