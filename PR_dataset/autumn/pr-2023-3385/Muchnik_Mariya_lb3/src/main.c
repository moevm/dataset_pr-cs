#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BLOCK_SIZE 20
#define FINAL "Dragon flew away!"

int main() {
    size_t idx = 0;
    size_t capacity = BLOCK_SIZE;
    size_t start_sentences = 0;
    size_t end_sentences = 0;
    size_t upper = 0;
    
    char ch = getchar();
    char* sentence = (char*)malloc(capacity);

    while(strcmp(sentence, FINAL)) {
        if (!((idx == 0) && ((ch == '\t') || (ch == ' ')))) sentence[idx++] = ch; 
        if (ch == '.' || ch == '?' || ch == ';') {
            start_sentences++;
            if (upper < 2){
                end_sentences++;
                sentence[idx] = '\0';
                printf("%s\n", sentence);
            }
            idx = 0;
            capacity = BLOCK_SIZE;
            upper = 0;
            free(sentence);
            sentence = (char*)calloc(capacity, sizeof(char));
        }

        if (isupper(ch)) upper++;

        if (idx == capacity-1) {
            char* ptr = sentence;
            capacity += BLOCK_SIZE;
            sentence = (char*)realloc(sentence, capacity);
            if (sentence == NULL){
                printf("Ошибка выделения памяти\n");
                free(ptr);
                exit(0);
            }
        }
        ch = getchar();
    }
    sentence[idx] = '\0';
    printf("%s\n", sentence);
    free(sentence);

    printf("Количество предложений до %ld и количество предложений после %ld", start_sentences, end_sentences);

    return 0;
}
