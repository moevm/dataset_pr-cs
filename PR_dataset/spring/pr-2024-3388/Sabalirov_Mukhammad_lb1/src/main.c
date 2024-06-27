#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define DEFAULT_STR_SIZE 5000
#define END_OF_STRING '\0'
#define MEM_ERROR "Error: Failed to allocate memory"
#define REGCOMP_ERROR "Error: The regular expression could not be completed"
#define REGFIND_ERROR "Error: Regular expression match failed"
#define URL_REGEX "([A-Za-z]+:\\/\\/)?(www\\.)?([A-Za-z0-9.-]+)\\/([A-Za-z-]+\\/)*([A-Za-z0-9-]+\\.[A-Za-z0-9-]+)$"
#define CAPTURE_GROUP_COUNT 6
#define URL_GROUP_NUMBER 3
#define FILE_GROUP_NUMBER 5
#define INPUT_END "Fin."

void panic(char* message);
void realloc_str_arr(char*** str_arr_ptr, size_t len);
void realloc_str(char** str_ptr, size_t len);
char** input(size_t* len);
int get_link_and_file(char* str, char** link, char** file);
void print_links_and_files(char** str_arr, size_t len);

void panic(char* message) {
    printf("%s\n", message);
    exit(0);
}

void realloc_str_arr(char*** str_arr_ptr, size_t len){
    if (len % BUFFER_SIZE == 0)
        *str_arr_ptr = realloc(*str_arr_ptr, sizeof(char*)*(len+BUFFER_SIZE));
    
    if(!(*str_arr_ptr))
        panic(MEM_ERROR);
}


void realloc_str(char** str_ptr, size_t len){
    if ((len % BUFFER_SIZE) == 0)
        *str_ptr = realloc(*str_ptr, (len + BUFFER_SIZE) * sizeof(char));
    
    if (!(*str_ptr))
        panic(MEM_ERROR);
}


char** input(size_t* len){
    char current_char;
    char* row = NULL;
    char** rows = NULL;
    size_t i;
    size_t input_end_len = strlen(INPUT_END);

    *len = 0;
    i = 0;
    current_char = getchar();
    while (i < input_end_len || strncmp((row+i-input_end_len), INPUT_END, input_end_len)){
        realloc_str(&row, i);
        if (current_char == '\n'){
            row[i++] = END_OF_STRING;
            realloc_str_arr(&rows, *len);
            rows[(*len)++] = strdup(row);
            free(row);
            row = NULL;
            i = 0;
        }
        else{
            row[i++] = current_char;
        }

        current_char = getchar();
    }

    free(row);
    
    return rows;
}

int get_link_and_file(char* str, char** link, char** file){
    int link_start, link_finish, link_difference;
    int file_start, file_finish, file_difference;
    int regex_answer;
    regex_t regex;
    regmatch_t match[CAPTURE_GROUP_COUNT];

    *link = NULL;
    *file = NULL;

    regex_answer = regcomp(&regex, URL_REGEX, REG_EXTENDED);
    if (regex_answer)
        panic(REGCOMP_ERROR);
    
    regex_answer = regexec(&regex, str, 6, match, 0);
    if (regex_answer == REG_NOMATCH)
        return 0;
    
    if (regex_answer)
        panic(REGFIND_ERROR);
    
    link_start = match[URL_GROUP_NUMBER].rm_so;
    link_finish = match[URL_GROUP_NUMBER].rm_eo;
    link_difference = link_finish - link_start;

    *link = calloc(link_difference + 1, sizeof(char));
    sprintf(*link, "%.*s", link_difference, str + link_start);

    if (strstr(*link, "..") || !strstr(*link, "."))
        return 0;

    if ((*link)[0] == '.' || (*link)[strlen((*link))-1] == '.')
        return 0;

    file_start = match[FILE_GROUP_NUMBER].rm_so;
    file_finish = match[FILE_GROUP_NUMBER].rm_eo;
    file_difference = file_finish - file_start;

    *file = calloc(file_difference + 1, sizeof(char));
    sprintf(*file, "%.*s", file_difference, str + file_start);

    regfree(&regex);

    return 1;
}


void print_links_and_files(char** str_arr, size_t len){
    int is_first = 1;
    char *link;
    char *file;

    for (size_t i = 0; i < len; i++){
        if (get_link_and_file(str_arr[i], &link, &file)){
            if (is_first){
                printf("%s - %s", link, file);
                is_first = 0;
            }
            else{
                printf("\n%s - %s", link, file);
            }

            free(link);
            free(file);
        }
        free(str_arr[i]);
    }

    free(str_arr);
}

int main(){
    size_t len;
    char** str_arr = input(&len);
    print_links_and_files(str_arr, len);

    return 0;
}