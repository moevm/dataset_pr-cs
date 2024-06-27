#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_LEN 1024

char *search_file(const char *dir_path, const char *file_name, char *curr_path) {
    DIR *dir = opendir(dir_path);
    if (!dir) {
        return NULL;
    }
    struct dirent *de = readdir(dir);
    char new_path[MAX_LEN];
    while (de) {
        snprintf(new_path, MAX_LEN, "%s/%s", dir_path, de->d_name);
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            char *result = search_file(new_path, file_name, curr_path);
            if (result != NULL) {
                closedir(dir);
                return result;
            }
        }
        if (strcmp(de->d_name, file_name) == 0) {
            closedir(dir);
            strcpy(curr_path, new_path);
            return curr_path;
        }
        de = readdir(dir);
    }
    closedir(dir);
    return NULL;
}

int read_file(const char *dir_path, const char *file_name, char **current_list, int index) {
    char line[MAX_LEN], current_path[MAX_LEN];
    search_file(dir_path, file_name, current_path);
    if (!current_path[0]) {
        return 0;
    }
    current_list[index] = strdup(current_path);
    index++;
    FILE *file = fopen(current_path, "r");
    if (!file) {
        return 0;
    }
    int result = 1;
    while (fgets(line, MAX_LEN, file)) {
        size_t len = strlen(line);
        if (len > 0 && line[len - 1] == '\n') {
            line[len - 1] = '\0';
        }
        if (strcmp(line, "Minotaur") == 0) {
            result = 0;
            break;
        } else if (strcmp(line, "Deadlock") == 0) {
            current_list[index] = NULL;
            result = 1;
            break;
        } else if (strncmp(line, "@include ", 9) == 0) {
            char include_file[MAX_LEN];
            strcpy(include_file, line + 9);
            if (read_file(dir_path, include_file, current_list, index) == 0) {
                result = 0;
                break;
            }
        }
    }
    fclose(file);
    return result;
}

int main() {
    char *current_list[MAX_LEN];
    if (read_file("./labyrinth", "file.txt", current_list, 0) == 0) {
        FILE *file = fopen("./result.txt", "w");
        if (file == NULL) {
            printf("Ошибка открытия файла.\n");
            return 1;
        }
        for (int i = 0; current_list[i]; i++) {
            fputs(current_list[i], file);
            fputs("\n", file);
            free(current_list[i]);
        }
        fclose(file);
    } else {
        printf("Ошибка чтения файла.\n");
    }
    return 0;
}