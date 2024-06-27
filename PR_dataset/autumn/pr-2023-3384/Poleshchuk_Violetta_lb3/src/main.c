#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char **spawn(int *len);
int findDigit(char *sentence);
void output(char **text, int textSize);
int isNumber(char *word);

int main(){
    int textSize = 0;
    char **text = spawn(&textSize);
    output(text, textSize);
    for (int i = 0; i < textSize; i++) {
        free(text[i]);
    }
    free(text);
    return 0;
}

char **spawn(int *textSize){
    int textVolume = 1;
    int sentenceVolume = 1;
    int sentenceLen = 0;
    char symbol;
    char *sentence = malloc(sizeof(char) * sentenceVolume); 
    char **text = malloc(sizeof(char*) * textVolume); 

    do{
        symbol = getchar();
        sentence[sentenceLen++] = symbol;
        
        if(sentenceVolume < sentenceLen){
            sentenceVolume *= 2;
            sentence = realloc(sentence, sizeof(char) * sentenceVolume);
        }
        
        if (symbol == '.' || symbol == ';' || symbol == '?' || symbol == '!'){
            sentence[sentenceLen] = '\0';
            if (sentence[0] == ' '){
                memmove(sentence, sentence + 1, strlen(sentence));
            }
            
            text[(*textSize)++] = strdup(sentence);
            sentenceVolume = 1;
            sentenceLen = 0;

            if (textVolume < *textSize){
            textVolume *= 2;
            text = realloc(text, sizeof(char*) * textVolume);
            }

        }

    } while (symbol != '!');
    sentence = realloc(sentence, sizeof(char) * (sentenceLen + 1));
    text = realloc(text, sizeof(char*) * (*textSize + 1));
    return text;
}   


int isNumber(char *word){
    int len = strlen(word);
    for (int i = 0; i < len; i++){
        if (!isdigit(word[i])){
            return 0;
        }
    }
    return 1;
}


int findDigit(char *sentence){
    const char *sep = " .!?;";
    char* token = strtok(strdup(sentence), sep);
    while (token != NULL){
        if (isNumber(token)){
            token = strtok(NULL, sep);
            continue;
        }
        for (int index = 1; index < strlen(token)-1; index++){
            if (isdigit(token[index])){
                return 1;
            }
        }
        token = strtok(NULL, sep);
    }
    return 0;
}


void output(char **text, int textSize){
    int textSizeAfter = 0; 
    char *sentence;
    for (int i = 0; i < textSize; i ++){
        sentence = text[i];
        if (findDigit(sentence) == 0){
            printf("%s\n", sentence);
            textSizeAfter++;
        }
    }
    printf("Количество предложений до %d и количество предложений после %d", textSize-1, textSizeAfter-1);
}