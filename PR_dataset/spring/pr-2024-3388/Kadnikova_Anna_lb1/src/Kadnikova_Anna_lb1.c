#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ERROR "Error\n"
#define DELTA 1000
#define STR_SIZE 500
#define END_OF_STRING '\0'
#define REGEX "([A-Za-z]+:\\/\\/)?(www\\.)?([A-Za-z0-9.-]+)\\/([A-Za-z-]+\\/)*([A-Za-z0-9-]+\\.[A-Za-z0-9-]+)$"
#define END_OF_TEXT "Fin."
#define N_MATCH 6 
#define FILE_MATCH 5
#define PATH_MATCH 3

char* read_sentence()
{
    int capacity = STR_SIZE;
    int index = 0;
    char* sentence = malloc(capacity);
    char ch = getchar();
    while (1)
    {
        if (ch == '\n' || ch == EOF || ch == '\0')
        {
            break;
        }
        sentence[index++] = ch;
        if (index == capacity - 1)
        {
            capacity += DELTA;
            sentence = realloc(sentence, capacity);
        }
        ch = getchar();
    }
    sentence[index] = END_OF_STRING;
    return sentence;
}
char** read_text(int *len)
{
    int capacity = STR_SIZE;
    char** array = malloc(sizeof(char*) * capacity);
    int index=0;
    while (1)
    {
        array[index] = read_sentence();
        if (strcmp(array[index], END_OF_TEXT) == 0)
        {
            free(array[index]);
            break;
        }
        index++;
        if (index == capacity-2)
        {
            capacity += DELTA;
            array = realloc(array, sizeof(char*) * capacity);
        }
    }
    *len=index;
    return array;
}

int get_pair(char* str, char** path, char** file){
    int path_begin, path_finish, pathd;
    int file_start, file_finish, filed;
    int answer;
    regex_t regex;
    regmatch_t match[N_MATCH];

    *path = NULL;
    *file = NULL;

    answer = regcomp(&regex, REGEX, REG_EXTENDED);
    
    answer = regexec(&regex, str, N_MATCH, match, 0);
    if (answer == REG_NOMATCH)
        return 0;
    
    path_begin = match[PATH_MATCH].rm_so;
    path_finish = match[PATH_MATCH].rm_eo;
    pathd = path_finish - path_begin;

    *path = calloc(pathd + 1, sizeof(char));
    sprintf(*path, "%.*s", pathd, str + path_begin);

    if (strstr(*path, "..") || !strstr(*path, "."))
        return 0;

    if ((*path)[0] == '.' || (*path)[strlen((*path))-1] == '.')
        return 0;

    file_start = match[FILE_MATCH].rm_so;
    file_finish = match[FILE_MATCH].rm_eo;
    filed = file_finish - file_start;

    *file = calloc(filed + 1, sizeof(char));
    sprintf(*file, "%.*s", filed, str + file_start);

    regfree(&regex);

    return 1;
}

void print_answer(char** text, int len){
    char *path;
    char *file;

    for (int i = 0; i < len; i++){
        if (get_pair(text[i], &path, &file)){
            printf("%s - %s\n", path, file);                
            free(path);
            free(file);
        }
        free(text[i]);
    }
    free(text);
}

int main(){
    int len = 0;
    char** text =read_text(&len);
    print_answer(text, len);
    return 0;
}
