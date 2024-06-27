#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

char* readText(int* length, int* countSentences) {
    int capacity = 1;
    char* text = (char*) malloc(sizeof(char));
    char ch = getchar();
    while (ch != '!') {
        text[(*length) - 1] = ch;
        if ((*length) >= capacity) {
            capacity *= 2;
            text = (char*)realloc(text, capacity * sizeof(char));
        }
        (*length) ++;
        if (ch == '.' || ch == ';' || ch == '?') {
            (*countSentences) ++;
        }
        ch = getchar();
    }
    return text;
}

void getPunctuation(char *punctuation, char *text, int length){
    int j = 0;
    for (int i = 0; i < length; i ++){
        if (text[i] == '.' || text[i] == ';' || text[i] == '?'){
            punctuation[j ++] = text[i];
        }
    }

}

char* cleanSentence(char *sentence, int length){
    char *cleanedSentence = malloc(sizeof(char) * length);
    int i = 0, j = 0, k = 0, p = i;
    if (sentence[0] == ' ' || sentence[0] == '\n'){
        i = 1;
        p = i + 1;
    }

    if(sentence[p-1] == '5' && sentence[p] == '5' && sentence[p+1] == '5' && sentence[p +2] == ' '){
        k++;
    }
    for (; p < length - 3; p ++){
        if (sentence[p-1] == ' ' && sentence[p] == '5' && sentence[p+1] == '5' && sentence[p+2] == '5' && sentence[p +3] == ' '){
            k ++;
        }
        if (sentence[p-1] == ' ' && sentence[p] == '5' && sentence[p+1] == '5' && sentence[p+2] == '5' && sentence[p +3] == '\0'){
            k ++;
        }
    }
    if (k >= 1){
        cleanedSentence[0] = '\0';
    }else{
        for (; i < length; i ++){
            if (sentence[i] != '\n'){
                cleanedSentence[j ++] = sentence[i];
            }
        }
        cleanedSentence[j] = '\0';
    }
    return cleanedSentence;

}
void separateSentences(char *text, char **separatedSentences){
    int i = 0;
    char *separators = "?.;";
    char *sentence = strtok(text, separators);
    while(sentence != NULL){
        separatedSentences[i] = malloc(sizeof(char) * strlen(sentence) + 1);
        separatedSentences[i ++] = cleanSentence(sentence, strlen(sentence) + 1);
        sentence = strtok(NULL, separators);
    }

}

void output(char **separatedSentences, char *punctuation, int countSentences){

    int m = 0;
    for (int i = 0; i < countSentences; i ++){
        int j = 0;
        if (separatedSentences[i][j] != '\0'){
            while(separatedSentences[i][j] != '\0'){
                printf("%c", separatedSentences[i][j]);
                j ++;
            }
            printf("%c\n", punctuation[i]);
        }else{
            m ++;
        }
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %d и количество предложений после %d", countSentences, countSentences - m);

}

int main(){

    int length = 1, countSentences = 0;
    char *text = readText(&length, &countSentences);
    char *punctuation = (char*)malloc(countSentences * sizeof(char));
    getPunctuation(punctuation, text, length);

    char **separatedSentences = malloc(sizeof(char*) * countSentences);
    separateSentences(text, separatedSentences);
    output(separatedSentences, punctuation, countSentences);
    
    return 0;
}