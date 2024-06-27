#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void* word1_, const void* word2_) {
    char* word1 = *((char**)word1_);
    char* word2 = *((char**)word2_);
    return strcmp(word1, word2);
}

int binary_search(char** arr, int len, char* word) {
    int left = 0;
    int right = len - 1;
    while (left <= right) {
        int mid = (left + right) / 2;
        int cmp = strcmp(arr[mid], word);
        if (cmp == 0) {
            return mid;
        }
        else if (cmp < 0) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }
    return -1;
}

int main()
{
    char* text = malloc(sizeof(char) * 1001);
    char* input_word = malloc(sizeof(char) * 100);
    char symbol;
    int word_count = 0;
    fgets(text, 1001, stdin);
    text[strlen(text) - 1] = '\0';
    fgets(input_word, 100, stdin);
    input_word[strlen(input_word) - 1] = '\0';
    char** words = malloc(sizeof(char*) * 1000);
    char* word = malloc(sizeof(char) * 100);
    word = strtok(text, " .'");
    while (word != NULL) {
        word[strlen(word) - 1] = '\0';
        words[word_count] = malloc(sizeof(char) * 100);
        strcpy(words[word_count], word);
        word = strtok(NULL, " .");
        word_count++;
    }
    qsort(words, word_count, sizeof(char*), cmp);
    if (binary_search(words, word_count, input_word) != -1)
        printf("exists");
    else printf("doesn't exist");
    return 0;
}