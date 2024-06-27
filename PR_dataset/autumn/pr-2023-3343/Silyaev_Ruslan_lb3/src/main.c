#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define STEP_SIZE 50
#define SENTECSE_SIZE 10
 
int readText(char** textOriginal);
char** textRebuild(char* textOld, int countOfSentences);
char** delete555(char** text555, int* countOfSentences);
 
char** delete555(char** text555, int* countOfSentences){
    int countNew = 0;
    char** textEnded = malloc(sizeof(char*) * *countOfSentences);
    for(int i = 0; i < *countOfSentences; i++){
        if(!(text555[i][0]=='5' && text555[i][1]=='5' && text555[i][2]=='5' && text555[i][3]==' ') && (text555[i][strlen(text555[i])-2]!='5' && text555[i][strlen(text555[i])-3]!='5' && text555[i][strlen(text555[i])-4]!='5' && text555[i][strlen(text555[i])-5]!=' ')){
            if(strstr(text555[i], " 555 ")==NULL){
                textEnded[countNew++] = text555[i];
            }
        }
    }
    *countOfSentences = countNew;
    return textEnded;
}
 
int readText(char** textOriginal){
    int sizeOfText = STEP_SIZE;
    char* text = malloc(sizeof(char) * sizeOfText);;
    int symbols = 0;
    int countOfSentences = 1;
    do{
        if(symbols >= sizeOfText-2){
            sizeOfText += STEP_SIZE;
            char* ptr = (char*)realloc(text, sizeOfText);
            text = ptr;
        }
        text[symbols++] = getchar();
        if(text[symbols-1]=='.' || text[symbols-1]=='?' || text[symbols-1]==';'){
            countOfSentences++;
        }
    }while(text[symbols-1]!='!');
    text[symbols] = '\0';
    *textOriginal = text;
    return countOfSentences;
}
 
char** textRebuild(char* textOld, int countOfSentences){
    char** textSplitted = malloc(sizeof(char*) * countOfSentences);
    int lenOld = strlen(textOld);
    int count = 0;
    int symbolsNew = 0;
    for(int i = 0; i < countOfSentences; i++){
        textSplitted[i] = malloc(sizeof(char) * SENTECSE_SIZE);
        int sizeSplitted = SENTECSE_SIZE;
        int symbolsSplitted = 0;
        while(textOld[symbolsNew]!='.' && textOld[symbolsNew]!='?' && textOld[symbolsNew]!=';' && textOld[symbolsNew]!='!'){
            if(symbolsSplitted > SENTECSE_SIZE-2){
                sizeSplitted += SENTECSE_SIZE;
                char* ptrSplitted = (char*)realloc(textSplitted[i], sizeSplitted);
                textSplitted[i] = ptrSplitted;
            }
            textSplitted[i][symbolsSplitted++] = textOld[symbolsNew++];
        }
        textSplitted[i][symbolsSplitted++] = textOld[symbolsNew++];
        textSplitted[i][symbolsSplitted] = '\0';
        char* ptrNew = textSplitted[i];
        while(*ptrNew == ' ' || *ptrNew == '\t' || *ptrNew == '\n'){
            ptrNew++;
        }
        memmove(textSplitted[i], ptrNew, strlen(ptrNew)+1);
    }
    return textSplitted;
}
 
int main(){
    char* textOriginal;
    int countOfSentences = readText(&textOriginal);
    int countOfSentencesOld = countOfSentences;
    char** textNew = textRebuild(textOriginal, countOfSentences);
    textNew = delete555(textNew, &countOfSentences);
    for(int i = 0; i < countOfSentences; i++){
        printf("%s\n", textNew[i]);
    }
    printf("Количество предложений до %d и количество предложений после %d\n", countOfSentencesOld-1, countOfSentences-1);
    for(int i = 0; i < countOfSentences; i++){
        free(textNew[i]);
    }
    free(textNew);
    free(textOriginal);
    return 0;
}
