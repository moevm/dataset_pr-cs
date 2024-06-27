#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#define TRUE 1
#define PATTERN "(\\w+)@([A-Za-z0-9_-]+):\\s*~\\s*#\\s(.*)"
int main()
{
    char* regexString=PATTERN;
    regex_t regexCompiled;

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("can't compile regular expression\n");
        return 0;
    };

    size_t maxGroups=4;
    regmatch_t groupArray[maxGroups];

    char inp[200];
    char names[50][100];
    char commands[50][100];
    int sent,temp=0;
    while(TRUE){
        fgets(inp,200,stdin);

        if (strstr(inp,"Fin.")!=NULL){
            break;
        }

        if(regexec(&regexCompiled,inp,maxGroups,groupArray, 0) == 0){
                for (int i=groupArray[1].rm_so;i<groupArray[1].rm_eo;i++)
                    names[sent][temp++] = inp[i];
                temp=0;
                for(int j=groupArray[3].rm_so;j<groupArray[3].rm_eo-1;j++)
                    commands[sent][temp++] = inp[j];
                temp=0;sent++;
        }

    }
    
    for (int i=0;i<sent;i++)
        printf("%s - %s\n", names[i], commands[i]);
    
    regfree(&regexCompiled);
    return 0;
} 
