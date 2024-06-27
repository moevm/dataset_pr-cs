#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdbool.h>
#include <ctype.h>

#define BUF 1024
#define SEP_PATH "/"
#define END_LINE '\0'
#define CURRENT_DIRECTORY "."
#define PARENT_DIRECTORY ".."

bool is_valid_directory(struct dirent *entity) {
    return (entity->d_type == DT_DIR && strcmp(entity->d_name, CURRENT_DIRECTORY) != 0 && strcmp(entity->d_name, PARENT_DIRECTORY) != 0);
}

void print_in_file(FILE* file, const char *path, char *line){
    fprintf(file, "%s%s%s\n", path, SEP_PATH, line);
}

void search_letter(char letter, const char *path, FILE *file) {
    DIR* directory = opendir(path);
    if (directory != NULL) {
        struct dirent* entity;
        while ((entity = readdir(directory)) != NULL) {
            if (is_valid_directory(entity)) {
                char new_path[strlen(path) + strlen(entity->d_name) + 1];
                new_path[0] = END_LINE;
                strcat(new_path, path);
                strcat(new_path, SEP_PATH);
                strcat(new_path, entity->d_name);
                search_letter(letter, new_path, file);
            }
            else if (strlen(entity->d_name) == 5 && entity->d_name[0] == letter){
                print_in_file(file, path, entity->d_name);
            }
        }
        closedir(directory);
    }
}

void work_with_file(const char *word, const char *path, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file != NULL) {
        for (int i = 0; i < strlen(word); i++) {
            search_letter(word[i], path, file);
        }
    }
    fclose(file);
}

int main() {
    char word[BUF];
    scanf("%s", word);
    const char *path = "./tmp";
    const char *output_filename = "result.txt";
    work_with_file(word, path, output_filename);
    return 0;
}
