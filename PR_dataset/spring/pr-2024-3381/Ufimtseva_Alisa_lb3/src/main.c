#include <stdio.h>
#include <string.h>
#include <dirent.h>

void find_file(char letter, char* di, FILE* file) {
    DIR* dir = opendir(di);
    if (dir) {
        struct dirent* de = readdir(dir);
        while (de) {
            if ((de->d_type == DT_DIR) && (strcmp(de->d_name, ".")) && (strcmp(de->d_name, ".."))) {
                char new_dir[strlen(de->d_name) + strlen(di) + 1];
                new_dir[0] = '\0';
                strcat(new_dir, di);
                strcat(new_dir, "/");
                strcat(new_dir, de->d_name);
                find_file(letter, new_dir, file);
            } 
            else {
                if ((strlen(de->d_name) == 5) && (de->d_name[0] == letter) && strstr(de->d_name,".txt")){
                    fprintf(file, "%s/%s\n", di, de->d_name);
                }
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main() {
    char word[30];
    scanf("%s", word);
    char* di = "./tmp";
    FILE* file = fopen("result.txt", "w");
    for (int i=0; i < strlen(word); i++){
        find_file(word[i], di, file);
    }
    fclose(file);
    return 0;
}