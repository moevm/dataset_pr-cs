#include <stdio.h>
#include <string.h>
#include <dirent.h>
#define SIZE 100


void need_letter(char letter, char* path, FILE* file){
    DIR* dir = opendir(path);
    if (dir){
        struct dirent* new = readdir(dir);
        while (new){
            if ((new -> d_type == DT_DIR) && strcmp(new -> d_name, ".") && strcmp(new -> d_name, "..")){
                char new_path[strlen(path) + strlen(new -> d_name) + 1];
                new_path[0] = '\0';
                strcat(new_path, path);
                strcat(new_path, "/");
                strcat(new_path, new -> d_name);
                need_letter(letter, new_path, file);
            } 
            else{
                if (strlen(new -> d_name) == 5 && new -> d_name[0] == letter){
                    fprintf(file, "%s/%s\n", path, new -> d_name);
                }
            }
            new = readdir(dir);
        }
    }
    closedir(dir);
}


int main(){
    char str[SIZE];
    fgets(str, SIZE, stdin);
    char* path = "./tmp";
    FILE* file = fopen("result.txt", "w");
    for (int i = 0; i < strlen(str); i++){
        need_letter(str[i], path, file);
    }
    fclose(file);
    return 0;
}
