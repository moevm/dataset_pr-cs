#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define MAX_STR_SIZE 1000
#define INPUT_STR_SIZE 500
#define FAILED_PATH "\0"
#define START_DIR "tmp"
#define OUTPUT_FILE "result.txt"
#define NEXT_DIR_TEMLATE "%s/%s"
#define UP_DIR "."
#define DIR_TYPE 4

void make_all();
char* find_file_for_name(char *dir_path, char *file_to_found);

char* find_file_for_name(char *dir_path, char *file_to_found){
    DIR *dir = opendir(dir_path);
    char *find_path;
    char *next_dir_path = calloc(MAX_STR_SIZE, sizeof(char));
    if(dir){
        struct  dirent *current_dir = readdir(dir);
        while (current_dir){ 
            if (!strcmp(current_dir->d_name, file_to_found))
                return dir_path;

            if (current_dir->d_type == DIR_TYPE && strstr(current_dir->d_name, UP_DIR) == 0){
                sprintf(next_dir_path, NEXT_DIR_TEMLATE, dir_path, current_dir->d_name);
                find_path = find_file_for_name(next_dir_path, file_to_found);

                if (strcmp(find_path, FAILED_PATH) != 0){
                    return find_path;
                }
            }

            current_dir = readdir(dir);
        }
    }

    closedir(dir);

    return FAILED_PATH;
}
void make_all(){
    char input[INPUT_STR_SIZE];
    char cur_letter[INPUT_STR_SIZE];
    char answer[MAX_STR_SIZE];
    FILE *opened_file = fopen(OUTPUT_FILE, "w");

    scanf("%s", input);

    if(opened_file){
        for (int i = 0; i < strlen(input); i++){
            sprintf(cur_letter, "%c.txt", input[i]);
            sprintf(answer, "./%s/%s\n", find_file_for_name(START_DIR, cur_letter), cur_letter);
            fputs(answer, opened_file);
        }

        fclose(opened_file);
    }
}

int main(){
    make_all();
    return 0;
}