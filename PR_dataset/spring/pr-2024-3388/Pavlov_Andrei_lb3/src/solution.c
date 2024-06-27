#include <dirent.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define OUTPUT_FILENAME "result.txt"
#define ADD_NAMECONST "add"
#define FIND_ADD_DIR (strcmp(dir_entity->d_name, ADD_NAMECONST) == 0)
#define MUL_NAMECONST "mul"
#define FIND_MUL_DIR (strcmp(dir_entity->d_name, MUL_NAMECONST) == 0)
#define START_PROCESS 0
#define ADD_PROCESS 1
#define MUL_PROCESS 2


char* make_new_path(const char* old_path, const char* prefix)  {
    char *upd_path = malloc(sizeof(char) * (strlen(old_path) + strlen(prefix) + 1));
    strcpy(upd_path, old_path);
    strcat(upd_path, prefix);
    return upd_path;
}


int64_t change_result(int64_t past, int64_t new, int process_type) {
    switch (process_type) {
        case START_PROCESS:
            return new;
        case ADD_PROCESS:
            return past + new;
        case MUL_PROCESS:
            return past * new;
    }
}


int64_t process_dir(const char *path, int process_type) {
    int64_t result = (process_type == MUL_PROCESS) ? 1ll : 0ll;
    DIR *dir = opendir(path);
    if (!dir) return 0;

    struct dirent *dir_entity = readdir(dir);
    while (dir_entity) {
        if (FIND_ADD_DIR) {
            char *upd_path = make_new_path(path, "add/");
            result = change_result(result, process_dir(upd_path, ADD_PROCESS), process_type);
        } else if (FIND_MUL_DIR) {
            char *upd_path = make_new_path(path, "mul/");
            result = change_result(result, process_dir(upd_path, MUL_PROCESS), process_type);
        } else if ((process_type != START_PROCESS) && (strstr(dir_entity->d_name, ".txt") != NULL)) {
            char *file_path = make_new_path(path, dir_entity->d_name);
            FILE *file = fopen(file_path, "r");
            int digit;
            while (fscanf(file, "%d", &digit) == 1) result = change_result(result, digit, process_type);
            fclose(file);
        }
        dir_entity = readdir(dir);
    }

    closedir(dir);
    return result;
}


int main() {
    char path[] = "./tmp/";
    int64_t result = process_dir(path, START_PROCESS);
    FILE *file = fopen(OUTPUT_FILENAME, "w");
    fprintf(file, "%ld", result);
    fclose(file);
    return 0;
}
