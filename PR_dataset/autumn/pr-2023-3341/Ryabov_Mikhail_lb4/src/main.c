#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TEXT_SIZE 1000
#define KEY_SIZE 30

int compare(const void *a, const void *b);
int bcompare(const void* key, const void* b);
char** split_text(char *text, int n_words);
void result(char **words, int n_words, char *str);
int count_words(char* sentense);

int main() {

    char text[TEXT_SIZE];
    char key[KEY_SIZE];

    fgets(text, sizeof(text), stdin);
    scanf("%s", key);

    int n_words = count_words(text);
    char **words = split_text(text, n_words);
    result(words, n_words, key);

    return 0;
}

int count_words(char* sentense){
    int i = 0, counter = 0;
    while (sentense[i] != '\n') {
        if (sentense[i] == ' ') {
            counter++;
        }
        i++;
    }
    
    return counter+1;
}

int compare(const void *a, const void *b) {
    return strcmp(*(const char **)a, *(const char **)b);
}

int bcompare(const void* key, const void* b){
    const char *k = (const char*)key;
    const char **s = (const char**)b;
    return strcmp(k, *s);
}

char** split_text(char *text, int n_words) {
    char** words = malloc(sizeof(char*) * n_words);
    char *word = strtok(text, " .");
    int size = 0;
    while (word != NULL) {
        words[size] = strdup(word);
        word = strtok(NULL, " .");
        size++;
    }
    return words;
}   

void result(char **words, int n, char *str) {
    qsort(words, n, sizeof(char *), compare);
    char* exist = bsearch(str, words, n, sizeof(char*), bcompare);

    if (exist != NULL) {
        printf("exists");
    } else { 
        printf("doesn't exist");
    }

}
