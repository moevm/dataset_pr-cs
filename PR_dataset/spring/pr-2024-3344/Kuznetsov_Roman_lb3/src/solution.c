#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

typedef struct {
    long int number;
    char text[256];
} Line;

Line *lines = NULL;
int count = 0;
int capacity = 0;

int comparation(const void* a, const void* b) {
    const Line* line_a = (const Line*)a;
    const Line* line_b = (const Line*)b;
    
    if (line_a->number < line_b->number) return -1;
    if (line_a->number > line_b->number) return 1;
    return 0;
}

void read_txt(const char* name_of_file, FILE* result) {
    FILE* f = fopen(name_of_file, "r");
    if (f == NULL) {
        perror(name_of_file);
        return;
    }

    if(fscanf(f, "%ld %[^\n]\n", &lines[count].number, lines[count].text) == 2) {
        count++;
        if (count >= capacity) {
            capacity = (capacity == 0) ? 1 : capacity * 2;
            lines = realloc(lines, capacity * sizeof(Line));
            if (lines == NULL) {
                fprintf(stderr, "Memory allocation error\n");
                exit(1);
            }
        }
    }

    fclose(f);
}

void find_txt(const char* dirname, FILE* result) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        perror(dirname);
        return;
    }

    struct dirent* entry;

    while ((entry = readdir(dir)) != NULL) {
         
        if (entry->d_type == DT_REG) {
            char path_to_file[strlen(entry->d_name) + strlen(dirname) + 2];
            
            strcpy(path_to_file, dirname);
            strcat(path_to_file, "/");
            strcat(path_to_file, entry->d_name);
            read_txt(path_to_file, result);
        
        } else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            char path_to_dir[strlen(entry->d_name) + strlen(dirname) + 2];

            strcpy(path_to_dir, dirname);
            strcat(path_to_dir, "/");
            strcat(path_to_dir, entry->d_name);
            find_txt(path_to_dir, result);
        }
    }

    closedir(dir);
}

int main() {
    lines = malloc(1000 * sizeof(Line));
    if (lines == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 1;
    }

    FILE* result = fopen("result.txt", "w");
    if (result == NULL) {
        perror("result.txt");
        return 1;
    }

    find_txt(".", result);
    qsort(lines, count, sizeof(Line), comparation);

    for (int i = 0; i < count; i++) {
        fprintf(result, "%ld %s\n", lines[i].number, lines[i].text);
    }

    fclose(result);
    free(lines);
    return 0;
}
