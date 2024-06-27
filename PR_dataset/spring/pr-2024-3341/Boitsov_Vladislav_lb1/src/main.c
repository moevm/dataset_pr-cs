#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<regex.h>

const char* pattern="([a-z]+\\:\\/\\/)?(www\\.)?(([a-z]+\\.)+[a-z]+)\\/([a-z]+\\/)*([a-z]+\\.[a-z0-9]+)";
const int maxNumOfGroups = 7;
const int maxBufSize = 1000;
const char* textEnding = "Fin.";

void printLinks(char* currentString, regmatch_t* currentGroup)
{
    for(int i=currentGroup[3].rm_so;i<currentGroup[3].rm_eo;i++)
        printf("%c", currentString[i]);
    printf(" - ");
    for(int i=currentGroup[6].rm_so;i<currentGroup[6].rm_eo;i++)
            printf("%c", currentString[i]);
    printf("\n");
}

int main()
{
    regex_t patternCompiled;
    regmatch_t groupsArray[maxNumOfGroups];
    regcomp(&patternCompiled, pattern, REG_EXTENDED);
    char buf[maxBufSize];
    do
    {
        fgets(buf, maxBufSize, stdin);
        if(regexec(&patternCompiled, buf, maxNumOfGroups, groupsArray, 0)==0)
        {
            printLinks(buf, groupsArray);
        }
    }
    while(strncmp(buf, textEnding, maxBufSize));
    regfree(&patternCompiled);
    return 0;
}