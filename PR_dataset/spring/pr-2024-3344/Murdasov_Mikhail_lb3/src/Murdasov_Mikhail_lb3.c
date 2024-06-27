#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void scan_dir(char* base_dir, FILE* file, char target){
    char path[3000];
    struct dirent* current_dir;
    DIR* dir = opendir(base_dir);
    DIR* is_dir;
    if(dir == NULL) return;

    while((current_dir = readdir(dir)) != NULL){
        if(strcmp(current_dir->d_name, ".") == 0 || strcmp(current_dir->d_name, "..") == 0){
            continue;
        }
        
        strcpy(path, base_dir);
        strcat(path, "/");
        strcat(path, current_dir->d_name);

        char* file_name = (char*)strdup(current_dir->d_name);
        if(file_name == NULL){
            fprintf(stderr, "[ ERROR ]: Memory allocation error.");
        }
        if((is_dir = opendir(path)) == NULL && strcmp(strtok(file_name, "."), &target) == 0){
            fprintf(file, "%s\n", path);
        }else{
            closedir(is_dir);
        }

        free(file_name);
        scan_dir(path, file, target);
    }
    closedir(dir);
}

int main(){

    FILE* result = fopen("./result.txt", "w");
    if(result == NULL){
        fprintf(stderr, "[ ERROR ]: Failed to open file.");
    }

    char* input = (char*)malloc(sizeof(char)*1000);
    if(input == NULL){
        fprintf(stderr, "[ ERROR ]: Memory allocation error.");
    }
    scanf("%s", input);

    for(int i = 0; i<strlen(input); i++){
        scan_dir("./tmp", result, input[i]);
    }

    fclose(result);
    free(input);

    return 0;
}
