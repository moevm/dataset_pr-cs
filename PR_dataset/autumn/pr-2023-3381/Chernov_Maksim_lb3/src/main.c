#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define TRUE 1
#define BF 16

int findIndex(char *string, char *symbol);
int findSepIndex(char *string, int start);
int upperCount(char *string);
int main() {
    int CntSent = 0;
    int Tcnt = 0;
    int MaxSize = BF;
    char *buffer = calloc(BF, sizeof(char));
    char *sentence = calloc(MaxSize, sizeof(char));
    while (fgets(buffer, BF, stdin) != NULL) {
        int starti = 0;
        while (TRUE) {
            unsigned int endi = findSepIndex(buffer, starti);
            if (endi == -1) {
                MaxSize += BF;
                char *temp = realloc(sentence, MaxSize * sizeof(char));
                if (temp) sentence = temp;
                strcat(sentence, starti + buffer);
                break;
            }
            if (sentence[strlen(sentence) - 1] == ' ' && buffer[starti] == ' ')
                starti++;
            strncat(sentence, buffer + starti, endi - starti + 1);
            if (upperCount(sentence) > 1) {
                memset(sentence, 0, BF);
                Tcnt++;
                starti = endi + 1;
                continue;
            }
            short starts = 0;
            if (isspace(sentence[strlen(sentence) - 1])) sentence[strlen(sentence) - 1] = '\0';
            if (isspace(sentence[0])) starts = 1;
            printf("%s\n", starts + sentence);
            if (strstr(sentence, "Dragon flew away!")) {
                break;
            }
            memset(sentence, 0, MaxSize);
            MaxSize = BF;
            char *temp = realloc(sentence, MaxSize);
            if (temp) sentence = temp;
            CntSent++;
            starti = endi + 1;
        }
    }
    char *formatstring = "Количество предложений до %d и количество предложений после %d";
    printf(formatstring, Tcnt + CntSent, CntSent);
    free(buffer);
    free(sentence);
    return 0;
}
int upperCount(char *string) {
    int counter = 0;
    for(int i = 0; i < strlen(string); i++)
        if (isupper(string[i])) counter++;
    return counter;
}
int findIndex(char *string, char *symbol) {
    char *ptr = strstr(string, symbol);
    if (ptr == NULL) return -1;
    return ptr - string;
}
int findSepIndex(char *string, int start) {
    unsigned int doti = findIndex(string + start, ".");
    unsigned int sci = findIndex(string + start, ";");
    unsigned int exci = findIndex(string + start, "!");
    unsigned int qi = findIndex(string + start, "?");
    if (doti == -1 && sci == -1 && exci == -1 && qi == -1)
        return -1;
    int sepIndex = sci;
    if (doti < sci) sepIndex = doti;
    if (exci < sepIndex) sepIndex = exci;
    if (qi < sepIndex) sepIndex = qi;
    return start + sepIndex;
}