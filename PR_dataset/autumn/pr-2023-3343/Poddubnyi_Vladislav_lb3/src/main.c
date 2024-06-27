#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char** readText(int* textSize, int* refactoredTextSize);
char* generateText(char** text, int textSize);

int main() {
    // put your code here
    int textSize = 0;
    int questionOccurencies = 0;
    char** text = readText(&textSize, &questionOccurencies);
    char* newText = generateText(text,textSize);
    printf("%sКоличество предложений до %d и количество предложений после %d", newText,textSize + questionOccurencies -1, textSize -1);
    return 0;
}

char** readText(int* textSize, int* refactoredTextSize){
    int sentenceBuffer = 1;
    int textBuffer = 1;
    int sentenceSize = 0;
    char tempChar;

    char* sentence = malloc(sizeof(char) * sentenceBuffer);
    char** text = malloc(sizeof(char*)*textBuffer);

   do{
        tempChar = getchar();
        if(tempChar=='\n'){
            continue;
        }
        sentence[sentenceSize++] = tempChar;
        if (sentenceSize >= sentenceBuffer){
            sentenceBuffer *= 2;
            sentence = realloc(sentence, sizeof(char) * sentenceBuffer);
        }

        if(tempChar=='.' || tempChar==';' || tempChar=='!'){
            sentence[sentenceSize] = '\0';
            if (sentence[0]==' '){
                memmove(sentence,sentence+1, strlen(sentence));
            }
            text[(*textSize)++] = strdup(sentence);
            sentenceSize=0;
            sentenceBuffer=1;
            if ((*textSize)>=textBuffer){
                textBuffer *= 2;
                text = realloc(text,sizeof(char*)*textBuffer);
            }
        }
        if (tempChar=='?'){
            sentenceSize=0;
            sentenceBuffer=1;
            (*refactoredTextSize) ++;
        }
    }  while (tempChar!='!');
    free(sentence);
    return text;
}

char* generateText(char** text, int textSize){
    char* newText = calloc(1, sizeof(char));

    for (int i = 0; i < textSize; ++i) {
        newText = realloc(newText, strlen(newText) + strlen(text[i]) + 2);
        strcat(newText, text[i]);
        strcat(newText, "\n");
    }
    return newText;
}
