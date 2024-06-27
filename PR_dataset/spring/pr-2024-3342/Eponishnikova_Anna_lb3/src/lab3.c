#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_LEN 512

int file_path(char *dir_name, char *filename, char *path) {
    DIR *dir;
    if ((dir = opendir(dir_name)) == NULL)
        return 0;
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        if (de->d_type == DT_DIR) {
            if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
                continue;
            char next_dir[MAX_LEN];
            snprintf(next_dir, MAX_LEN, "%s/%s", dir_name, de->d_name);
            if (file_path(next_dir, filename, path)) {
                closedir(dir);
                return 1;
            }
        } else {
            if (strcmp(de->d_name, filename) == 0) {
                char curr_path[MAX_LEN];
                snprintf(curr_path, MAX_LEN, "%s/%s", dir_name, de->d_name);
                strcpy(path, curr_path);
                return 1;
            }
        }
    }
    closedir(dir);
    return 0;
}

int find_minotaur(char *dir_name, char *filename, char** answer, int ind) {
    FILE* file;
    char path[MAX_LEN], str[MAX_LEN];
    if (file_path(dir_name, filename, path) == 0)
        return 0;
    int flag = 1;
    for (int i = 0; i < ind; i++) {
        if (strcmp(answer[i], path) == 0) {
            flag = 0;
            break;
        }
    }
    if (flag)
        answer[ind++] = path;
    file = fopen(path, "r");
    if (file == NULL)
        return 0;
    while (fgets(str, sizeof(str), file)) {
        if (strcmp(str, "Deadlock") == 0) {
            answer[ind] = NULL;
            fclose(file);
            return 0;
        } else if (strcmp(str, "Minotaur") == 0) {
            fclose(file);
            return 1;
        } else if (strncmp(str, "@include ", 9) == 0 && str[strlen(str) - 1] == '\n') {
            int i = 9;
            while (str[i] != '\n')
                i++;
            str[i] = '\0';
            if (find_minotaur(dir_name, &str[9], answer, ind) == 1) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

int main() {
    char* answer[MAX_LEN];
    int ind = 0;
    FILE *file;
    file = fopen("./result.txt", "w");
    if (find_minotaur("./labyrinth", "file.txt", answer, ind)) {
        for (int i = 0; answer[i]; i++) {
            fputs(answer[i], file);
            fputs("\n", file);
        }
    }
    fclose(file);
    return 0;
}