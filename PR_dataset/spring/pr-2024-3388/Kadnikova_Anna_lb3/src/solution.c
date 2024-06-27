#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_LEN 512
#define READ_FLAG "r"
#DEFINE WRITE_FLAG "w"
#define BLCK_LST "."
#define PREV ".."
#define NEXT_DIR_TEMLATE "%s/%s"
#define REQUIRED_FILE "Minotaur"
#define END_VAL "Deadlock"
#define START_DIR "./labyrinth"
#define START_FILE "file.txt"
#define OUTPUT_FILE "./result.txt"
#define INCLUDE_FLAG "@include "


char *result[MAX_LEN];
int ind = 0;

int get_file_path(char *curr_dir, char *filename, char *path) {
    DIR *dir;
    struct dirent *entry;
    if ((dir = opendir(curr_dir)) == NULL)
        return 0;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, BLCK_LST) == 0 || strcmp(entry->d_name, PREV) == 0)
                continue;
            char next_dir[MAX_LEN];
            snprintf(next_dir, sizeof(next_dir), NEXT_DIR_TEMLATE, curr_dir, entry->d_name);
            if (get_file_path(next_dir, filename, path)) {
                closedir(dir);
                return 1;
            }
        } else {
            if (strcmp(entry->d_name, filename) == 0) {
                char file_path[MAX_LEN];
                snprintf(file_path, sizeof(file_path), NEXT_DIR_TEMLATE, curr_dir, entry->d_name);
                strcpy(path, file_path);
                return 1;
            }
        }
    }
    closedir(dir);
    return 0;
}

int find_minotaur(char *root_dir, char *filename) {
    char file_path[MAX_LEN];
    if (get_file_path(root_dir, filename, file_path) == 0)
        return 0;
    FILE *file = fopen(file_path, READ_FLAG);
    if (file == NULL)
        return 0;
    int file_indicator = 1;
    for (int i = 0; i < ind; i++) {
        if (strcmp(result[i], file_path) == 0) {
            file_indicator = 0;
            break;
        }
    }
    if (file_indicator)
        result[ind++] = file_path;
    char str[MAX_LEN];
    while (fgets(str, sizeof(str), file)) {
        if (strstr(str, END_VAL) != NULL) {
            result[ind] = NULL;
            fclose(file);
            return 0;
        } else if (strstr(str, EQUIRED_FILE) != NULL) {
            fclose(file);
            return 1;
        } else if (strncmp(str, INCLUDE_FLAG, 9) == 0 && str[strlen(str) - 1] == '\n') {
            int i = 9;
            while (str[i] != '\n')
                i++;
            str[i] = '\0';
            if (find_minotaur(root_dir, &str[9]) == 1) {
                fclose(file);
                return 1;
            }
        }
    }
    fclose(file);
    return 0;
}

int main() {
    FILE *file;
    file = fopen(OUTPUT_FILE, WRITE_FLAG);
    if (find_minotaur(START_DIR, START_FILE)) {
        for (int i = 0; i < ind; i++) {
            fputs(result[i], file);
            fputs("\n", file);
        }
    }
    fclose(file);
    return 0;
}
