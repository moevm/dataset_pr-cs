#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define MAX_STR_SIZE 1000
#define BUFFER_SIZE 10
#define NOT_FOUND_PATH "\0"
#define START_DIR "labyrinth"
#define START_FILE "file.txt"
#define OUTPUT_FILE "result.txt"
#define NEXT_DIR_TEMLATE "%s/%s"
#define HISTORY_TEMPLATE "%s./%s\n"
#define BLACK_LIST "."
#define REQUIRED_CONTENT "Minotaur"
#define DEAD_END_VAL "Deadlock"
#define MEM_ERROR "Error: Failed to allocate memory"
#define DEAD_END_CODE 0
#define NEXT_FILES_CODE 1
#define FINISH_CODE 2
#define DIR_TYPE 4

void panic(char* message);
void realloc_str_arr(char*** str_arr_ptr, size_t len);
void free_str_arr(char** str_arr, size_t len);
void make_asnwer();
int read_file(char *file_path, char ***next_files, size_t *len);
char* find_file(char *dir_path, char *filename);
char* find_word(char *file, char *history);

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

void free_str_arr(char** str_arr, size_t len){
    for (size_t i = 0; i < len; i++)
        free(str_arr[i]);
    free(str_arr);
}

char* find_file(char *dir_path, char *filename){
    DIR *dir = opendir(dir_path);
    char *reqired_path;
    char *next_dir_path = calloc(MAX_STR_SIZE, sizeof(char));
    if(dir){
        struct  dirent *cur_dir = readdir(dir);
        while (cur_dir){; 
            if (!strcmp(cur_dir->d_name, filename))
                return dir_path;

            if (cur_dir->d_type == DIR_TYPE && !strstr(cur_dir->d_name, BLACK_LIST)){
                sprintf(next_dir_path, NEXT_DIR_TEMLATE, dir_path, cur_dir->d_name);
                reqired_path = find_file(next_dir_path, filename);

                if ((strcmp(reqired_path, NOT_FOUND_PATH))){
                    return reqired_path;
                }
            }

            cur_dir = readdir(dir);
        }
    }

    closedir(dir);

    return NOT_FOUND_PATH;
}

int read_file(char *file_path, char ***next_files, size_t *len){
    char buffer[MAX_STR_SIZE] = {'\0'};
    char commad[MAX_STR_SIZE] = {'\0'};
    char file_name[MAX_STR_SIZE] = {'\0'};

    FILE *file = fopen(file_path, "r");
    *len = 0;
    *next_files = NULL;

    if(file)
    {
        while((fgets(buffer, MAX_STR_SIZE, file)) != NULL && buffer[0] != '\n')
        {   

            sscanf(buffer, "%s", commad);
            if(!strcmp(commad, DEAD_END_VAL)){
                free_str_arr(*next_files, *len);

                return DEAD_END_CODE;
            }
            
            if(!strcmp(commad, REQUIRED_CONTENT)){
                free_str_arr(*next_files, *len);

                return FINISH_CODE;
            }

            sscanf(buffer, "%s%s", commad, file_name);
            realloc_str_arr(next_files, *len);
            (*next_files)[*len] = calloc(strlen(file_name), sizeof(char));
            sscanf(file_name, "%s", (*next_files)[(*len)++]);
        }
        fclose(file);

        return NEXT_FILES_CODE;
    }

    return DEAD_END_CODE; 
}

char* find_word(char *file, char *history){
    char **files;
    char *next_file;
    char *finally_history;
    char *current_history;
    char *current_path;
    size_t len;

    int file_status = read_file(file, &files, &len);
    
    if (file_status == DEAD_END_CODE){
        return NOT_FOUND_PATH;
    }

    if (file_status == FINISH_CODE)
        return history;
    

    current_path = calloc(MAX_STR_SIZE, sizeof(char));
    current_history = calloc(MAX_STR_SIZE, sizeof(char));
    finally_history = calloc(MAX_STR_SIZE, sizeof(char));

    for (size_t i = 0; i < len; i++){
        next_file = find_file(START_DIR, files[i]);

        sprintf(current_path, NEXT_DIR_TEMLATE, next_file, files[i]);
        sprintf(current_history, HISTORY_TEMPLATE, history, current_path);
        sprintf(finally_history, "%s", find_word(current_path, current_history));

        if (strcmp(finally_history, NOT_FOUND_PATH)){
            free(current_path);
            free(current_history);
            return finally_history;
        }
    }

    return NOT_FOUND_PATH;
}

void make_asnwer(){
    char *file_path = find_file(START_DIR, START_FILE);
    char *file = calloc(MAX_STR_SIZE, sizeof(char));
    char *start_history = calloc(MAX_STR_SIZE, sizeof(char));
    sprintf(file, NEXT_DIR_TEMLATE, file_path, START_FILE);
    sprintf(start_history, HISTORY_TEMPLATE, "", file);
    FILE *opened_file = fopen(OUTPUT_FILE, "w");

    char *answer = find_word(file, start_history);
    if(opened_file){
        fputs(answer, opened_file);
        fclose(opened_file);
    }
    free(answer);
}

int main(){
    make_asnwer();
    return 0;
}

