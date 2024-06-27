#include <regex.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdio.h> 
 
#define MAX_TEXT_SIZE 1000 
 
char** make_text(int* text_len) 
{ 
    int capacity = 10; // Initial capacity 
    char** text = malloc(capacity * sizeof(char*)); 
    if (text == NULL) { 
        exit(EXIT_FAILURE); 
    } 
 
    int index = 0; 
    do { 
        if (index == capacity) { 
            capacity *= 2; // Double the capacity 
            text = realloc(text, capacity * sizeof(char*)); 
            if (text == NULL) { 
                exit(EXIT_FAILURE); 
            } 
        } 
 
        text[index] = calloc(MAX_TEXT_SIZE, sizeof(char)); 
        if (text[index] == NULL) { 
            exit(EXIT_FAILURE); 
        } 
 
        if (fgets(text[index], MAX_TEXT_SIZE, stdin) == NULL) { 
            free(text[index]); 
            break; // Break the loop on fgets failure 
        } 
 
        index++; 
    } while (!strstr(text[index - 1], "Fin.")); 
 
    *text_len = index; 
    return text; 
} 
 
void free_text(char** text, int text_len) 
{ 
    for (int i = 0; i < text_len; i++) { 
        free(text[i]); 
    } 
    free(text); 
} 
 
int main() 
{ 
    regex_t regex; 
    int value; 
    int text_len = 0; 
    char** text = make_text(&text_len); 
 
    char* pattern = "([a-zA-Z]+://)?([w]{3}\\.)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9]+)+)/?(([a-zA-Z0-9]+/)+)?([a-zA-Z0-9-]+(\\.[a-zA-Z0-9-]+))\n$"; 
    regmatch_t match[8]; 
    value = regcomp(&regex, pattern, REG_EXTENDED); 

 
    int count = 0; 
    int count_2 = 0; 
 
    for (int i = 0; i < text_len; i++) { 
        value = regexec(&regex, text[i], 8, match, 0); 
        if (value == 0) { 
            count++; 
        } 
    } 
 
    for (int i = 0; i < text_len; i++) { 
        value = regexec(&regex, text[i], 8, match, 0); 
        if (value == 0) { 
            count_2++; 
            if (count_2 != count) { 
                printf("%.*s - %.*s\n", 
                       (int)(match[3].rm_eo - match[3].rm_so), &text[i][match[3].rm_so], 
                       (int)(match[7].rm_eo - match[7].rm_so), &text[i][match[7].rm_so]); 
            } else { 
                printf("%.*s - %.*s", 
                       (int)(match[3].rm_eo - match[3].rm_so), &text[i][match[3].rm_so], 
                       (int)(match[7].rm_eo - match[7].rm_so), &text[i][match[7].rm_so]); 
            } 
        } 
    } 
 
    regfree(&regex); 
    free_text(text, text_len); 
    return 0; 
}
