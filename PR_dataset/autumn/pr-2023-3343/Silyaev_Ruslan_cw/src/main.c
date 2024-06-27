#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> 
#include <locale.h> 

#define STEP_SIZE 50
#define SENTECSE_SIZE 10
#define WORD_SIZE 5

//ОБЩИЕ ФУНКЦИИ

int comp (const char *i, const char *j){
    return (int)*i - (int)*j;
}

int average(const char* i){
    char* dupe = calloc(strlen(i) + 1, sizeof(char));
    strcpy(dupe, i);
    char* pch = strtok(dupe," ,.");
    int ave = 0;
    int cnt = 0;
    while (pch != NULL){
        int ok = 1;
        for(size_t n = 0; n < strlen(pch); n++){
            if(isalpha(pch[n])){
                ok = 0;
                break;
            }
        }
        if(ok){
            ave += atoi(pch);
            cnt++;
        }
        pch = strtok (NULL, " ,.");
    }
    return cnt > 0 ? (ave/cnt) : 0;
}

int cmp (const char* i, const char* j){
    const char* texti = *(char**)i;
    const char* textj = *(char**)j;
    int averagei = average(texti);
    int averagej = average(textj);
    if (averagei < averagej) {
        return -1;
    } else if (averagei > averagej) {
        return 1;
    } else {
        return 0;
    }
}

//СЧИТЫВАНИЕ ТЕКСТА И РАЗБИЕНИЕ НА ПРЕДЛОЖЕНИЯ
//ЗАДАНИЕ №0

char* readText(int* countOfSentences){
    int sizeOfText = STEP_SIZE;
    char* text = calloc(sizeOfText, sizeof(char));
    int symbols = 0;
    int countOfN = 0;
    char ch;
    while((ch = getchar())) {
        if(ch == '\n'){
            countOfN++;
            if (countOfN == 2)
                break;
            continue;
        }

        countOfN = 0;

        if (ch=='.')
            *countOfSentences = *countOfSentences + 1;

        if (symbols >= sizeOfText-1){
            sizeOfText += STEP_SIZE;
            text = (char*)realloc(text, sizeOfText);
        }
        text[symbols++] = ch;
    }
    text = (char*)realloc(text, sizeof(char)*symbols+1);
    text[symbols] = '\0';
    return text;
}

char** textRebuild(char* textOld, int countOfSentences, int* countOfSentencesNew){
    char** textV1 = malloc(sizeof(char*) * countOfSentences);
    int symbolsNew = 0;
    for(int i = 0; i < countOfSentences; i++){
        textV1[i] = malloc(sizeof(char) * SENTECSE_SIZE);
        int sizeSplitted = SENTECSE_SIZE;
        int symbolsSplitted = 0;
        while(textOld[symbolsNew]!='.'){
            if(symbolsSplitted > SENTECSE_SIZE-2){
                sizeSplitted += SENTECSE_SIZE;
                textV1[i] = (char*)realloc(textV1[i], sizeSplitted);
            }
            textV1[i][symbolsSplitted++] = textOld[symbolsNew++];
        }
        textV1[i][symbolsSplitted++] = textOld[symbolsNew++];
        textV1[i][symbolsSplitted] = '\0';
        char* ptrNew = textV1[i];
        while(*ptrNew == ' '){
            ptrNew++;
        }
        memmove(textV1[i], ptrNew, strlen(ptrNew)+1);
    }
    char** textV2 = malloc(sizeof(char*) * countOfSentences);
    textV2[0] = textV1[0];
    int countNew = 1;
    for(size_t i = 1; i < countOfSentences; i++){
        int ok = 1;
        char* textV1Copy = calloc((strlen(textV1[i])+1), sizeof(char));
        strcpy(textV1Copy, textV1[i]);
        for(size_t k = 0; k < (strlen(textV1Copy)); k++){
            textV1Copy[k] = tolower(textV1Copy[k]);
        }
        for(size_t j = 0; j < countNew; j++){
            char* textV2Copy = calloc((strlen(textV2[j])+1), sizeof(char));
            strcpy(textV2Copy, textV2[j]);
            for(size_t n = 0; n < (strlen(textV2Copy)); n++){
                textV2Copy[n] = tolower(textV2Copy[n]);
            }
            if(strcmp(textV1Copy, textV2Copy)==0){
                ok = 0;
            }
            free(textV2Copy);
        }
        if(ok){
            textV2[countNew++] = textV1[i];
        }
        free(textV1Copy);
    }
    *countOfSentencesNew = countNew;
    return textV2;
}

char** readAndRebuild(int* len){
    int lenText = 0;
    char* text = readText(&lenText);
    int lenTextNew;
    char** textNew = textRebuild(text, lenText, &lenTextNew);
    *len = lenTextNew;
    return textNew;
}

//ЗАДАНИЕ №1

char* scanPattern(){
    char* pattern = malloc(WORD_SIZE);
    int symbols = 0;
    int sizeOfPattern = WORD_SIZE;
    char ch;
    while((ch = getchar())) {
        if(ch == '\n'){
            break;
        }
        if (symbols >= sizeOfPattern-1){
            sizeOfPattern += STEP_SIZE;
            pattern = (char*)realloc(pattern, sizeOfPattern);
        }
        pattern[symbols++] = tolower(ch);
    }
    pattern[symbols] = '\0';
    return pattern;
}

void wordDelete(char *str, int pos, int count) {
    int len = strlen(str);
    for(size_t j = 0; j < count; j++){
        for(size_t i = pos; i < len - 1; i++) {
            str[i] = str[i + 1];
        }
    }
    str[len - count] = '\0';
}

char** deleteWord(char** text, int* len, char* pattern){
    for(size_t i = 0; i < *len; i++){
        for(size_t j = 0; j < strlen(text[i]); j++){
            int ok = 1;
            for(size_t k = 0; k < strlen(pattern); k++){
                if(tolower(text[i][j+k])!=pattern[k]){
                    ok = 0;
                }
            }
            if(ok){
                wordDelete(text[i], j, strlen(pattern));
            }
        }
    }
    char** text1 = calloc(*len, sizeof(char*));
    int cnt = 0;
    for(size_t i = 0; i < *len; i++){
        int ok = 0;
        for(size_t j = 0; j < strlen(text[i]); j++){
            if(isalpha(text[i][j])){
                ok = 1;
            }
        }
        if(ok){
            text1[cnt] = calloc((strlen(text[i]))+1, sizeof(char));
            strcpy(text1[cnt++], text[i]);
        }
    }    
    return text1;
}

//ЗАДАНИЕ №2

void upperSort(char** text, int len){
    for(size_t i = 0; i < len; i++){
        int cnt = 0;
        char* upperCase = calloc(strlen(text[i]), sizeof(char));
        for(size_t j = 0; j < strlen(text[i]); j++){
            if(isupper(text[i][j]) && isalpha(text[i][j])){
                upperCase[cnt++] = text[i][j];
            }
        }
        upperCase[cnt] = '\0';
        if(strlen(upperCase)==0){
            free(upperCase);
            continue;
        }
        qsort(upperCase, strlen(upperCase), sizeof(upperCase[0]), (int(*) (const void *, const void *)) comp);
        for(size_t k = 0; k < strlen(upperCase); k++){
            if(k==strlen(upperCase)-1){
                printf("%c\n", upperCase[k]);
            }else{
                printf("%c ", upperCase[k]);
            }
        }   
        free(upperCase);
    }
}

//ЗАДАНИЕ №3

char** sortAverageDigit(char** text, int len){
    qsort(text, len, sizeof(text[0]), (int(*) (const void*, const void*)) cmp);
    return text;
}

//ЗАДАНИЕ №4

char** deleteLowercase(char** text, int* len){
    char** text4 = malloc(sizeof(char*) * *len);
    int ct = 0;
    for(size_t i = 0; i < *len; i++){
        int ok = 0;
        for(size_t j = 0; j < strlen(text[i]); j++){
            if(islower(text[i][j])){
                ok = 1;
            }
        }
        if(ok){
            text4[ct++] = text[i];
        }
    }
    *len = ct;
    return text4;
}

//ЗАДАЧА №9

char** deleteUpper(char** text, char* first, int* len){
    int sumUp = 0;
    for(size_t i = 0; i < strlen(first); i++){
        if(isupper(first[i])){
            sumUp++;
        }
    }
    char** text9v = calloc(sizeof(char*), *len);
    int len9v = 0;
    for(size_t i = 0; i < *len; i++){
        int curSum = 0;
        for(size_t j = 0; j < strlen(text[i]); j++){
            if(isupper(text[i][j])){
                curSum++;
            }
        }
        if(curSum <= sumUp){
            text9v[len9v] = calloc(sizeof(char), strlen(text[i])+1);
            text9v[len9v++] = text[i];
        }
    }
    *len = len9v;
    return text9v;
}

int main(){
    setlocale(LC_ALL, "Russian");
    printf("Course work for option 4.20, created by Ruslan Silyaev\n");
    int command;
    scanf("%d", &command);
    switch(command){
        case 0: ;
            int lenText0v;
            char** text0v = readAndRebuild(&lenText0v);
            for(size_t i = 0; i < lenText0v; i++){
                printf("%s\n", text0v[i]);
            }
            free(text0v);
            break;
        case 1: ;
            int lenText1v;
            char* pattern = scanPattern();
            char** text1v = readAndRebuild(&lenText1v);
            text1v = deleteWord(text1v, &lenText1v, pattern);
            for(size_t i = 0; i < lenText1v; i++){
                printf("%s\n", text1v[i]);
            }
            free(text1v);
            break;
        case 2: ;
            int lenText2v;
            char** text2v = readAndRebuild(&lenText2v);
            upperSort(text2v, lenText2v);
            free(text2v);
            break;
        case 3: ;
            int lenText3v;
            char** text3v = readAndRebuild(&lenText3v);
            text3v = sortAverageDigit(text3v, lenText3v);
            for(size_t i = 0; i < lenText3v; i++){
                printf("%s\n", text3v[i]);
            }
            free(text3v);
            break;
        case 4: ;
            int lenText4v;
            char** text4v = readAndRebuild(&lenText4v);
            text4v = deleteLowercase(text4v, &lenText4v);
            for(size_t i = 0; i < lenText4v; i++){
                printf("%s\n", text4v[i]);
            }
            free(text4v);
            break;
        case 9: ;
            char* first = malloc(sizeof(char) * 122);
            scanf("%s", first);
            int lenText9v;
            char** text9v = readAndRebuild(&lenText9v);
            text9v = deleteUpper(text9v, first, &lenText9v);
            for(size_t i = 0; i < lenText9v; i++){
                printf("%s\n", text9v[i]);
            }
            break;
        case 5: 
            printf("0 - Вывод текста после первичной обязательной обработки\n\
                    \r1 - Во всем тексте удалить слово введенное пользователем.\n\
                    \r2 - Для каждого предложения вывести все заглавные буквы в лексикографическом порядке.\n \
                    \r3 - Отсортировать предложения по среднему арифметическому чисел в предложении.\n \
                    \r4 - Удалить все предложения в которых нет строчных букв.\n \
                    \r5 - Вывод справки о функциях, которые реализует программа.\n");
            break;
        default:
            fprintf(stderr, "Error: incorrect code for command\n");
    }
    return 0;
}
