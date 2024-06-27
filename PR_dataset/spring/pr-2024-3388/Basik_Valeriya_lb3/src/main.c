#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_DIR_NAME_LENGTH 128
#define MAX_RESULT_STRING_LENGTH 512
#define MAX_INPUT_STRING_LENGTH 128

void rec_search(char letter, char* dir_name, FILE* res_file){
    DIR* dir = opendir(dir_name);
    if(dir){
        struct dirent* r_dir = readdir(dir);
        while(r_dir){
            if ((r_dir->d_type == DT_DIR) && (strcmp(r_dir->d_name, ".") && strcmp(r_dir->d_name, ".."))){
                char new_dir_name[strlen(r_dir->d_name) + strlen(dir_name) + 1];
                new_dir_name[0] = '\0';
                strcat(new_dir_name, dir_name);
                strcat(new_dir_name, "/");
                strcat(new_dir_name, r_dir->d_name);
                rec_search(letter, new_dir_name, res_file);
            } else {
                if((strlen(r_dir->d_name) == MAX_RESULT_STRING_LENGTH) && ((r_dir->d_name)[0] == letter)){
                    char res_str[MAX_RESULT_STRING_LENGTH];
                    snprintf(res_str, sizeof res_str, "%s/%s\n", dir_name, r_dir->d_name);
                    fputs(res_str, res_file);
                }
            }
            r_dir = readdir(dir);
        }
    closedir(dir);
    }
}

int main(){
    int i = 0;
    char str[MAX_INPUT_STRING_LENGTH];
    scanf("%s", str);
    char* dir_name = "./tmp";
    FILE* res_file = fopen("result.txt", "w");
    for(; i < strlen(str); i++){
        rec_search(str[i], dir_name, res_file);
    }
    fclose(res_file);
}

