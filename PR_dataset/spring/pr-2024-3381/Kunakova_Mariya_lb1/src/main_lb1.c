#include <stdio.h>
#include <regex.h>
#include <stdlib.h>
#include <string.h>
#define SIZE_STRING 256
#define AMOUNT_GROUPS 7
#define NAME_WEBSITE 3
#define NAME_FILE 6

int main(){
    char* regexString = "(\\w+\\:\\/\\/)?(www\\.)?(\\w+(\\.\\w+)+)(\\/\\w+)*\\/(\\w+\\.\\w+)$";
    regex_t regexCompiled;
    regmatch_t groupArray[AMOUNT_GROUPS];
    if(regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("ERROR: This regular expression was not compiled\n");
        return 0;
    }
    int regexStatus;
    while(1)
    {
        char* currentString = calloc(SIZE_STRING, sizeof(char));
        fgets(currentString, SIZE_STRING, stdin);
        for(int i = 0; i < SIZE_STRING; i++)
        {
            if(currentString[i] == '\n')
            {
                currentString[i] = '\0';
            }
        }
        if(!strcmp(currentString, "Fin."))
        {
            free(currentString);
            break;
        }
        regexStatus = regexec(&regexCompiled, currentString, AMOUNT_GROUPS, groupArray, 0);
        if(regexStatus == 0)
        {
            for(int i = groupArray[NAME_WEBSITE].rm_so; i < groupArray[NAME_WEBSITE].rm_eo; i++)
            {
                printf("%c", currentString[i]);
            }
            printf(" - ");
            for(int i = groupArray[NAME_FILE].rm_so; i < groupArray[NAME_FILE].rm_eo; i++)
            {
                printf("%c", currentString[i]);
            }
            printf("\n");
        }
        free(currentString);
    }
    regfree(&regexCompiled);
    return 0;
}