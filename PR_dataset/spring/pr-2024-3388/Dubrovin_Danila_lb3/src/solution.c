#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define MAX_LETTERS_COUNT 100
#define SEARCHED_FILE_BUFFER 10
#define DIR_PATH "./tmp"
#define OUTPUT_FILE_NAME "result.txt"
#define FILE_OPEN_ERROR "Error opening file\n"


void list_dir(const char *dir_path, const char *searched_file, FILE *file)
{
    DIR *dir = opendir(dir_path);
    if(dir) {
        struct  dirent *entry = readdir(dir);
        while (entry) {
            if(strcmp(entry->d_name, ".")!=0 && strcmp(entry->d_name, "..")!=0){
                char* path = (char*)malloc(strlen(dir_path) + strlen(entry->d_name) + 2);
                sprintf(path, "%s/%s", dir_path, entry->d_name);
                if (strcmp(entry->d_name, searched_file) == 0) {
                    fprintf(file, "%s\n", path);
                    break;
                }
                list_dir(path, searched_file, file);
                free(path);
            }
            entry = readdir(dir);
        }
    }
    closedir(dir);
}

void search_files(FILE *file){
    char* searched_letters = (char*)malloc(MAX_LETTERS_COUNT * sizeof(char));
    char* searched_file = (char*)malloc(SEARCHED_FILE_BUFFER * sizeof(char));
    fgets(searched_letters, MAX_LETTERS_COUNT, stdin);
    searched_letters[strlen(searched_letters)-1] = '\0';
    for(int i = 0; i < strlen(searched_letters); i++){
        snprintf(searched_file, sizeof(searched_file), "%c.txt", searched_letters[i]);
        list_dir(DIR_PATH, searched_file, file);
    }
    free(searched_file);
    free(searched_letters);
}

void file_check(FILE *file){
    if(file == NULL){
        perror(FILE_OPEN_ERROR);
        exit(1);
    }
}

int main(){
    FILE *file = fopen(OUTPUT_FILE_NAME, "w+");
    file_check(file);
    search_files(file);
    fclose(file);
    return 0;
}
