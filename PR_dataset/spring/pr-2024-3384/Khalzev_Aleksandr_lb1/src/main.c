#include <stdio.h>
#include <stdlib.h>
#include <regex.h>
#include <string.h>

char** write_text(int* c_pr) {
    char** text = NULL;
    char* sent = malloc(sizeof(char));
    char el;
    sent[0] = '\0';
    int len_sent = 1, len_txt = 0, ch_sent = 1;

    while (1) {
        el = getchar();

        if(el == '\n' || el == EOF) {
            len_txt++;
            text = (char**)realloc(text, sizeof(char*) * len_txt);
            text[len_txt - 1] = sent;
            if(sent[len_sent - 2] == '.' && sent[len_sent - 3] == 'n' && sent[len_sent - 4] == 'i' && sent[len_sent - 5] == 'F') {
                break;
            }
            ch_sent++;
            sent = malloc(ch_sent * sizeof(char));
            sent[0] = '\0';
            len_sent = 1;
        } else {
            len_sent++;
            if(ch_sent == len_sent) {
                ch_sent++;
                sent = (char*)realloc(sent, sizeof(char) * ch_sent);
            }
            sent[len_sent - 1] = '\0';
            sent[len_sent - 2] = el;
        }
    }
    *c_pr = len_txt;
    return text;
}

int main()
{
    int lent;
    char** text = write_text(&lent);
    char* regexSTR = "([a-zA-Z0-9_]+)@[a-zA-Z0-9_-]+: ?\\~ ?\\# (.+)";
    regex_t regexCOMPL;
    regmatch_t groups[3];
    regcomp(&regexCOMPL, regexSTR, REG_EXTENDED);
    for (int i = 0; i < lent; i++) {
        if (regexec(&regexCOMPL, text[i], 3, groups, 0) == 0) {
            for (int j = 1; j < 3; j++) {
                if (groups[j].rm_so != -1) {
                    for (int k = groups[j].rm_so; k < groups[j].rm_eo; k++) {
                        printf("%c", text[i][k]);
                    }
                    if(j != 2){
                        printf(" - ");
                    }
                }
            }
            printf("\n");
        }
    }

    free(text);
    return 0;
}

