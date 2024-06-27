#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void listFilesRecursively(FILE *inp, char *base_path, char letter) {

    DIR *dir = opendir(base_path);

    if (!dir) return;

    struct dirent *dp = readdir(dir);
    char *path;

    while (dp != NULL) {

        if (dp->d_type == DT_DIR && strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {

            path = (char *)malloc(sizeof(char) * (strlen(base_path) + strlen(dp->d_name) + 2));
            path[0] = '\0';

            strcat(path, base_path);
            strcat(path, "/");
            strcat(path, dp->d_name);
            listFilesRecursively(inp, path, letter);

            free(path);

        } else {

            if (dp->d_type == DT_REG && strlen(dp->d_name) == 5 && dp->d_name[0] == letter && dp->d_name[1] == '.' &&
            dp->d_name[2] == 't' && dp->d_name[3] == 'x' && dp->d_name[4] == 't') {

                fprintf(inp, "%s/%s\n", base_path, dp->d_name);
            }
        }

        dp = readdir(dir);
    }

    closedir(dir);
}


int main() {
    char *base_path = "./tmp";
    FILE *file = fopen("./result.txt", "w");

    char *inp_string = (char *)malloc(sizeof(char) * 1000);
    scanf("%s", inp_string);

    for (size_t i = 0; i < strlen(inp_string); i++) listFilesRecursively(file, base_path, inp_string[i]);

    fclose(file);
    free(inp_string);

    return 0;
}
