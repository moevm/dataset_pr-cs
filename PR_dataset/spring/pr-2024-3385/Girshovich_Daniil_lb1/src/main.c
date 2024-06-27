#include <stdio.h>
#include <regex.h>
#include <string.h>

#define inputSize 2048

int main() {
    char input[inputSize];
    char* regexPattern =  "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?~ ?# ?(.+)";

    size_t countGroups = 3;
    regex_t regexCompiled;
    regmatch_t groupArray[countGroups];


    if(regcomp(&regexCompiled,regexPattern,REG_EXTENDED)){
        printf(("Regex compilation error\n"));
        return 1;
    }
    while(fgets(input, inputSize, stdin)){
        if(strstr(input,"Fin.")){
            break;
        }
        if(regexec(&regexCompiled,input,countGroups,groupArray,0) == 0){
            for(int i = groupArray[1].rm_so; i < groupArray[1].rm_eo;i++){
                printf("%c", input[i]);
            }
            printf(" - ");
            for (int i = groupArray[2].rm_so; i < groupArray[2].rm_eo; i++) {
                printf("%c", input[i]);
            }
        }
    }
    regfree(&regexCompiled);
    return 0;
}