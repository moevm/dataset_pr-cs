#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define START_PATH "./labyrinth"

typedef struct ContainerString
{
    int size;
    int capacity;
    char** array;
} ContainerString;

void pushBack(ContainerString* v, char* el)
{
    if (v->size >= v->capacity) {
        v->capacity = (v->size == 0) ? 2 : v->capacity*v->capacity;
        v->array = realloc(v->array, v->capacity*sizeof(char*));
        if (v->array == NULL){
            exit(0);
        }
    }
    v->array[v->size++] = el;
}

ContainerString* getDataFromFile(char* file_path)
{
    ContainerString* content = (ContainerString*) calloc(1, sizeof(ContainerString));
    if (content == NULL){
        exit(0);
    }
    FILE* fin = fopen(file_path, "r");

    char* string = (char*) malloc(128*sizeof(char));
    if (string == NULL){
        exit(0);
    }
    while (fgets(string, 128, fin)) {
        if (strchr(string, '\n')) {
            *(strchr(string, '\n')) = '\0';
        }
        pushBack(content, string);
        string = (char*) malloc(128*sizeof(char));
        if (string == NULL){
            exit(0);
        }
    }

    fclose(fin);
    free(string);
    free(content);
    return content;
}

void output(char* file_path, char* labyrinth_path)
{
    FILE* fout = fopen(file_path, "w");
    if (fout == NULL){
        exit(0);
    }
    fprintf(fout, labyrinth_path, "%s\n");
    fclose(fout);
}

char* joinStrings(char* str1, char* str2, char symbol)
{
    char* subPath = (char*) calloc((strlen(str1) + strlen(str2) + 2), sizeof(char));
    if (subPath == NULL){
        exit(0);
    }
    strcpy(subPath, str1);
    if (strcmp(str1, "") != 0) {
        subPath[strlen(str1)] = symbol;
    }
    strcat(subPath, str2);
    return subPath;
}

void process(char* dir_name, char* target_file_name, char* labyrinth_path)
{
    DIR* dir = opendir(dir_name);
    if (dir == NULL){
        exit(0);
    }

    struct dirent* de;

    while ( de = readdir(dir) ) {

        if (de->d_type == DT_DIR) {

            if ((strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)) {
                process(joinStrings(dir_name, de->d_name, '/'), target_file_name, labyrinth_path);
            }
        }

        if (de->d_type == DT_REG && (strcmp(de->d_name, target_file_name) == 0)) {

            char* subPath = joinStrings(dir_name, target_file_name, '/');
            ContainerString* data = getDataFromFile(subPath );


            if (strcmp(data->array[0], "Deadlock") == 0) {
                closedir(dir);
                for (int i = 0; i < data->size; i++){
                    free(data->array[i]);
                }
                free(data->array);
                free(data);
                return;
            }
            if (strcmp(data->array[0], "Minotaur") == 0) {
                output("result.txt", joinStrings(labyrinth_path, subPath, '\n'));
                closedir(dir);
                for (int i = 0; i < data->size; i++){
                    free(data->array[i]);
                }
                free(data->array);
                free(data);

            } else {
                for (int i=0; i<data->size; i++) {
                    process(START_PATH, strchr(data->array[i], ' ') + 1,
                            joinStrings(labyrinth_path, subPath, '\n'));
                }
            }
            closedir(dir);
            for (int i = 0; i < data->size; i++){
                free(data->array[i]);
            }
            free(data->array);
            free(data);
        }
    }
}


int main()
{
    process(START_PATH, "file.txt", "");
}
