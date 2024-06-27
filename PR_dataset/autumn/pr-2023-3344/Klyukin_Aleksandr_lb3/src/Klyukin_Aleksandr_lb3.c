#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

int CollectingData(char **(*text),int *SentNum,int *before,int *after){
    
    int SentLen = 250;
    int column = 0;
    int string = 0;
    int CheckLine = 0;
    char letter;
    
    for(int i = 0;i < *SentNum; i++){
        ((*text))[i] = malloc(SentLen*sizeof(char));
    }
    while((letter = getchar()) != '!'){
        if (CheckLine && isspace(letter)){
            continue;
        }
        if (letter != ';' && letter != '.' && letter != '?'){
            (*text)[string][column] = letter;
            column++;
            CheckLine = 0;
        }
        if (letter == ';' || letter == '.' || letter =='?'){
            (*text)[string][column] = letter;
            (*before)++;
            if (letter == '?'){
                (*text)[string] = malloc(SentLen*sizeof(char));
            }
            else{
                (*after)++;
                string++;
            }
            column = 0;
            CheckLine = 1;
        }
        if (SentLen - column == 1){
            SentLen+=25;
            (*text)[string] = realloc((*text)[string], SentLen*sizeof(char));
        }
        if (*SentNum - string == 1){
            *SentNum+=25;
            (*text) = realloc((*text), *SentNum*sizeof(char*));
            for (int i = *SentNum-25; i<*SentNum;i++){
                (*text)[i] = malloc(SentLen*sizeof(char));
            }
        }
    }
    (*text)[string][column] = '!';
    (*text)[string][column+1] = '\0';
    return string;
}

int main()
{
    int SentNum = 25;
    int before = 0;
    int after = 0;
    char** text = malloc(SentNum*sizeof(char*));
    int exactlyNum = CollectingData(&text, &SentNum, &before, &after);
    for(int string = 0; string < exactlyNum+1; string++){
        printf("%s\n",text[string]);
        free(text[string]);
    }
    free(text);
    printf("Количество предложений до %d и количество предложений после %d",before,after);
    return 0;
}
