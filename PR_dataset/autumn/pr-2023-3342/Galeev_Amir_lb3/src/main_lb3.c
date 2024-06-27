#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define mx_wrds 1000
#define mx_txt 15000
#define str_end '\0'

int number_check(const char *word) {
    int size = 0;
    char *words[mx_wrds];
    int i = 0, j = 0;
    char currentWord[mx_wrds];
    
    while (word[i] != str_end) {
        if (word[i] != ' ') {
            currentWord[j] = word[i];
            j++;
        } else {
            currentWord[j] = str_end;
            int isAllDigits = 1;
            for (int k = 0; k < j; k++) {
                if (!isdigit(currentWord[k])) {
                    isAllDigits = 0;
                    break;
                }
            }
            if(j != 1) {
                if (!isAllDigits) {
                    words[size] = (char *)malloc((j + 1) * sizeof(char));
                    words[size][0] = ' ';
                    words[size][j - 1] = ' ';
                    strncpy(words[size] + 1, currentWord + 1, j - 2);
                    words[size][j] = str_end;
                    size++;
                }
            }

            j = 0;
        }
        i++;
    }

    currentWord[j] = str_end;
    int isAllDigits = 1;
    for (int k = 0; k < j; k++) {
        if (!isdigit(currentWord[k])) {
            isAllDigits = 0;
            break;
        }
    }

    if (!isAllDigits && j > 1) {
        words[size] = (char *)malloc((j + 1) * sizeof(char));
        words[size][0] = ' ';
        words[size][j - 1] = ' ';
        strncpy(words[size] + 1, currentWord + 1, j - 2);
        words[size][j] = str_end;
        size++;
    }

for (int i = 0; i < size; i++) {
    for (int k = 0; words[i][k] != str_end; k++) {
        if (isdigit(words[i][k])) {
            free(words[i]);
            words[i] = NULL;
            return 1;
        }
    }
    free(words[i]);
    words[i] = NULL;
}

    return 0;
}

void replaceSubstr(char *str, const char *find, const char *replace) {
    char *pos = str;
    while ((pos = strstr(pos, find))) {
        memmove(pos + strlen(replace), pos + strlen(find), strlen(pos + strlen(find)) + 1);
        memcpy(pos, replace, strlen(replace));
        pos += strlen(replace);
    }
}

void text_processing(char *text, int *beforeCount, int *afterCount) {
    char *result = (char *)malloc(mx_txt * sizeof(char));
    result[0] = str_end;
    char *sentence = strtok(text, ".;?");
    while (sentence) {
        while (*sentence && isspace(*sentence)) {
            sentence++;
        }
        if (!number_check(sentence)) {
            strcat(result, sentence);
            strcat(result, "\n");
            (*afterCount)++;
        }
        (*beforeCount)++;
        sentence = strtok(NULL, ".;?");
    }
    replaceSubstr(result, " +", ".");
    replaceSubstr(result, " -", "?");
    replaceSubstr(result, " =", ";");
    printf("%s", result);
    free(result);
}

int main() {
    char *text = (char *)malloc(mx_txt * sizeof(char));
    int beforeCount = 0, afterCount = 0;
    fgets(text, mx_txt, stdin);
    text[strcspn(text, "\n")] = str_end;
    replaceSubstr(text, ".", " +.");
    replaceSubstr(text, "?", " -?");
    replaceSubstr(text, ";", " =;");
    text_processing(text, &beforeCount, &afterCount);
    printf("Количество предложений до %d и количество предложений после %d\n", beforeCount - 1, afterCount - 1);
    free(text);
    return 0;
}