#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* getText(){
    int initial_size = 10;
    char* text = calloc(initial_size, sizeof(char));
    int k = 0, c = 1;
    int ch;

    while ((ch = getchar()) != '\n') {
        text[k] = ch;
        k++;
        if (k == c * 10 - 1) {
            c++;
            initial_size = c * 10;
            text = realloc(text, initial_size * sizeof(char));
        }
    }
    if (k < initial_size) {
        text[k] = '\0';
    } else {
        initial_size++;
        text = realloc(text, initial_size * sizeof(char));
        text[k] = '\0';
    }
    return text;
}

char** Words(char* text,int* num_of_words) {
    int initial_size = 10,k=0,c=1;
    char** words = malloc(initial_size * sizeof(char*));
    char sep[]=" .,()";
    char* istr= strtok(text,sep);
    while (istr!=NULL){
        words[k]= strdup(istr);
        k++;
        istr= strtok(NULL,sep);
        if  (k==c*initial_size-1){
            c++;
            words= realloc(words,initial_size*c* sizeof(char*));
        }
    }
    words[k]=NULL;
    *num_of_words=k;
    return words;
}

int cmp(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

int main() {
    int num_of_words=0;
    char* text = getText();
    char** words = Words(text,&num_of_words);

    char* keyWord = malloc(31 * sizeof(char));
    scanf("%s", keyWord);

    qsort(words, num_of_words, sizeof(char*), cmp);
    char* p = bsearch(&keyWord, words, num_of_words, sizeof(char*), cmp);
    if (p){
        printf("exists");
    } else{
        printf("doesn't exist");
    }
    for (int i = 0; i < num_of_words; i++) {
        free(words[i]);
    }
    free(text);
    free(keyWord);

    return 0;
}


