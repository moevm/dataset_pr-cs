#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define PATH "./tmp"
#define WORD_MAX_SIZE 20


char *get_file_path(char *dir_path, char *file_name) {
    size_t file_path_length = strlen(dir_path) + 1 + strlen(file_name);
    char *file_path = (char *) malloc((file_path_length + 1) * sizeof(char));
    if (!file_path) {
        return NULL;
    }

    file_path[0] = '\0';
    strcat(file_path, dir_path);
    strcat(file_path, "/");
    strcat(file_path, file_name);

    return file_path;
}

char *find_file_named_letter(char letter_to_find, char *dir_path) {
    DIR *dir = opendir(dir_path);
    // if an error occurs when opening the directory, return an empty string
    if (!dir) return "";

    char *file_path = "";

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            // if the current entity is a directory

            // skip links to the current and previous directories
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

            // get path to the found directory
            char *new_dir_path = get_file_path(dir_path, entry->d_name);

            // if a memory allocation error occurred, return NULL
            if (!new_dir_path) {
                return NULL;
            }

            // try to find files in the found directory
            file_path = find_file_named_letter(letter_to_find, new_dir_path);
            free(new_dir_path);

            // if a memory allocation error occurred, return NULL
            if (!file_path) return NULL;

            // if a correct file is found, return the path to it, else continue searching in the current directory
            if (strlen(file_path) != 0) break;
        } else {
            // if the current entity is a file

            // check if the file extension is txt and the file name consists of a single char
            char *file_extension = strrchr(entry->d_name, '.');
            if (!file_extension) continue;
            if (strcmp(file_extension, ".txt") != 0) continue;
            if (strlen(entry->d_name) - 4 != 1) continue;

            // if the file name is the letter to be found
            if (entry->d_name[0] == letter_to_find) {
                // get path to the file
                file_path = get_file_path(dir_path, entry->d_name);

                // if a memory allocation error occurred, return NULL
                if (!file_path) {
                    return NULL;
                }

                break;
            }
        }
    }

    closedir(dir);
    return file_path;
}


int main() {
    char *word = (char *) malloc(WORD_MAX_SIZE * sizeof(char));
    fgets(word, WORD_MAX_SIZE, stdin);
    word[strcspn(word, "\n")] = '\0';

    FILE *result = fopen("result.txt", "w");

    for (size_t i = 0; i < strlen(word); i++) {
        char *file_path = find_file_named_letter(word[i], PATH);
        if (!file_path) {
            fprintf(stderr, "\033[0;31mERROR: Memory allocation error.\033[0m\n");
            return 1;
        }
        if (strlen(file_path) == 0) {
            fprintf(stderr, "\033[0;31mERROR: Files with the name %c.txt were not found.\033[0m\n", word[i]);
            return 1;
        }
        fprintf(result, "%s\n", file_path);
        free(file_path);
    }
    fclose(result);
    free(word);

    return 0;
}

