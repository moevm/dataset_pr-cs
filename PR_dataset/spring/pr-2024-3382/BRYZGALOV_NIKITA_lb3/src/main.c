#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char * pathfinding(char letter, char * file_path);

int main() {
    char * word = malloc(sizeof(char) * 1000);
    fgets(word, 1000, stdin);
    int num_letters = strlen(word) -1;
    char * file_path = "./tmp";
    FILE * result = fopen("result.txt", "w");
    int i;
    for (i = 0; i < num_letters; i++) {
        char * result_path = pathfinding(word[i], file_path);
        fprintf(result, "%s\n", result_path);
        free(result_path);
    }
    fclose(result);
}

char * pathfinding(char letter, char * file_path) {
    DIR * directory = opendir(file_path);
    if (directory) {
        struct dirent * object = readdir(directory);
        while (object) {
            char * name = object->d_name;
            char new_file_path[strlen(name) + strlen(file_path) + 1];
            strcpy(new_file_path, file_path);
            strcat(new_file_path, "/");
            strcat(new_file_path, name);
                
            if ((object->d_type == DT_DIR) && strcmp(name, ".") && strcmp(name, "..")) {
                if (pathfinding(letter, new_file_path) != NULL)
                    return pathfinding(letter, new_file_path);
            } 
            else if (strlen(name) == 5 && name[0] == letter) {
                char * result_path = malloc(sizeof(char) * (strlen(new_file_path) + 5));
                strcpy(result_path, new_file_path);
                return result_path;
            }
            object = readdir(directory);
        }
    }
    closedir(directory);
}