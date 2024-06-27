#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX 1024

int comparator(const void *a, const void *b) {
    const char *str_a = *(const char **) a;
    const char *str_b = *(const char **) b;
    long int num_1, num_2;
    sscanf((const char *) str_a, "%ld", &num_1);
    sscanf((const char *) str_b, "%ld", &num_2);
    return num_1 - num_2;
}

char *file_text(const char *file_path) {
    FILE *file = fopen(file_path, "r");
    if (!file) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }
    char *text = malloc(MAX);
    if (!text) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    if (fgets(text, MAX, file) == NULL) {
        perror("fgets");
        exit(EXIT_FAILURE);
    }
    fclose(file);
    return text;
}

void dir_list(const char *dir_name, char **files, int *files_len) {
    DIR *dir = opendir(dir_name);
    if (!dir) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }
        char *file_path = malloc(strlen(dir_name) + strlen(de->d_name) + 2);
        if (!file_path) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        snprintf(file_path, strlen(dir_name) + strlen(de->d_name) + 2, "%s/%s", dir_name, de->d_name);
        if (de->d_type == DT_REG) {
            files[*files_len] = file_text(file_path);
            (*files_len)++;
        } else if (de->d_type == DT_DIR) {
            dir_list(file_path, files, files_len);
        }
        free(file_path);
    }
    closedir(dir);
}

int main() {
    char **files = malloc(MAX * sizeof(char *));
    if (!files) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }
    int files_len = 0;
    dir_list("./root", files, &files_len);
    qsort(files, files_len, sizeof(char *), comparator);
    FILE *result = fopen("result.txt", "w");
    for (int i = 0; i < files_len; i++) {
        fprintf(result, "%s\n", files[i]);
        free(files[i]);
    }
    fclose(result);
    free(files);
    return 0;
}