#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

char** read_sentences(int* count) {
    int N = 100; 
    int k = 10; 
    int amount = 0; 
    int index = 0;
    char** sentences = (char**)malloc(k * sizeof(char**)); 
    sentences[amount] = (char*)malloc(N * sizeof(char*)); 
    char symbol;
    while (1) {
        symbol = getchar();
        sentences[amount][index++] = symbol;
        if (strstr(sentences[amount], "Fin.") != NULL) {
            *count = amount;
            return sentences;
        }
        if (index >= N - 1) {
            N *= 2;
            sentences[amount] = realloc(sentences[amount], N * sizeof(char));
        }
        if (symbol == '\n') {
            amount++;
            if (amount == k) { 
                k *= 2;
                sentences = realloc(sentences, k * sizeof(char*));
            }
            sentences[amount] = (char*)malloc(N * sizeof(char));
            index = 0;
        }
    }
}

int main() {
    int count = 0;
    char** text = read_sentences(&count);
    char* regex_string = "([a-zA-Z]+:\\/\\/)?(www.)?(([a-zA-z0-9]+\\.)+[a-zA-Z0-9]+)\\/([a-zA-z0-9]+\\/)*(([a-zA-z0-9]+\\.)+[a-zA-Z0-9]+)";
    size_t max_groups = 7; 
    regex_t regex_compiled;
    regmatch_t group_array[max_groups];
    regcomp(&regex_compiled, regex_string, REG_EXTENDED);
    for (int k = 0; k < count; k++){
        if (regexec(&regex_compiled, text[k], max_groups, group_array, 0) == 0) {
            for(int j = group_array[3].rm_so; j < group_array[3].rm_eo; j++)
                printf("%c",text[k][j]);
            printf(" - ");
            for(int f = group_array[6].rm_so; f < group_array[6].rm_eo; f++)
                printf("%c",text[k][f]);
            printf("\n");
        }
    }
    regfree(&regex_compiled);
    for (int i = 0; i <= count; i++) {
        free(text[i]);
    }
    free(text);
    return 0;
}