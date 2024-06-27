#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>

int main(){

    // Ввод
    char **inputs = (char**)malloc(1*sizeof(char*));
    size_t num_inp = 0;
    char *s = (char*)malloc(1*sizeof(char));
    size_t len_s = 1;
    char c;

    while (1){
        do{
            c = getchar();
            len_s++;
            s = (char*)realloc(s, sizeof(char)*len_s);
            s[len_s-2] = c;
            s[len_s-1] = '\0';
        } while (c != '\n' && c != EOF);
        if (s[0] == 'F' && s[1] == 'i' && s[2] == 'n' && s[3] == '.'){
            break;
        }
        inputs[num_inp] = (char*)malloc((strlen(s)+1)*sizeof(char));
        strcpy(inputs[num_inp++], s);
        inputs = (char**)realloc(inputs, sizeof(char*)*(num_inp+1));
        len_s = 1;
    }

    // Обработка
    char *regexString = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_\\-]+: ?~ ?# (.+)";
    size_t maxGroup = 3;

    regex_t regexCompiled;
    regmatch_t groupArray[maxGroup];

    if (regcomp(&regexCompiled, regexString, REG_EXTENDED)){
        printf("Wow, no - can't compile regular expression\n");
        return 0;
    }
    for (int i=0; i<num_inp; i++){
        if (regexec(&regexCompiled, inputs[i], maxGroup, groupArray, 0) == 0){
            for(int j=groupArray[1].rm_so; j<groupArray[1].rm_eo; j++){
                printf("%c", inputs[i][j]);
            }
            printf(" - ");
            for(int j=groupArray[2].rm_so; j<groupArray[2].rm_eo; j++){
                printf("%c", inputs[i][j]);
            }
        }
    }

    return 0;
}
