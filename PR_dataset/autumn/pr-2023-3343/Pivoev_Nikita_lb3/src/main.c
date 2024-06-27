#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define SIZE_STEP 50

char* inputText();
char** parseText(char* text, int* sentencesCount, int* realSentencesCount);
int upperCheck(char* text, int* currentLength, int i);
void removeSpaces(char** parsedText, int* realSentencesCount);

int main() {
    char* text = inputText();
    int sentencesCount = 0, realSentencesCount = 0;
    char** parsedText = parseText(text, &sentencesCount,&realSentencesCount);
    
    for(int i = 0; i < realSentencesCount; ++i) {
        printf("%s\n",parsedText[i]);
        free(parsedText[i]);
    }
    free(text);
    free(parsedText);
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d", sentencesCount, realSentencesCount);
}

char* inputText() {
    char* text;
    int size = 0;
    int limit = SIZE_STEP;
    text = malloc(sizeof(char)*SIZE_STEP);
    char letter;
    while((letter = getchar()) != '!') {
        if (letter == '\n')
            continue;
        if (size >= limit - 1) {
            limit += SIZE_STEP;
            text = realloc(text,sizeof(char)*limit);
        }
        text[size++] = letter;
    }
    text = realloc(text,sizeof(char)*(size+2));
    text[size++] = '!';
    text[size] = '\0';
    return text;
}

char** parseText(char* text, int* sentencesCount, int* realSentencesCount) {
    char** parsedText = malloc(sizeof(char*));
    int currentLength = 0;
    int position;
    
    for (int i = 0; i < strlen(text); ++i) {
        if (text[i] == '.' || text[i] == ';' || text[i] == '?') {
            position = 0;
            *sentencesCount = *sentencesCount + 1;
            
            if (upperCheck(text,&currentLength,i)) {
                continue;
            }

            *realSentencesCount = *realSentencesCount + 1;
            parsedText = realloc(parsedText,sizeof(char*) * *realSentencesCount);
            parsedText[*realSentencesCount-1] = malloc(sizeof(char)*(currentLength+2));
            
            for (int j = currentLength; j >= 0; --j)
                parsedText[*realSentencesCount-1][position++] = text[i-j];
            parsedText[*realSentencesCount-1][position] = '\0';

            removeSpaces(parsedText,&*realSentencesCount);

            currentLength = 0;
            continue;
        }
        ++currentLength;
    }
    return parsedText;
}

int upperCheck(char* text, int* currentLength, int i) {
    int upperCount = 0;
    for(int j = *currentLength; j >= 0; --j){
        if (isupper(text[i-j]) != 0) {
            ++upperCount;
        }
    }
    if (upperCount > 1) {
        *currentLength = 0;
        return 1;
    }
    return 0;
}

void removeSpaces(char** parsedText, int* realSentencesCount) {
    char* ptr = parsedText[*realSentencesCount-1];
    while (*ptr == ' ')
        ++ptr;
    memmove(parsedText[*realSentencesCount-1],ptr,strlen(ptr)+1);
}