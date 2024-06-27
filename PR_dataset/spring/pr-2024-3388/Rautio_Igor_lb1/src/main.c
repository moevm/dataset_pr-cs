#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_SIZE 100
#define DEFAULT_STR_SIZE 5000
#define CAPTURE_GROUP_COUNT 3
#define USER_GROUP 1
#define COMMAND_GROUP 2
#define END_OF_STRING '\0'
#define REGEX_STRING "([A-z0-9_]+)@[A-z0-9_-]+\\:[ ]*~[ ]*# (.+)"
#define INPUT_END "Fin."

char** input(size_t* len);
char* get_command_and_name_if_is_root(char* str);
void print_commands(char** str_arr, size_t len);

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
        row = realloc(row, (i + 1) * sizeof(char));
        if (current_char == '\n'){
            row[i++] = END_OF_STRING;
            rows = realloc(rows, sizeof(char*)*((*len)+1));
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

char* get_command_and_name_if_is_root(char* str){
    char *answer = calloc(sizeof(char), DEFAULT_STR_SIZE);
    int regex_answer;
    int user_start, user_delta;
    int command_start, commad_delta;
    regex_t regex;
    regmatch_t match[CAPTURE_GROUP_COUNT];

    regex_answer = regcomp(&regex, REGEX_STRING, REG_EXTENDED);
    regex_answer = regexec(&regex, str, CAPTURE_GROUP_COUNT, match, 0);
    if (regex_answer == REG_NOMATCH)
        return answer;
    
    user_start = match[USER_GROUP].rm_so;
    user_delta = match[USER_GROUP].rm_eo - user_start;

    command_start = match[COMMAND_GROUP].rm_so;
    commad_delta = match[COMMAND_GROUP].rm_eo - command_start;

    sprintf(answer, "%.*s - %.*s", user_delta, str+user_start, commad_delta, str+command_start);

    regfree(&regex);

    return answer;
}

void print_commands(char** str_arr, size_t len){
    char* answer;
    size_t count = 0;
    for (int i = 0; i < len; i++){
        answer = get_command_and_name_if_is_root(str_arr[i]);
        if (answer[0] == END_OF_STRING)
            continue;
        count++;
        if (count == 1)
            printf("%s", get_command_and_name_if_is_root(str_arr[i]));
        else
            printf("\n%s", get_command_and_name_if_is_root(str_arr[i]));
        free(answer);
        free(str_arr[i]);
    }
}

int main(){
    size_t len;
    char** str_arr = input(&len);
    print_commands(str_arr, len);
    return 0;
}