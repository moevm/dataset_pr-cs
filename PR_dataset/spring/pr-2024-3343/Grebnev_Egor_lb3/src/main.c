#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_INCLUDES 20000
#define MAX_PATH_LEN 1024
#define INITIAL_PATH "./labyrinth"
#define INITIAL_FILE "file.txt"
#define OUTPUT_FILE "result.txt"

char *deadlocks[MAX_INCLUDES];
int deadlock_count = 0;
char trace[MAX_INCLUDES][MAX_PATH_LEN];
int trace_count = 0;

void add_deadlock(const char *deadlock) {
    for (int i = 0; i < deadlock_count; ++i) {
        if (strcmp(deadlocks[i], deadlock) == 0) {
            return;
        }
    }
    deadlocks[deadlock_count] = (char *)malloc((strlen(deadlock) + 1) * sizeof(char));
    strcpy(deadlocks[deadlock_count], deadlock);
    deadlock_count++;
}

void get_deadlocks(const char *path) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[MAX_PATH_LEN];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (entry->d_type == 4) {
            get_deadlocks(fullpath);
            get_deadlocks(fullpath);
        } else {
            FILE *file = fopen(fullpath, "r");
            if (!file) continue;

            char line[MAX_PATH_LEN], file_include[MAX_PATH_LEN];
            int include_count = 0;

            while (fgets(line, sizeof(line), file)) {
                if (strcmp(line, "Deadlock") == 0) {
                    add_deadlock(entry->d_name);
                    break;
                }
                if (strcmp(line, "Minotaur") == 0) {
                    include_count++;
                    break;
                }
                if (sscanf(line, "@include %s", file_include) == 1) {
                    int isDeadlock = 0;
                    for (size_t i = 0; i < deadlock_count; i++) {
                        if (strcmp(file_include, deadlocks[i]) == 0) {
                            isDeadlock = 1;
                            break;
                        }
                    }
                    if (!isDeadlock) include_count++;
                }
            }

            if (include_count == 0) {
                add_deadlock(entry->d_name);
            }
            fclose(file);
        }
    }
    closedir(dir);
}

void process_directory(const char *path, const char *filename) {
    DIR *dir = opendir(path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir))) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            continue;

        char fullpath[MAX_PATH_LEN];
        snprintf(fullpath, sizeof(fullpath), "%s/%s", path, entry->d_name);

        if (entry->d_type == 4)
            process_directory(fullpath, filename);
        else if (strcmp(entry->d_name, filename) == 0) {
            FILE *file = fopen(fullpath, "r");
            if (!file) continue;

            char line[MAX_PATH_LEN], file_include[MAX_PATH_LEN];
            while (fgets(line, sizeof(line), file)) {
                if (strcmp(line, "Minotaur") == 0) {
                    FILE *output_file = fopen(OUTPUT_FILE, "w");
                    for (int i = 0; i < trace_count; i++) {
                        fprintf(output_file, "%s\n", trace[i]);
                    }
                    fprintf(output_file, "%s", fullpath);
                    fclose(output_file);
                    return;
                }
                if (sscanf(line, "@include %s", file_include) == 1) {
                    int isDeadlock = 0;
                    for (size_t i = 0; i < deadlock_count; i++) {
                        if (strcmp(file_include, deadlocks[i]) == 0) {
                            isDeadlock = 1;
                            break;
                        }
                    }
                    if (!isDeadlock) {
                        strcpy(trace[trace_count++], fullpath);
                        process_directory(INITIAL_PATH, file_include);
                    }
                }
            }
            fclose(file);
        }
    }
    closedir(dir);
}

int main() {
    get_deadlocks(INITIAL_PATH);
    get_deadlocks(INITIAL_PATH);
    process_directory(INITIAL_PATH, INITIAL_FILE);
    return 0;
}
