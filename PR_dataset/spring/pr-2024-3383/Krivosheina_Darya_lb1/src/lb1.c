#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define TEXT 10
#define SENT 20

int main(){
    int len_sent = 0, len_text = 0;
    int cap_sent = SENT, cap_text = TEXT;
    char** text = malloc(TEXT * sizeof(char*));
    char* sent = malloc(SENT * sizeof(char));
    char g;
    
    while(1){
        g = getchar();
        if (g == '\n'){
            if (len_text % (TEXT - 1) == 0){
                cap_text += TEXT;
                text = realloc(text, cap_text * sizeof(char*));
            }
            text[len_text] = malloc((len_sent + 1) * sizeof(char));
            for (int i = 0; i < len_sent; i++){
                text[len_text][i] = sent[i];
            }
            text[len_text][len_sent] = '\0';
            len_text ++;
            memset(sent, 0, len_sent);
            len_sent = 0;
            cap_sent = SENT;
        } else {
            if (len_sent % (SENT - 1) == 0){
                cap_sent += SENT;
                sent = realloc(sent, cap_sent * sizeof(char));
            }
            sent[len_sent] = g;
            len_sent ++;
            if (strcmp(sent, "Fin.") == 0){
                break;
            }
        }
    }
    regex_t compiled;
    char* pattern = "(\\w+)@(\\w|-)+: ?~ ?\\# (.+)";
    int check;
    size_t nmatch = 4;
    regmatch_t matchptr[4];
    if ((check = regcomp(&compiled, pattern, REG_EXTENDED)) == 0){
        for (int t = 0; t < len_text; t++){
            if ((check = regexec(&compiled, text[t], nmatch, matchptr, 0)) == 0){
                for (int t1 = matchptr[1].rm_so; t1 < matchptr[1].rm_eo; t1++){
                    printf("%c", text[t][t1]);
                }
                printf(" - ");
                for (int t2 = matchptr[3].rm_so; t2 < matchptr[3].rm_eo; t2++){
                    printf("%c", text[t][t2]);
                }
                printf("\n");
            }
        }
    }
    regfree(&compiled);
    for (int f = 0; f < len_text; f++){
        free(text[f]);
    }
    free(text);
    return 0;
}
