#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STEP 20
#define N 100

char** addLine(char** text, int* capacity, int* lastIndex, char* sentence) {
    if (*lastIndex >= *capacity) {
        *capacity += STEP;
        char** check = realloc(text, *capacity * sizeof(char*));
        if (!check){
            printf("Ошибка выделения памяти");
            exit(1);
        }
        text = check;
    }
    text[*lastIndex] = malloc((strlen(sentence) + 1) * sizeof(char));
    strcpy(text[*lastIndex], sentence);
    (*lastIndex)++;
    return text;
}

char* addChar(char* line, int* capacity, int* lastIndex, char c) {
    if (*lastIndex >= *capacity){
        *capacity += STEP;
        char* check = realloc(line, *capacity * sizeof(char));
        if (!check){
            printf("Ошибка выделения памяти");
            exit(1);
        }
        line = check;
    }
    line[*lastIndex] = c;
    (*lastIndex)++;
    return line;
}

int main() {
    char** result = malloc(N * sizeof(char*));
    int capacity = N;
    int lastIndex = 0;
    char* currentLine = malloc(N * sizeof(char));
    int currentCapacity = N;
    int currentLastIndex = 0;
    int endCounter = 0;
    int before = 0;
    char c = ' ';

    while(c != '!'){
        c = getchar();
        if (currentLastIndex == 0 && isspace(c)){
            continue;
        }
        currentLine = addChar(currentLine, &currentCapacity, &currentLastIndex, c);
        if (c == '.' || c == ';' || c == '!' || c == '?') {
            before++;
            currentLine = addChar(currentLine, &currentCapacity, &currentLastIndex, '\0');
            if (c != '?') {
                result = addLine(result, &capacity, &lastIndex, currentLine);
            } else {
                endCounter++;
            }
            currentLine = malloc(N * sizeof(char));
            currentCapacity = N;
            currentLastIndex = 0;
        }
    }

    for (int i = 0; i < lastIndex; i++) {
        puts(result[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d", before - 1, before - endCounter - 1);
}