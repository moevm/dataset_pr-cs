#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#define SIZE_START 130

void print_info(){
    printf("Course work for option 4.22, created by Kuzmin Kirill.\n");
}

char** input_text(size_t* size1){
    char* str = malloc(SIZE_START*sizeof(char));
    size_t str_size = SIZE_START;
    size_t len_str = 0;
    char** text = malloc(SIZE_START*sizeof(char*));
    size_t text_size = SIZE_START;
    size_t len_text = 0;
    char last = ' ';
    while(1) {

        if (text_size == len_text) {
            text_size*=2;
            text = realloc(text, sizeof(char*) * text_size);
            }

        if (str_size == len_str+1){
            str_size*=2;
            str = realloc(str, str_size);
        }
        char c;
        c = getchar();
        if (c == last && last == '\n'){
            break;
        }
        last = c;
        if (c == '\n'){
            c = ' ';
        }
        if (len_str == 0 && isspace(c)){
            continue;
        }
        str[len_str] = c;
        len_str++;

        if (c == '.'){
            text[len_text] = str;
            len_text++;
            str[len_str++] = '\0';
            str = malloc(SIZE_START*sizeof(char));
            str_size = SIZE_START;
            len_str = 0;
        }
    }
    *size1 = len_text;
    return text;
}

size_t duplicates(char **text, size_t len){
    size_t et = 0;
    for (size_t i = 0; i < len; i++){
        int duplicate = 0;
        for (size_t j = 0; j < et; j++){
            if (strcasecmp(text[i], text[j]) == 0){
                free(text[i]);
                duplicate = 1;
                break;
            }
        }
        if (!duplicate){
            text[et++] = text[i];
        }
    }
    return et;
}

void remove_delimiter(char **text, size_t len){
    for (int i = 0; i < len; i++) {
        int count = 0;
        for (int j = 0; j < strlen(text[i]); j++) {
            if (text[i][j] == ' ' || text[i][j] == ',') {
                count++;
                if (count % 3 == 0) {
                    for (int k = j; k < strlen(text[i]); k++) {
                        text[i][k] = text[i][k + 1];
                    }
                    j--;
                }
            }
        }
    }
}

void free_text(char **text, size_t len) {
    for (size_t i = 0; i < len; i++) {
        free(text[i]);
    }
    free(text);
}

void print_text(char **text, size_t len) {
    for (size_t i = 0; i < len; i++)
        puts(text[i]);
}

int calculate_max_repeating_len(char *str) {
    size_t len = strlen(str);
    size_t max_repeat = 0;
    for (size_t i = 1; i < len; i++) {
        size_t j;
        for (j = 0; j < len - i; j++) {
            if (str[j] != str[j + i])
                break;
        }

        if (j > max_repeat) {
            max_repeat = j;
        }
    }

    return max_repeat;
}

int comparator(const void *a, const void *b){
    char *str_a = *((char**)a);
    char *str_b = *((char**)b);
    return calculate_max_repeating_len(str_b) - calculate_max_repeating_len(str_a);
}

void sort_by_repeating_max(char **text, size_t len) {
    qsort(text, len, sizeof(char*), comparator);
}

size_t delete_sentences_similar_prefix(char **text, size_t len)
{
    size_t et = 0;
    for (size_t i = 0; i < len; i++) {
        //char *tmp = strdup(text[i]);
        size_t sent_len = strlen(text[i]);
        char *tmp = malloc(sizeof(char) * (sent_len + 1));
        strcpy(tmp, text[i]);
        char *first_token = strtok(tmp, " ,.");
        char *token = first_token;
        int failed = 0;

        while (token != NULL) {
            size_t toklen = strlen(token);
            if (toklen < 3) {
                failed = 1;
                break;
            }

            if (strncmp(first_token, token, 3) != 0) {
                failed = 1;
                break;
            }

            token = strtok(NULL, " ,.");
        }

        if (!failed) {
            free(text[i]);
        }
        else {
            text[et++] = text[i];
        }

        free(tmp);
    }

    return et;
}


void dopsa(char **text, size_t len) {
    for (size_t i = 0; i < len; i++) {
        //char *tmp = strdup(text[i]);
        size_t sent_len = strlen(text[i]);
        char *tmp = malloc(sizeof(char) * (sent_len + 1));
        strcpy(tmp, text[i]);
        size_t token_i = 0;

        char *prev_token = NULL;
        char *token = strtok(tmp, " ,.");
        char *next_token = strtok(NULL, " ,.");

        while (token != NULL) {
            if (strcmp(token, "dopsa") == 0) {
                if (prev_token == NULL && next_token == NULL)
                    printf("%ld %ld\n", i, token_i);
                else if (prev_token == NULL)
                    printf("%ld %ld next %s\n", i, token_i, next_token);
                else if (next_token == NULL)
                    printf("%ld %ld prev %s\n", i, token_i, prev_token);
                else
                    printf("%ld %ld prev %s next %s\n", i, token_i, prev_token, next_token);
            }

            prev_token = token;
            token = next_token;
            next_token = strtok(NULL, " ,.");
            token_i++;
        }

        free(tmp);
    }
}

void print_help() {
    puts(
        "0 - Print preprocessed text\n"
        "1 - Find all occurrences of the word 'dopsa' and for each occurrence display the sentence number,\n"
        "    the position of the word in the sentence, and the words that come before and after it.\n"
        "2 - Remove every third delimiter.\n"
        "3 - Delete all sentences in which the first 3 characters of each word match.\n"
        "4 - Sort all sentences by the length of the maximum repeating sequence of characters in it.\n"
        "5 - Display help message."
    );
}

void det_sentenses(char **text, size_t len){
    int firstCount = 0;
    for (int i = 0; i < strlen(text[0]); i++){
        if (isdigit(text[0][i])){
            int c = text[0][i] - 48;
            firstCount = firstCount + c;
        }
        }
    for (int i = 1; i < len; i++){
            int nextCount = 0;
        for (int j = 0; j<strlen(text[i]); j++){
            if (isdigit(text[i][j])){
                int c = text[i][j] - 48;
                nextCount = nextCount + c;
            }
        }
        if (nextCount > firstCount){
                printf("(%d) %s\n", nextCount-firstCount, text[i]);
            }
    }
}

int main()
{
    print_info();

    int g;
    if (scanf("%d", &g) == 0) {
        puts("Error: failed to read option.");
        return 0;
    }

    if (g == 5) {
        print_help();
        return 0;
    }

    char** text;
    size_t len;
    text = input_text(&len);
    len = duplicates(text, len);

    switch(g){
        case 0:
            print_text(text, len);
            break;
        case 1:
            dopsa(text, len);
            break;
        case 2:
            remove_delimiter(text, len);
            print_text(text, len);
            break;
        case 3:
            len = delete_sentences_similar_prefix(text, len);
            print_text(text, len);
            break;
        case 4:
            sort_by_repeating_max(text, len);
            print_text(text, len);
            break;
        case 8:
            det_sentenses(text, len);
            break;
        default:
            puts("Error: unknown option.");
            free_text(text, len);
            return 0;
    }

    free_text(text, len);
    return 0;
}

