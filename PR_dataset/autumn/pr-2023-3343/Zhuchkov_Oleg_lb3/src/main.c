#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define N 1000
#define M 1000
#define WORD_SIZE 50

int check_words(char* sentence);
int check_word(char* word);

int main(){
    char **sentences = calloc(N, sizeof(char*));
    char *sentence;
    int i=0, j=0, count=0;
    char symbol;
    while (symbol != '!'){
        symbol = '\0';
        sentence = calloc(M, sizeof(char));
        char* sentence_ptr = sentence; 
        *(sentences + i) = sentence;
        j = 0;
        while(symbol!='.' && symbol!=';' && symbol!='?' && symbol!='!'){
            scanf("%c", &symbol);
            if (symbol == '\n') continue;
            if ((symbol == ' ' || symbol == '\t') && j == 0) continue;
            *sentence_ptr++ = symbol;
            j++;
        }
        if (!(check_words(sentence))){
            count++;
            continue;
        }
        *sentence_ptr = '\n';
        i++;
    }
    int k, l;
    for (k = 0; k < i; k++){
        sentence = *(sentences + k);
        printf("%s",sentence);
    }
    printf("Количество предложений до %d и количество предложений после %d", i+count-1, i-1);
}

int check_words(char* sentence){
    char *word = calloc(WORD_SIZE, sizeof(char));
    char *word_ptr = word;
    while (*sentence != '\0'){
        if (!isalnum(*sentence)){
            *word_ptr = '\0';
            if (!(check_word(word))) return 0;
            sentence++;
            word = calloc(WORD_SIZE, sizeof(char));
            word_ptr = word;
            continue;
        }
        *word_ptr = *sentence;
        word_ptr++;
        sentence++;
    }
    return 1;
}

int check_word(char* word){
    if (strlen(word) < 3) return 1;
    char *letter = word;
    letter++;
    while (*(letter+1) != '\0'){
        if (isdigit(*letter) && ((isalpha(*(letter-1)) || isalpha(*(letter+1)))))
            return 0;
        letter++;
    }
    return 1;
}