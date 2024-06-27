#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_STRING_LEN 100
#define START_PATH "./tmp"
#define ANSWER_PATH "result.txt"
#define REG_TYPE 8
#define DIR_TYPE 4
#define CUR_DIR_NAME "."
#define PREV_DIR_NAME ".."
#define WRITE_FLAG "w"

char *concatenate_paths(char *path, char *next_file){
    size_t new_len = strlen(path) + 2 + strlen(next_file);
    char *new_path = (char*)malloc(new_len*sizeof(char));
    sprintf(new_path, "%s/%s", path, next_file);
    return new_path;
}


int find_letter(char *cur_path, char *file_name, FILE *answer_file){
    int file_found = 0;
    DIR *dir = opendir(cur_path);
    if(dir){
        struct dirent *cur_file;
        cur_file = readdir(dir);
        char *new_path = concatenate_paths(cur_path, cur_file->d_name);

        while(cur_file){
            new_path = concatenate_paths(cur_path, cur_file->d_name);
            if (cur_file->d_type == REG_TYPE &&
                strcmp(cur_file->d_name, file_name) == 0){
                    fprintf(answer_file, "%s\n", new_path);
                    free(new_path);
                    file_found = 1;
                    break;
                }

            if (cur_file->d_type == DIR_TYPE &&
                strcmp(cur_file->d_name, CUR_DIR_NAME) &&
                strcmp(cur_file->d_name, PREV_DIR_NAME)){

                if(find_letter(new_path,file_name, answer_file) == 1){
                    free(new_path);
                    file_found = 1;
                    break;
                }
            }

            cur_file = readdir(dir);

        free(new_path);
        }
    }else{
        printf("Error: couldn't open a directory at %s", cur_path);
        exit(0);
    }
    closedir(dir);
    return file_found;
}


void get_path(char *word, FILE *answer_file){
    char target_file[] = "?.txt";
    char *path = (char*)malloc((1+strlen(START_PATH)) * sizeof(char));
    strcpy(path, START_PATH);

    for(int i = 0; i < strlen(word); i++){
        target_file[0] = word[i];
        find_letter(path, target_file, answer_file);
        strcpy(path, START_PATH);
    }

}


int main(){
    char *searched_string = (char*)malloc(MAX_STRING_LEN*sizeof(char));
    fgets(searched_string, MAX_STRING_LEN, stdin);
    FILE *answer_file = fopen(ANSWER_PATH, WRITE_FLAG);
    get_path(searched_string, answer_file);
    fclose(answer_file);
    free(searched_string);
    return 0;
}
