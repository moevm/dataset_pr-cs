#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define PATH "./labyrinth"
#define ANSWER_PATH "result.txt"
#define FIRST_FILE "file.txt"
#define ADD 20
#define START 100

char *pathcat(const char *path1, const char *path2) {
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);
    return res_path;
}


char *find_file(const char *dir_name, const char *file_name) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        return NULL;
    }
    struct dirent *de = readdir(dir);
    while (de) {
        char *de_path = pathcat(dir_name, de->d_name);
        if (!de_path) {
            closedir(dir);
            return NULL;
        }
        if (de->d_type == DT_REG) {
            if (strcmp(de->d_name, file_name) == 0) {
                closedir(dir);
                return de_path;
            }
        } else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            char *sub_dir_res = find_file(de_path, file_name);
            if (sub_dir_res != NULL) {
                free(de_path);
                closedir(dir);
                return sub_dir_res;
            }
        }
        free(de_path);
        de = readdir(dir);
    }
    closedir(dir);
    return NULL;
}

int find_minotaur(char *dir_name, char *file_name, char ***all_paths, size_t *count, size_t *capacity) {
    char *file_path = find_file(dir_name, file_name);
    if (!file_path) {
        return 0;
    }
    FILE *file = fopen(file_path, "r");
    if (!file) {
        free(file_path);
        return 0;
    }
    if (*count >= *capacity) {
        size_t new_capacity = *capacity + ADD;
        char **tmp = (char **) realloc(*all_paths, new_capacity * sizeof(char *));
        if (!tmp) {
            return 0;
        }
        *capacity = new_capacity;
        *all_paths = tmp;
    }
    (*all_paths)[(*count)++] = file_path;
    char str[100];
    while (fgets(str, 100, file) != NULL) {
        str[strcspn(str, "\n")] = '\0';
        if (strstr(str, "Deadlock") != NULL) {
            break;
        } else if (strstr(str, "Minotaur") != NULL) {
            fclose(file);
            return 1;
        } else if (strstr(str, "@include") != NULL) {
            int sub_res = find_minotaur(dir_name, &str[9], all_paths, count, capacity);
            if (sub_res == 1) {
                fclose(file);
                return sub_res;
            }
        }
    }
    (*count)--;
    free((*all_paths)[*count]);
    (*all_paths)[(*count)] = NULL;
    fclose(file);
    return 0;
}

int main() {
    size_t count = 0;
    size_t capacity = START;
    char **all_paths = (char **) malloc(capacity * sizeof(char *));
    int res = find_minotaur(PATH, FIRST_FILE, &all_paths, &count, &capacity);
    if (res == 0) {
        printf("smth went wrong\n");
        return 0;
    }
    FILE *result = fopen(ANSWER_PATH, "w");
    for (size_t i = 0; i < count; i++) {
        fprintf(result, "%s\n", all_paths[i]);
        free(all_paths[i]);
    }
    free(all_paths);
    fclose(result);
    return 0;
}