#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define SENT 100
#define LEN 100


int main(){
        char** text = malloc(SENT * sizeof(char*));
        int i = 0;
        int j = 0;
        char chr;

        while (1){
                text[i] = malloc(LEN * sizeof(char));
                j = 0;
                chr = getchar();
                while (chr != '\n'|| chr == EOF){
                        text[i][j] = chr;
                        j++;
                        text[i][j] = '\0';
                        if (!(strcmp(text[i], "Fin.\0"))){
                                break;
                        }
                        chr = getchar();
                }
                text[i][j] = '\0';

                if (!(strcmp(text[i], "Fin.\0"))){
                        break;
                }
                i++;
        }

        char* r = "([a-zA-Z]+://)?(www\\.)?(\\w+(\\.\\w+)+)/(\\w+/)*(\\w+\\.\\w+)";
        regex_t regex;
        regcomp(&regex, r, REG_EXTENDED);

        for (int p = 0; p<i; p++){
                regmatch_t matches[7];
                if (!(regexec(&regex, text[p], 7, matches, 0))){
                        for (int j = matches[3].rm_so; j < matches[3].rm_eo; j++) {
                                printf("%c", text[p][j]);
                        }
                        printf(" - ");
                        for (int j = matches[6].rm_so; j < matches[6].rm_eo; j++) {
                                printf("%c", text[p][j]);
                        }
                        printf("\n");
                }
                free(text[p]);
        }
        free(text);
        regfree(&regex);
}