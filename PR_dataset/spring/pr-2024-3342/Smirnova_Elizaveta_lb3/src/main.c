#include <stdio.h>
#include <string.h>
#include <dirent.h>

void search_letter(char letter, char* file_path, FILE* file) {

    DIR* dir = opendir(file_path);
    if (dir) {
        struct dirent* de = readdir(dir);
        while (de) {
            if ((de->d_type == DT_DIR) && (strcmp(de->d_name, ".") != 0) && (strcmp(de->d_name, "..") != 0)) {
                char* new_file_path[strlen(file_path) + strlen(de->d_name) + 1];
                sprintf(new_file_path, "%s/%s", file_path, de->d_name);
                search_letter(letter, new_file_path, file);
            }
            else {
                if ((strlen(de->d_name) == 5) && (de->d_name[0] == letter))
                    fprintf(file, "%s/%s\n", file_path, de->d_name);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main() {

    char word[100];
    scanf("%s", word);
    char* file_path = "./tmp";
    FILE* file = fopen("result.txt", "w");
    for (int i = 0; i < strlen(word); i++)
        search_letter(word[i], file_path, file);
    fclose(file);
    return 0;
}