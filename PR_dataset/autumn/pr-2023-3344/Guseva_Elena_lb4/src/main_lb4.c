#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
 
int cmpstr(const void* a, const void* b) { 
    return strcmp(*(const char**)a, *(const char**)b); 
} 
 
int cmpstr1(const void* a, const void* b) { 
    return strcmp((const char*)a, *(const char**)b); 
} 
 
int main() { 
    char text[1001]; 
    char** words = malloc(sizeof(char*) * 1000); 
    char* true_text; 
    int len = 0; 
    char* str = malloc(31); 
     
    fgets(text, sizeof(text), stdin); 
    fgets(str, sizeof(str), stdin); 
     
    for(int i = 0; i < strlen(str); i++) { 
        if (str[i] == '\n') str[i] = '\0'; 
    } 
     
    true_text = strtok(text, " .\n\0"); 
    while (true_text != NULL) { 
        words[len++] = true_text; 
        true_text = strtok(NULL, " .\n\0"); 
    } 
     
    qsort(words, len, sizeof(char*), cmpstr); 
     
    char** res = bsearch(str, words, len, sizeof(char*), cmpstr1); 
 
    if (res != NULL) printf("exists\n"); 
    else printf("doesn't exist\n"); 
     
    free(words); 
    free(str); 
}