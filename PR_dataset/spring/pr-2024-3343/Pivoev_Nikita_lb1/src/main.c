#include <stdio.h>
#include <regex.h>
#include <string.h>
/*
gcc ./main.c -lregex
./a.exe
*/
int main (){
    char * regexString = "([0-9a-zA-Z_-]+)@[0-9a-zA-Z_-]+: *~ *# (.+)";
    
    size_t groups = 3;
    regex_t compiledString;
    regmatch_t groupArray[groups];

    regcomp(&compiledString, regexString, REG_EXTENDED);
    
    char s[1000];
    while (fgets(s,1000,stdin)){
        if (strstr(s, "Fin.") != NULL)
            break;
        
        if (regexec(&compiledString, s, groups, groupArray, 0) == 0){
            for (int i = 1; i < groups; ++i){
                for (int j = groupArray[i].rm_so; j < groupArray[i].rm_eo; ++j)
                    printf("%c", s[j]);
                if (i == 1)
                    printf(" - ");
            }
        } 
    }
    regfree(&compiledString);
    return 0;
}