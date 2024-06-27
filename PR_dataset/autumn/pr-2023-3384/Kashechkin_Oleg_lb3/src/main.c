#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_SENTENCES 200
#define MAX_SYMBOL_IN_TEXT 10000

int main() {
    char** text = (char**)malloc(MAX_SENTENCES * sizeof(char*));
    char input[MAX_SYMBOL_IN_TEXT];
    int sentence_count = 0;

    fgets(input, sizeof(input), stdin);

    char* start = input;
    char* point = strchr(input, '.');
    char* exclamation = strchr(input, '!');
    char* question = strchr(input, '?');
    char* semicolon = strchr(input, ';');

    while ((point != NULL) || (exclamation != NULL) || (question != NULL) || (semicolon != NULL)) {
        if ((point == NULL) || (exclamation != NULL && exclamation < point)) {
            point = exclamation;
        }
        if ((point == NULL) || (question != NULL && question < point)) {
            point = question;
        }
        if ((point == NULL) || (semicolon != NULL && semicolon < point)) {
            point = semicolon;
        }

        text[sentence_count] = (char*)malloc((point - start + 2) * sizeof(char));
        strncpy(text[sentence_count], start, point - start + 1);
        text[sentence_count][point - start + 1] = '\0';
        sentence_count++;
        
        start = point + 1;
        point = strchr(start, '.');
        exclamation = strchr(start, '!');
        question = strchr(start, '?');
        semicolon = strchr(start, ';');
    }

    int original_count = sentence_count;
    int formatted_count = 0;

    for (int i = 0; i < sentence_count; i++) {
        if ((strstr(text[i], " 555 ") != NULL) || (strstr(text[i], " 555.") != NULL) || (strstr(text[i], "555 ") != NULL)) {
            formatted_count++;
            free(text[i]);
            continue;
        }

        int leading_spaces = strspn(text[i], " \t");
        printf("%s\n", text[i] + leading_spaces);
        free(text[i]);
    }

    printf("Количество предложений до %d и количество предложений после %d\n", original_count-1, original_count - formatted_count-1);
    
    free(text);
    
    return 0;
}