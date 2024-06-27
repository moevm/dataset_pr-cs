#include <ctype.h>
#include <stdio.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define TEXT_SIZE 100
#define BLOCK 10

int readText(char **text){
    int size = TEXT_SIZE;
    char *buf = (char*)malloc(size*sizeof(char));
    int n=0;
    int count_sentence = 0;
    char temp;
    do{
        if(n >= size-2){
            char *t = (char*)realloc(buf, size+TEXT_SIZE);
            size+=TEXT_SIZE;
            buf = t;
        }
        temp = getchar();
        if (temp=='.' || temp=='?' || temp==';') count_sentence++;
        buf[n]= temp;
        n++;
    }while(temp!='!');
    buf[n]= '\0';
    *text = buf;
    return count_sentence;
}

int MoreOneUpper(char* sentence){
    int upper_counter = 0;
    for (int i = 0; sentence[i] != '\0'; i++) {
        if (isupper(sentence[i])) {
            upper_counter++;
            if (upper_counter > 1) {
                return 1;
            }
        }
    }
    return 0;
}

char** splitSentences(char* text, int* count_sentence) {
    int len_text = strlen(text);
    int capacity = BLOCK;
    char** new_text = (char**)malloc(capacity * sizeof(char*));
    int sentence_start = 0;
    for (int i = 0; i < len_text; i++) {
        if (text[i] == '.' || text[i] == '?' || text[i] == ';') {
            if (text[sentence_start]==' ') sentence_start++;
            int len_sentence = i - sentence_start + 2;
            char* sentence = (char*)malloc((len_sentence) * sizeof(char));
            strncpy(sentence, text + sentence_start, len_sentence - 1);
            sentence[len_sentence-1] = '\0';
            if (!MoreOneUpper(sentence)) {
                if (*count_sentence>= capacity) {
                    capacity+=BLOCK;
                    new_text = (char**)realloc(new_text, capacity * sizeof(char*));
                }
                new_text[*count_sentence] = sentence;
                (*count_sentence)++;
            } else {
                free(sentence);
            }
            sentence_start = i + 1;
        }
    }
    return new_text;
}


int main() {
    char** text = (char**)malloc(sizeof(char*));
    int number_sentences = readText(text);
    int new_number_sentences = 0;
    char** new_text = splitSentences(*text,&new_number_sentences);
    for (int i = 0; i<new_number_sentences;i++){
        for (int j = 0; j<strlen(new_text[i]);j++){
            if (new_text[i][j]!='\t' || new_text[i][j]!='\n') printf("%c",new_text[i][j]);
        }
        printf("\n");
    }
    printf("Dragon flew away!\n");
    printf("Количество предложений до %i и количество предложений после %i",number_sentences,new_number_sentences);
    return 0;
    free(text);
    free(new_text);
}
