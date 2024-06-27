#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include <ctype.h>


char* toLowerCase(char* str) {
    char* tStr = (char*)malloc((strlen(str) + 1) * sizeof(char));
    strcpy(tStr, str);
    for (int i = 0; tStr[i] != '\0'; ++i) {
        tStr[i] = tolower(tStr[i]);
    }
    return tStr;
}

char* removeDuplicateSentences(char* text) {
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;

    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        char* temp = sentence;
        while (*temp == ' ' || *temp == '\n') {
            temp++;
        }
        strcpy(sentences[count], temp);
        count++;
        sentence = strtok(NULL, ".");
    }

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (sentences[i] != NULL && sentences[j] != NULL && strcmp(toLowerCase(sentences[i]), toLowerCase(sentences[j])) == 0) {
                free(sentences[j]);
                sentences[j] = NULL;
            }
        }
    }

    char* res = (char*)malloc(1);
    res[0] = '\0';

    for (int i = 0; i < count; i++) {
        if (sentences[i] != NULL) {
            res = realloc(res, (strlen(res) + strlen(sentences[i]) + 2) * sizeof(char));
            strcat(res, sentences[i]);
            strcat(res, ".");
            free(sentences[i]);
        }
    }
    free(sentences);
    return res;
}

int Timefider(char* text) {
    char* tt = (char*)malloc((strlen(text) + 1) * sizeof(char));
    strcpy(tt,text);
    char* token;
    int sumtime = 0;
    int h = 0;
    int m = 0;
    int s = 0;

    token = strtok(tt, ", ,");
    if (token == NULL) {
        return 0;
    }
    for (int i = 0; token != NULL; i++) {
        int x;
        int y;
        int t;
        if (sscanf(token, "%d-%d-%d", &x, &y, &t)) {
            h = h + x;
            m = m + y;
            s = s + t;
        }
        token = strtok(NULL, ", ,");
    }
    sumtime = (h * 3600) + (m * 60) + s;
    free(tt);
    return sumtime;
}

int compareTimes(const void *a, const void *b) {
    char *strA = *(char **)a;
    char *strB = *(char **)b;

    int timeA = Timefider(strA);
    int timeB = Timefider(strB);

    return timeB - timeA;
}

void sortStringsByTime(char **text, int count) {
    qsort(text, count, sizeof(char *), compareTimes);
}

int wordcnt(char* text) {
    int cnt = 0;
    char* tt = (char *)malloc((strlen(text) + 1) * sizeof(char));
    strcpy(tt,text);
    char* slice = strtok(tt,", ,.");
    while(slice != NULL){
        slice = strtok(NULL,", ,.");
        cnt++;
    }
    free(tt);
    return cnt;
}

int dotcnt(char* text) {
    int dot = 0;
    char* tt = malloc((strlen(text) + 1) * sizeof(char));
    strcpy(tt,text);
    char* slice = strtok(tt,".");
    while(slice != NULL){
        slice = strtok(NULL,".");
        dot++;
    }
    free(tt);
    return dot;
}

int firstline(){
    int a;
    char b;
    scanf("%d%c", &a, &b);
    return a;
}

void duplsen(char* text,int number){
    for (int i = 0; i < number - 1; i++){
        printf("%s ",text);
    }
    printf("%s.\n",text);
}

int base() {
    printf("Course work for option 4.21, created by Mikhail Lysikov.\n");
    int a;
    char q;
    if (scanf("%d%c", &a, &q))
        return a;
    else
        return -1;
}

char* input() {
    char *str = (char *)malloc(1 * sizeof(char));
    int size = 1;
    int index = 0;
    int newline_count = 0;
    char c;

    while (newline_count < 2) {
        c = getchar();
        if (c == '\n') {
            newline_count++;
        } else {
            newline_count = 0; 
        }

        str[index] = c;
        index++;
        str = (char *)realloc(str, (size + 1) * sizeof(char));
        size++;
    }
    str[index - 2] = '\0'; 
    return str;
}

char replacetoup(char c) {
    if ((isalpha(c)) && !(strchr("qeyuioa",c))) return toupper(c);
    else return c;
}

void option0(char* text) {    
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;
    
    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        if(*sentence == '\n') {
            memmove(sentence, sentence + 1, strlen(sentence));
        }
        strcpy(sentences[count], sentence);
        count++;
        sentence = strtok(NULL, ".");
    }
    for (int i = 0; i < count; i++) {
        if (sentences[i]!= NULL && strlen(sentences[i]) > 1)
            printf("%s.\n", sentences[i]);
        if (sentences[i]!= NULL)
            free(sentences[i]);
    }
    free(sentences);
}

void option1(char* text){
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;
    
    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        if(*sentence == '\n') {
            memmove(sentence, sentence + 1, strlen(sentence));
        }
        strcpy(sentences[count], sentence);
        count++;
        sentence = strtok(NULL, ".");
    }
    sortStringsByTime(sentences, count);
    for (int i = 0; i < count; i++){
        if (sentences[i]!= NULL && strlen(sentences[i]) > 1)
            printf("%s.\n",sentences[i]);
        if (sentences[i]!= NULL)
            free(sentences[i]);
    }
    free(sentences);
}

void option2(char* text){
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;

    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        if(*sentence == '\n') {
            memmove(sentence, sentence + 1, strlen(sentence));
        }
        strcpy(sentences[count], sentence);
        count++;
        sentence = strtok(NULL, ".");
    }

    for (int i = 0; i < count; i++) {
        if (sentences[i] != NULL && (wordcnt(sentences[i]) < 3 || wordcnt(sentences[i]) > 7)) {
            free(sentences[i]);
            sentences[i] = NULL;
        }
    }
    for (int i = 0; i < count; i++){
        if (sentences[i]!= NULL && strlen(sentences[i]) > 1){
            printf("%s.\n",sentences[i]);
        }
        if (sentences[i]!= NULL)
            free(sentences[i]);
    }
    free(sentences);
}

void option3(char* text){
    for (int i = 0; i < strlen(text); i++){
        text[i] = replacetoup(text[i]);
    }
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;

    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        if(*sentence == '\n') {
            memmove(sentence, sentence + 1, strlen(sentence));
        }
        strcpy(sentences[count], sentence);
        count++;
        sentence = strtok(NULL, ".");
    }
    for (int i = 0; i < count; i++){
        if(strlen(sentences[i]) > 1)
            printf("%s.\n",sentences[i]);
        if (sentences[i]!= NULL)
            free(sentences[i]);
    }
    free(sentences);
}

void option4(char* text){
    int totalSentences = dotcnt(text);
    int totalWords = wordcnt(text);
    int wordavr = totalWords / totalSentences;
    
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;

    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        if(*sentence == '\n') {
            memmove(sentence, sentence + 1, strlen(sentence));
        }
        strcpy(sentences[count], sentence);
        count++;
        sentence = strtok(NULL, ".");
    }

    for (int i = 0; i < count; i++) {
        if (sentences[i] != NULL && (wordcnt(sentences[i]) > wordavr)) {
            free(sentences[i]);
            sentences[i] = NULL;
        }
    }
    
    for (int i = 0; i < count; i++){
        if (sentences[i]!= NULL && strlen(sentences[i]) > 1)
            printf("%s.\n",sentences[i]);
        if (sentences[i]!= NULL)
            free(sentences[i]);
    }
    free(sentences);
}

void option8(char* text,int number){
    char* sentence = strtok(text, ".");
    char** sentences = NULL;
    int count = 0;

    while (sentence != NULL) {
        sentences = realloc(sentences, (count + 1) * sizeof(char*));
        sentences[count] = (char*)malloc((strlen(sentence) + 1) * sizeof(char));
        char* temp = sentence;
        while (*temp == ' ' || *temp == '\n') {
            temp++;
        }
        strcpy(sentences[count], temp);
        count++;
        sentence = strtok(NULL, ".");
    }

    for (int i = 0; i < count; i++) {
        for (int j = i + 1; j < count; j++) {
            if (sentences[i] != NULL && sentences[j] != NULL && strcmp(toLowerCase(sentences[i]), toLowerCase(sentences[j])) == 0) {
                free(sentences[j]);
                sentences[j] = NULL;
            }
        }
    }
    
    for (int i = 0; i < count; i++){
        if ((sentences[i] != NULL) && (strlen(sentences[i]) > 1)){
            duplsen(sentences[i],number);    
        } 
    }
    free(sentences);
}

int main() {
    int o = base();
    int number;
    char *text0, *text1, *text2, *text3, *text4, *text8;
    switch (o) {
        case 0:
            text0 = input();
            text0 = removeDuplicateSentences(text0);
            option0(text0);
            break;
        case 1:
            text1 = input();
            text1 = removeDuplicateSentences(text1);
            option1(text1);
            break;
        case 2:
            text2 = input();
            text2 = removeDuplicateSentences(text2);
            option2(text2);
            break;
        case 3:
            text3 = input();
            text3 = removeDuplicateSentences(text3);
            option3(text3);
            break;
        case 4:
            text4 = input();
            text4 = removeDuplicateSentences(text4);
            option4(text4);
            break;
        case 8:
            number = firstline();
            text8 = input();
            option8(text8,number);
            break;
        case 5:
            printf("option 0 deletes duplicates.\n");
            printf("option 1 sorts by time.\n");
            printf("option 2 prints all sentences wich have more than 2 words and least then 7.\n");
            printf("option 3 makes all consonants upper case.\n");
            printf("option 4 prints all sentences wich have less then averege word per sentense ratio.\n");
            break;
        case -1:
            printf("incorrect input\n");
            break;
        default:
            printf("incorrect input\n");
            break;
    }
    return 0;
}
