#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 10
#define END_SYMBOL '!'
#define SPLITTERS ".;?"

char *textInput();
char **textConvert(char *inputText, int *initialSentencesNumber, int *resultSentenceNumber, const char *splitters);


int main(){
    const char *splitters = SPLITTERS;
    int initialSentencesNumber = 0;
    int resultSentencesNumber = 0;
    char *inputText = textInput();
    char **convertedText = textConvert(inputText, &initialSentencesNumber, &resultSentencesNumber, splitters);

    for (int i = 0; i < resultSentencesNumber; i++){
        printf("%s\n", convertedText[i]);
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d\n", initialSentencesNumber, resultSentencesNumber);

    for (int i = 0; i < resultSentencesNumber; i++){
        free(convertedText[i]);
    }
    free(inputText);
    return 0;
}


char *textInput(){
    int textSize = 0;
    int capacity = BLOCK_SIZE;
    char *text = (char *)malloc(sizeof(char) * BLOCK_SIZE);
    char currentChar;
    while ((currentChar = getchar()) != END_SYMBOL){
        if (currentChar == '\n'){
            continue;
        }
        if (textSize >= capacity - 1){
            capacity += BLOCK_SIZE;
            text = (char *)realloc(text, sizeof(char) * capacity);
        }
        text[textSize++] = currentChar;
    }
    text = (char *)realloc(text, sizeof(char) * (textSize + 2));
    text[textSize++] = END_SYMBOL;
    text[textSize] = '\0';

    return text;
}


char **textConvert(char *inputText, int *initialSentencesNumber, int *resultSentencesNumber, const char *splitters){
    int sentencesCounter = 0;
    int end = 0;
    int charsCounter;
    char **convertedText = (char **)malloc(sizeof(char *));
    for (int i = 0; i < strlen(inputText); i++){
        if (strchr(splitters, inputText[i]) != NULL){
            sentencesCounter++;
            convertedText = (char **)realloc(convertedText, sizeof(char *) * sentencesCounter);
            convertedText[sentencesCounter - 1] = (char *)malloc(sizeof(char) * (end + 2));

            charsCounter = 0;
            for (int j = end; j >= 0; j--){
                convertedText[sentencesCounter - 1][charsCounter++] = inputText[i - j];
            }
            convertedText[sentencesCounter - 1][charsCounter] = '\0';

            char *p = convertedText[sentencesCounter - 1];
            while (*p == ' '){
                p++;
            }
            memmove(convertedText[sentencesCounter - 1], p, strlen(p) + 1);
            end = 0;
            continue;
        }
        end++;
    }
    *initialSentencesNumber = sentencesCounter;

    int sentencesNumber = *initialSentencesNumber;
    int deletedSentencesCounter = 0;
    for (int i = 0; i < sentencesNumber; i++){
        char *sentence = convertedText[i];
        if (strstr(sentence, "555 ") != NULL || strstr(sentence, " 555.") != NULL || strstr(sentence, " 555;") != NULL || strstr(sentence, " 555?") || NULL){
            deletedSentencesCounter++;
            --sentencesNumber;
            for (int j = i; j < sentencesNumber; j++){
                convertedText[j] = convertedText[j + 1];
            }
            i -= 1;
            convertedText[sentencesNumber] = NULL;
            free(sentence);
        }
    }
    *resultSentencesNumber = *initialSentencesNumber - deletedSentencesCounter;


    return convertedText;
}
