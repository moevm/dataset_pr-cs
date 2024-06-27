#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(){
    regex_t reg;
    char* sentences = calloc(1, sizeof(char));
    int len = 0;
    int sizemas = 1;
    char symbol;
    while (1){
        symbol = getchar();
        sentences[len]=symbol;
        len++;
        if (len == sizemas) {
            sizemas= sizemas+100;
            sentences = realloc(sentences, sizemas * sizeof(char));
        }
        if (strstr (sentences,"\nFin.")){
            break;                
        }
    }

    char* token = strtok(sentences, "\n");
    int numSentences = 0;
    char** stroki = malloc(len * sizeof(char*));
    while (token != NULL) {
        stroki[numSentences] = malloc(strlen(token) + 1);  
        strcpy(stroki[numSentences], token);               
        numSentences++;
        token = strtok(NULL, "\n");
    }
    size_t nmatch = 4;
    regmatch_t match[nmatch];

    if (!regcomp(&reg, "([a-zA-Z0-9_]+)@([a-zA-Z0-9_-]+): ?~ ?# (.+)", REG_EXTENDED)) {

        for (size_t i = 0; i < numSentences; i++) {
            if (!regexec(&reg, stroki[i], nmatch, match, 0)) {
                printf("\n");
                for (int j = match[1].rm_so; j < match[1].rm_eo; j++) {
                    printf("%c", stroki[i][j]);
                }
                printf(" - ");
                for (int j = match[3].rm_so; j < match[3].rm_eo; j++) {
                    printf("%c", stroki[i][j]);
                }
                
            }
        }

        regfree(&reg);
    }
    return 0;
}
