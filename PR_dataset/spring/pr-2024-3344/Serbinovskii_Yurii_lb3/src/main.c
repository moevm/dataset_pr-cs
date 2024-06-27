#define _GNU_SOURCE


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>


char* requiredFile(FILE* result);
int recTravel(const char* dirname, const char* file, FILE* result);


int main() {
    char dirname[256] = "/.tmp";
    char* file;
    FILE* result;
    result = fopen("result.txt", "w");
    if(result == NULL)
        fprintf(stderr, "Failed to open file.");

    while (1)
    {
        file = requiredFile(result);
        if (recTravel(dirname, file, result) == 0) {
            fprintf(stderr, "Required file is missing.");
            break;
        }
    }

    free(file);
    fclose(result);
    return 0;
}


char* requiredFile(FILE* result){
    char letter = getchar();
    char* file = malloc(sizeof(char)*256);
    if(file == NULL)
        fprintf(stderr, "Allocation failed.");
    if (letter != '\n')
        sprintf(file, "%c.txt", letter);
    else {
        free(file);
        fclose(result);
        exit(0);
    }
    return file;
}


int recTravel(const char* dirname, const char* file, FILE* result) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return 0;
    }

    struct dirent* entity;
    while ((entity = readdir(dir)) != NULL) {
        if (strcmp(entity->d_name, ".") == 0 || strcmp(entity->d_name, "..") == 0) {
            continue;
        }

        if (strcmp(file, entity->d_name) == 0) {
            fprintf(result, "%s/%s\n", dirname, entity->d_name);
            return 1;
        }

        if (entity->d_type == DT_DIR) {
            char path[512];
            sprintf(path, "%s/%s", dirname, entity->d_name);
            if(recTravel(path, file, result) == 1) {
                closedir(dir);
                return 1;
            }
        }
    }

    closedir(dir);
}
