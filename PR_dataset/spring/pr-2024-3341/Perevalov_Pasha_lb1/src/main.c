#include <string.h> 
#include <regex.h> 
#include <stdio.h> 
#include <stdlib.h> 
 
const char* REGEX_PATTERN = "(\\w+)@(\\w|-)+: ?~ ?# (.*)"; 
 
void get_text(char**); 
void checking(char*, regex_t); 
void output(char*, regmatch_t*); 
 
void get_text(char** text) { 
    int capacity = 1, len = 0; 
    char symbol = getchar(); 
    while (symbol != '\n') { 
    if (len + 1 >= capacity) { 
        capacity = capacity * 2; 
        (*text) = (char*)realloc(*text, capacity * sizeof(char)); 
    } 
    (*text)[len++] = symbol; 
    (*text)[len] = '\0'; 
    if (strcmp(*text, "Fin.") == 0) break; 
        symbol = getchar(); 
    } 
} 
 
void checking(char* text, regex_t pattern) { 
    regmatch_t group[4]; 
    if (regexec(&pattern, text, 4, group, 0) == 0) { 
        output(text, group); 
    } 
} 
 
void output(char* text, regmatch_t* group) { 
    text[group[1].rm_eo] = '\0'; 
    text[group[3].rm_eo] = '\0'; 
    printf("%s - %s\n", text + group[1].rm_so, text + group[3].rm_so); 
} 
 
int main() { 
    regex_t pattern; 
    regcomp(&pattern, REGEX_PATTERN, REG_EXTENDED); 
    char* text = NULL; 
    get_text(&text); 
    while (strcmp(text, "Fin.")) { 
        checking(text, pattern); 
        get_text(&text); 
    } 
    return 0; 
}