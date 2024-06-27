#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <strings.h>

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
    char pr_c = '0';
    
    int str_cap = BLOCK;
    int str_size = 0;
    
    int arr_cap = BLOCK;
    int arr_size = 0;
    
    char** text = malloc(sizeof(char*) * BLOCK);
    char* str = malloc(sizeof(char*) * BLOCK);
    
    while ((c != '\n') || (pr_c != '\n')) {
        if ((str_size == 0) && (isspace(c))) {
            pr_c = c;
            c = getchar();
            continue;
        }
        str = append_chr(str, &str_cap, str_size++, c);
        if (c == '.') {
            str = append_chr(str, &str_cap, str_size++, '\0');
            text = append_str(text, &arr_cap, arr_size++, str);
            str_cap = BLOCK;
            str_size = 0;
            str = malloc(sizeof(char*) * BLOCK);
        }
        pr_c = c;
        c = getchar();
    }
    
    *array_size =  arr_size;
    return text;
}

void pr_text(char** text, int size) {
    for (int i = 0; i < size; i++) {
        printf("%s\n", text[i]);
    }
}

int is_time_format(char* str) {
    if (strlen(str) != 8) {
        return 0;
    }
    for (int i = 0; i < 8; i++) {
        if ((i == 2) || (i == 5)) {
            if (str[i] != '-') {
                return 0;
            }
        }
        else {
            if(!isdigit(str[i])) {
                return 0;
            }
        }
    }
    return 1;
}

int cacl_time(char* str) {
    int total = 0;
    char* copy = malloc(sizeof(char) * (strlen(str)+1));
    strcpy(copy, str);
    char* sep = strtok(copy, " ,");
    while (sep != NULL) {
        if (sep[strlen(sep)-1] == '.') {
            sep[strlen(sep)-1] = '\0';
        }
        
        if (is_time_format(sep)) {
            int h, m, s;
            sscanf(sep, "%d-%d-%d", &h, &m, &s);
            total += s + 60 * (m + 60 * h);
        }
        sep = strtok(NULL, " ,");
        
    }
    free(copy);
    return total;
}



int t_comp(const void* str1, const void* str2) {
    return cacl_time(*((char**)str2)) - cacl_time(*((char**)str1));
}

void t_sort(char** text, int size) {
    qsort(text, size, sizeof(char*), t_comp);
}

void rm_repeats(char** text, int* s) {
    int size = *s;
    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (!strcasecmp(text[i], text[j])) {
                free(text[j]);
                for (int h = j; h < size - 1; h++) {
                    text[h] = text[h+1];
                }
                
                size = size - 1;
                text[size] = NULL;
                j--;
            }
            
        }
    }
    *s = size;
}

int count_words(char* str) {
    int c = 1;
    for (int i = 0; i < strlen(str) - 1; i++) {
        if ((str[i] == ' ' || str[i] == ',') && !(str[i+1] == ' ' || str[i+1] == ',' || str[i+1] == '.')) {
            c++;
        }
    }
    return c;
}

void pr_limited(char** text, int s) {
    for (int i = 0; i < s; i++) {
        if (count_words(text[i]) > 2 && count_words(text[i]) < 7) {
            printf("%s\n", text[i]);
        }
    }
}

int is_vowel(char c) {
    return (tolower(c) == 'a') || (tolower(c) == 'e') || (tolower(c) == 'o') || (tolower(c) == 'y') || (tolower(c) == 'u') || (tolower(c) == 'i');
}

void lower_to_upper(char** text, int s) {
    for (int i = 0; i < s; i++) {
        for (int j = 0; j < strlen(text[i]); j++) {
            if (!is_vowel(text[i][j]) && isalpha(text[i][j]) && islower(text[i][j])) {
                text[i][j] = toupper(text[i][j]);
            }
        }
    }
}

void rm_some_str(char** text, int* s) {
    int size = *s;
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += count_words(text[i]);
    }
    for (int i = 0; i < size; i++) {
        if (count_words(text[i]) * size > sum) {
            free(text[i]);
            for (int h = i; h < size - 1; h++) {
                text[h] = text[h+1];
            }
                
            size = size - 1;
            text[size] = NULL;
            i--;
        }
    }
    *s = size;
}



char** sep(char* str, int* s) {
    char** res = malloc(BLOCK * sizeof(char*));
    int cap = BLOCK;
    int size = 0;
    
    
    char* copy = malloc(sizeof(char) * (strlen(str)+2));
    strcpy(copy, str);
    int len = strlen(copy);
    copy[len-1] = ' ';
    copy[len] = '.';
    copy[len+1] = '\0';
    
    char* sep = strtok(copy, " ,");
    while (sep != NULL) {
        
        char* entry = malloc(sizeof(char) * (strlen(sep)+1));
        strcpy(entry, sep);
        
        res = append_str(res, &cap, size++, entry);
        sep = strtok(NULL, " ,");
    }
    free(copy);
    *s = size;
    return res;
    
}

void rm_words(char** text, int size, int* r_size) {
    char** res = malloc(BLOCK * sizeof(char*));
    int cap = BLOCK;
    int cur = 0;
    
    
    for (int i = 0; i < size; i++) {
        int size1 = 0;
        char** seped1 = sep(text[i], &size1);
        for(int j = 0; j < size1; j++) {
            int f = 1;
            for (int h = 0; h < size; h++) {
                int size2 = 0;
                char** seped2 = sep(text[h], &size2);
                for (int k = 0; k < size2; k++) {
                    if (((i==h)&&(j==k)) || seped1[j][0] == '.') {
                        continue;
                    }
                    
                    if (!strcasecmp(seped1[j], seped2[k])) {
                        f = 0;
                    }
                }
            }
            
            if (f == 1) {
                res = append_str(res, &cap, cur++, seped1[j]);
            }
        }
    }
    
    int c = 0;
    
    for (int i = 0; i < cur; i++){
        
        if (c == 0 && res[i][0] == '.') {
            continue;
        }
        if (c == 0) {
            printf("%s", res[i]);
            c++;
            continue;
        }
        if (res[i][0] == '.') {
            printf(".\n");
            c = 0;
            continue;
        }
        printf(" %s", res[i]);
        c++;
    }
}

int main() {
    int size = 0;
    printf("Course work for option 4.21, created by Evdokimov Maksim.\n");
    char** text;
    int opt = -1;
    scanf("%d", &opt);
    
    switch (opt) {
        case 0:
            text = read_text(&size);
            rm_repeats(text, &size);
            pr_text(text, size);
            break;
        
        case 1:
            text = read_text(&size);
            rm_repeats(text, &size);
            t_sort(text, size);
            pr_text(text, size);
            break;
        
        case 2:
            text = read_text(&size);
            rm_repeats(text, &size);
            pr_limited(text, size);
            break;
        
        case 3:
            text = read_text(&size);
            rm_repeats(text, &size);
            lower_to_upper(text, size);
            pr_text(text, size);
            break;
        
        case 4:
            text = read_text(&size);
            rm_repeats(text, &size);
            rm_some_str(text, &size);
            pr_text(text, size);
            break;
        
        case 5:
            printf("1. Sort all the text by decreasing the total time specified in the line. The time in the line is indicated as the word HH-MM-SS. For example, for the line abs 12-03-13 p 01-10-23 02-32-24 the total time is 15-46-00. If a sentence does not indicate the time, then the total time for it is 00-00-00.\n2. Print all sentences in which the number of words is more than 2 and less than 7.\n3. In the entire text, replace lowercase consonants with capital ones. \n4. Delete all sentences in which the number of words is greater than the average number of words in sentences.");
            break;
            
        case 9:
            text = read_text(&size);
            rm_repeats(text, &size);
            int r = 0;
            rm_words(text, size, &r);
            break;
        default:
            printf("Error: Incorrect option.");
            break;
    }
    
}