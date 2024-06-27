#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
int main() {
    int size_sent = 20;
    int size_text = 20;
    char *sentence = malloc(size_sent * sizeof(char));
    char **text = malloc(size_text * sizeof(char*));
    int a = 0; 
    int i = size_sent;
    int j = size_text;
    int sents_count = 0;
    while (1) {
        char symbol = getchar();
        if (symbol == '\n'){
            sentence[a] = '\0';
            text[sents_count] = malloc((a + 1) * sizeof(char)); 
            strcpy(text[sents_count], sentence); 
            sents_count++;
            a = 0;
            if (sents_count >= j){ 
                j += size_text;
                text = realloc(text, j * sizeof(char*));
            }
        } else{
            sentence[a] = symbol;
            a++;
            if (a >= i){
                i += size_sent;
                sentence = realloc(sentence, i * sizeof(char));
            }
            sentence[a] = '\0';
            if (strcmp(sentence, "Fin.") == 0){
                break;
            }
        } 
    }
    regex_t regex;
    char *str = "([a-zA-Z]+:\\/\\/)?(www\\.)?(([a-zA-Z0-9-]+\\.)+[a-zA-Z0-9-]+)\\/([a-zA-Z0-9-]+\\/)*([a-zA-Z0-9-]+\\.[a-zA-Z0-9-]+)";
    size_t nmatch = 7; 
    regmatch_t match[7]; 
    if (regcomp(&regex, str, REG_EXTENDED) == 0){
        for (int k=0; k<sents_count; k++){
            if (regexec(&regex, text[k], nmatch, match, 0) == 0){
                for (int p = match[3].rm_so; p<match[3].rm_eo; p++){
                    printf("%c", text[k][p]);
                }
                printf(" - ");
                for (int p = match[6].rm_so; p<match[6].rm_eo; p++){
                    printf("%c", text[k][p]);
                }
                printf("\n");
            }
        }
    }
    for (int k = 0; k < sents_count; k++){
        free(text[k]); 
    }
    free(sentence);
    free(text);
    regfree(&regex);
    return 0;
}

