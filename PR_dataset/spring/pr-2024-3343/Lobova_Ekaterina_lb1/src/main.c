#include <stdio.h>
#include <regex.h>
#include <string.h>

void printGroup(char* s, regmatch_t group) {
    for (int i=group.rm_so; i<group.rm_eo; i++) {
        printf("%c", s[i]);
    }
}

int main ()
{
    char * regexString = "([A-Za-z]+:\\/{2})?(w{3}\\.)?(([A-Za-z0-9\\-]+\\.)+[A-Za-z0-9\\-]+)\\/([A-Za-z0-9_\\-]+\\/)*([A-Za-z0-9_\\-]+\\.[a-z0-9]+)";
 
    size_t maxGroups = 7;
    regex_t regexCompiled;
    regmatch_t groupArray[maxGroups];
    
    if (regcomp(&regexCompiled, regexString, REG_EXTENDED))
    {
        printf("Wowm no - can't compile regular expression\n");
        return 0;
    };
    
    char s[100];
    while(1){
        fgets(s,100,stdin);
         if (strstr(s,"Fin.") != NULL){
            break;
        }
        if (regexec(&regexCompiled, s, maxGroups, groupArray, 0) == 0){
            printGroup(s,groupArray[3]);
            printf(" - ");
            printGroup(s,groupArray[6]);
            printf("\n");
        } 
    }
    regfree(&regexCompiled);
    return 0;
}
