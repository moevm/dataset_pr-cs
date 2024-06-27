#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N 10000
#define STOP_CHAR '7'

void read(char*);
int numOfSentences(char*);
int makeAnswer(char*);
void delTabsPrint(char*);
bool isEndSentence(char);

bool isEndSentence(char charOfString){
	if (charOfString == '?' || charOfString == ';' || charOfString == '.')
		return true;
	return false;
}

void delTabsPrint(char* str){
    for (int i = 0; str[i]; i++) {
        if (str[i] != '\t' && str[i] != ' ' && str[i] != '\n') {
            printf("%s\n", str + i);
            break;
        }
    }
}

void read(char* answerString){
    char* str = malloc(N*sizeof(char ));
    int i = 0;
    while (1){
        fgets(str, N, stdin);
        for (int j=0; str[j]; j++){
            answerString[i] = str[j];
            i++;
        }
        if(strstr(str,"Dragon flew away!"))
            break;
    }
    free(str);
}

int numOfSentences(char* str){
    int answer = 0;
    for (int i = 0; str[i]; i++)
        if (isEndSentence(str[i]))
            answer++;
    return answer;
}

int makeAnswer(char* mainStr){
    int sentencesCount = 0;
    bool isNotSeven = true;
    char* str = calloc(N,sizeof(char ));
    for (int i = 0, j = 0; mainStr[i]; i++){
        str[j] = mainStr[i];
        if (str[j] == STOP_CHAR)
            isNotSeven = false;
        if (isEndSentence(str[j])){
            if (isNotSeven){
                sentencesCount++;
                delTabsPrint(str);
            }
            j = -1;
            isNotSeven = true;
            str = calloc(N,sizeof(char ));
        }
        j ++;
    }
    printf("Dragon flew away!\n");
    free(str);
    return sentencesCount;
}

int main(){
    char* answerString = malloc(N*sizeof(char ));
    read(answerString);
    int numOfSentencesAfter = numOfSentences(answerString);
    int numOfSentencesBefore = makeAnswer(answerString);
    printf("Количество предложений до %d и количество предложений после %d\n", numOfSentencesAfter, numOfSentencesBefore);
    free(answerString);
    return 0;
}
