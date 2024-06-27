#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


#define NAME_LEN 500
#define STOP_WORD "Deadlock"
#define NEEDED_WORD "Minotaur"
#define LEN_OF_WORD 8
#define WRITE_FILE "w"
#define READ_FILE "r"
#define CURRENT "."
#define PREVIOUS ".."

int add_to_answer(char *root_dir, char *file_name, char** result, int answer_len);

int search_for_file_path(const char *directory_name, const char *file_name, char *path){
    DIR *directory = opendir(directory_name);
    struct dirent *current_file;

    if(directory!=NULL){
        current_file = readdir(directory);
        if(current_file!=NULL ){
            while (current_file!=NULL){
                if(current_file->d_type == DT_REG && strcmp(current_file->d_name, file_name)==0){
                    char file_path[NAME_LEN];
                    snprintf(file_path, sizeof(file_path), "%s/%s", directory_name, file_name);
                    strcpy(path, file_path);
                    return 1;
                }else if (current_file->d_type == DT_DIR && strcmp(current_file->d_name, CURRENT) != 0 && strcmp(current_file->d_name, PREVIOUS) != 0){
                    char new_directory[NAME_LEN];
                    snprintf(new_directory, sizeof(new_directory), "%s/%s", directory_name, current_file->d_name);
                    if (search_for_file_path(new_directory, file_name, path)) {
                        closedir(directory);
                        return 1;
                    }
                }
                current_file = readdir(directory);
            }
            closedir(directory);
        }
    }
    return 0;

}
int check_in_file(char *root_dir, char *file_name, char** result, int answer_len, char* file_path){
    result[answer_len] = file_path;
    answer_len+=1;
    FILE *file = fopen(file_path, READ_FILE);
    char line[NAME_LEN];

    while (fgets(line, sizeof(line), file)) {
        if (strncmp(line, STOP_WORD, LEN_OF_WORD) == 0) {
            result[answer_len] = NULL;
            fclose(file);
            return 0;
        } else if (strncmp(line, NEEDED_WORD, LEN_OF_WORD) == 0) {
            fclose(file);
            return answer_len;
        } else if (strncmp(line, "@include ", LEN_OF_WORD+1) == 0) {
            line[strlen(line)-1] = '\0';
            int answer = add_to_answer(root_dir, &line[LEN_OF_WORD+1], result, answer_len);
            if (answer>0) {
                fclose(file);
                return answer;
            }
        }
    }
    fclose(file);
    return 0;
}
int add_to_answer(char *root_dir, char *file_name, char** result, int answer_len) {
    char* file_path = malloc(sizeof(char)*NAME_LEN);

    if (search_for_file_path(root_dir, file_name, file_path) == 0)
        return 0;
    else{
        result[answer_len] = file_path;
        answer_len+=1;
        return check_in_file(root_dir, file_name, result, answer_len-1, file_path);
    }
}

int main() {
    FILE *file;
    char *result[NAME_LEN];
    file = fopen("./result.txt", WRITE_FILE);
    int answer_len = add_to_answer("./labyrinth", "file.txt", result, 0);

    if (answer_len>0) {
        for (int path_ind = 0; path_ind < answer_len; path_ind++) {
            fputs(result[path_ind], file);
            fputs("\n", file);
        }
    }
    fclose(file);
    return 0;
}
