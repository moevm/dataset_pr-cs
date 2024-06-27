#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#define STEP 20
int main()
{
    char** text;
    char* sentence;
    char symbol;
    int size_text = 10;
    int size_sent = 10;
    int num_sent = 0, i = 0;
    text = (char**)calloc(size_text, sizeof(char*));
    sentence = (char*)calloc(size_sent, sizeof(char));
    while (strcmp(sentence, "Fin.")) {
        symbol = getchar();
        if (symbol == '\n') {
            if (size_text <= num_sent) {
                size_text += STEP;
                text = (char**)realloc(text, size_text*sizeof(char*));
            }
            text[num_sent] = sentence;
            sentence = (char*)calloc(size_sent, sizeof(char));
            num_sent++;
            i = 0;
        }
        else {
            if (size_sent <= i) {
                size_sent += STEP;
                sentence = (char*)realloc(sentence, size_sent*sizeof(char));
            }
            sentence[i++] = symbol;
        }
    }
    char* pattern = "([a-zA-z]+\\:\\/{2})?(w{3}\\.)?([_a-zA-Z0-9-]+(\\.[_a-zA-Z0-9-]+)+)(\\/[_a-zA-Z0-9-]+)*\\/([_a-zA-Z0-9-]+\\.[_a-zA-Z0-9-]+)";
    int maxgroup = 7;
    regmatch_t group[7];
    regex_t reg;
    regcomp(&reg, pattern, REG_EXTENDED);
    for (int i = 0; i < num_sent; i++) {
        if (regexec(&reg, text[i], maxgroup, group, 0) == 0) {
            for (int j = group[3].rm_so; j < group[3].rm_eo; j++) {
                printf("%c", text[i][j]);
            }
            printf(" - ");
            for (int j = group[6].rm_so; j < group[6].rm_eo; j++) {
                printf("%c", text[i][j]);
            }
            printf("\n");
            free(text[i]);
        }
    }
    free(text);
    regfree(&reg);
    return 0;
}