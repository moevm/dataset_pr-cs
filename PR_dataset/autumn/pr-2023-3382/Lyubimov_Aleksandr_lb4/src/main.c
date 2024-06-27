#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Binary_search(char ** words, int count, char * word) {
    int left = 0;
    int right = count - 1;
    int mid;
    
    while (left <= right) {
        mid = (left + right) / 2;
        if (strcmp(words[mid], word) == 0) {
            return 1;
        } else if (strcmp(words[mid], word) < 0) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return 0;
}

int cmp(const void * a, const void * b) {
    char * word_a = *((char**)a);
    char * word_b = *((char**)b);
    return strcmp(word_a, word_b);
}

int main()
{
    char * text = malloc(sizeof(char) * 1001);
    char * word = malloc(sizeof(char) * 31);
    char * word_from_text = malloc(sizeof(char) * 31);
    char ** words_from_text = malloc(sizeof(char*) * 1001);
    int count = 0;
    
    for (int i = 0; i < 1001; i ++) {
        words_from_text[i] = malloc(sizeof(char) * 31);
    }
    
    fgets(text, 1001, stdin);
    fgets(word, 31, stdin);
    word[strlen(word) - 1] = '\0';
    
    word_from_text = strtok(text, " .\n");
    while (word_from_text != NULL) {
        strcpy(words_from_text[count], word_from_text);
        words_from_text[count][strlen(word_from_text) - 1] = '\0';
        word_from_text = strtok(NULL, " .\n");
        count ++;
    }
    
    qsort(words_from_text, count, sizeof(char*), cmp);
    
    if (Binary_search(words_from_text, count, word)) {
        printf("exists");
    } else {
        printf("doesn't exist");
    }
    
    return 0;
}
