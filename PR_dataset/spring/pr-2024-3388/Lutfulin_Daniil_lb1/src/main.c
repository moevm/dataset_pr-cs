#include <stdio.h>
#include <regex.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#define STRING_SIZE 100
#define STR_END '\0'
#define REGEX_STRING "([A-Za-z0-9_]+)@[A-Za-z0-9_-]+\\: ?\\~ ?\\# (.+)\n"

void match_and_print(char* cur_str, regex_t* regex_compiled, size_t *count){
    size_t max_groups = 3;
    regmatch_t group_array[max_groups];
    if(regexec(regex_compiled, cur_str, max_groups, group_array, 0) == 0){
        (*count)++;

        int name_len = group_array[1].rm_eo-group_array[1].rm_so+1;
        char name[name_len];
        for (int i = 0; i < name_len;i++){
                name[i] = cur_str[i+group_array[1].rm_so];
            }
        name[name_len-1] = STR_END;

        int command_len = group_array[2].rm_eo-group_array[2].rm_so+1;
        char command[command_len];
        for (int i = 0; i < command_len;i++){
                command[i] = cur_str[i+group_array[2].rm_so];
            }
        command[command_len-1] = STR_END;

        if((*count)==1){
            printf("%s - %s", name, command);
        }else{
            printf("\n%s - %s", name, command);
        }
    }
}


void print_commands(regex_t *regex_compiled){
    char* cur_str;
    cur_str=(char*)malloc(STRING_SIZE*sizeof(char));
    size_t count = 0;
    while(!strstr(cur_str,"Fin.")){
        if(fgets(cur_str, STRING_SIZE, stdin)==NULL){
            printf("Error:can't read file");
            exit(1);
        }
        match_and_print(cur_str, regex_compiled,&count);
    }
    free(cur_str);
}

int main(){
    char* regex_string = REGEX_STRING;
    regex_t regex_compiled;
    if(regcomp(&regex_compiled, regex_string, REG_EXTENDED)){
        printf("Error: can't compile regex");
        exit(1);
    }
    print_commands(&regex_compiled);
    regfree(&regex_compiled);
    return 0;
}
