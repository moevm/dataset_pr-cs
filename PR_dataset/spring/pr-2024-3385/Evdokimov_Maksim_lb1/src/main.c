#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <ctype.h>
#define BLOCK 50


char** append_str(char** m, int* cap, int last, char* c) {
    if (last >= *cap) {
        *cap = *cap + BLOCK;
        m = realloc(m, *cap * sizeof(char*));
        if (m == NULL) {
            printf("Error: Out of memory!");
            exit(1);
        }
    }
    m[last] = c;
    return m;
}

char* append_chr(char* m, int* cap, int last, char c) {
    if (last >= *cap) {
        *cap = *cap + BLOCK;
        m = realloc(m, *cap * sizeof(char));
        if (m == NULL) {
            printf("Error: Out of memory!");
            exit(1);
        }
    }
    m[last] = c;
    return m;
}

char** read_text(int* array_size) {
    char c = getchar();
    
    int str_cap = BLOCK;
    int str_size = 0;
    
    int arr_cap = BLOCK;
    int arr_size = 0;
    
    char** text = malloc(sizeof(char*) * BLOCK);
    char* str = malloc(sizeof(char*) * BLOCK);
    
    while (strcmp(str, "Fin.")) {
        if ((str_size == 0) && (isspace(c))) {
            c = getchar();
            continue;
        }
        str = append_chr(str, &str_cap, str_size++, c);
        if (c == '\n') {
            str = append_chr(str, &str_cap, str_size++, '\0');
            text = append_str(text, &arr_cap, arr_size++, str);
            str_cap = BLOCK;
            str_size = 0;
            str = malloc(sizeof(char*) * BLOCK);
        }
        c = getchar();
    }
    
    *array_size =  arr_size;
    return text;
}

int main () {
    
    int group_c = 6;
    int site_name_j = 3;
    int file_name_j = 5;
    
    char* reg_str = "([a-zA-Z]+:\\/\\/)?(www\\.)?([a-zA-Z\\.]+\\.[a-zA-Z\\.]+)\\/([a-zA-Z]+\\/)*([a-zA-Z\\.]+\\.[a-zA-Z0-9\\.]+)";
    int size = 0;
    regex_t reg;
    regmatch_t match[group_c];
    
    char** text = read_text(&size);
    
    if (regcomp(&reg, reg_str, REG_EXTENDED) != 0) {
        printf("Regex compilation failed!");
        exit(2);
    }
    
    for (int i = 0; i < size; i++) {
        int res = regexec(&reg, text[i], group_c, match,0);
        if (res == 0) {
            for (int j = match[site_name_j].rm_so; j < match[site_name_j].rm_eo; j++){
                printf("%c", text[i][j]);
            }
            printf(" - ");
            for (int j = match[file_name_j].rm_so; j < match[file_name_j].rm_eo; j++){
                printf("%c", text[i][j]);
            }
            printf("\n");
        }
     }
    
    return 0;
}