#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define BUF 100

void search_letter(char letter, char *file_path, FILE *file) {

    DIR *dir = opendir(file_path);
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de) {
            if ((de->d_type == DT_DIR) && (strcmp(de->d_name, ".")) && (strcmp(de->d_name, ".."))) {
                char new_file_path[strlen(de->d_name) + strlen(file_path) + 1];
                new_file_path[0] = '\0';
                strcat(new_file_path, file_path);
                strcat(new_file_path, "/");
                strcat(new_file_path, de->d_name);
                search_letter(letter, new_file_path, file);

            } else {
                if ((strlen(de->d_name) == 5) && (de->d_name[0] == letter))
                    fprintf(file, "%s/%s\n", file_path, de->d_name);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}


int main() {
    int i = 0;
    char word[BUF];
    scanf("%s", word);
    char *file_path = "./tmp";
    FILE *file = fopen("result.txt", "w");
    for (; i < strlen(word); i++)
        search_letter(word[i], file_path, file);
    fclose(file);
}