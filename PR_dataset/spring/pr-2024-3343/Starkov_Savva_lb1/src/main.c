#include <stdio.h>
#include <regex.h>
#include <string.h>
void printGroup(char* string, regmatch_t group) {
    for (int i=group.rm_so; i<group.rm_eo; i++) {
        printf("%c", string[i]);
    }
}

int main()
{
    char* regString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: *~ *# (.*)";
    size_t maxGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    if (regcomp(&regexCompiled,regString,REG_EXTENDED))
    {
        printf("Cant Compile\n");
        return 0;
    }
    char s[101];
    while(1)
    {
        fgets(s,100,stdin);
        if (strstr(s,"Fin.") != NULL){
            break;
        }
        if(regexec(&regexCompiled, s,maxGroups,groupArray,0) == 0){
            printGroup(s,groupArray[1]);
            printf(" - ");
            printGroup(s,groupArray[2]);
        }
    }
    regfree(&regexCompiled);
    return 0;
}
