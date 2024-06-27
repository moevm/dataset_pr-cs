#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#include <libgen.h>
 
#define FILE_OPEN_ERROR "couldn't open this file or directory"
#define MEMORY_ALLOCATION_ERROR "memory allocation failed"
 
char* processString(char* str) {
    char* newline = strchr(str, '\n');
    if (newline) {
        *newline = '\0';
    }
 
    char* lastSpace = strrchr(str, ' ');
    if (lastSpace) {
        *lastSpace = '\0';
    }
 
    if (strcmp(str, "Deadlock") == 0) {
        return "Deadlock";
    } else if (strcmp(str, "Minotaur") == 0) {
        return "Minotaur";
    } else if (strstr(str, "@include") == str) {
        return str + 9;
    } else {
        return "Unknown string";
    }
}
 
char* findFileByName(const char *dirPath, const char* fileName) {
    DIR *dir = opendir(dirPath);
    if(dir == NULL) {
        perror(FILE_OPEN_ERROR);
        return NULL;
    }

    struct dirent *de;

    while ((de = readdir(dir)) != NULL) {
        if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) {
            continue;
        }

        char newDirPath[512];
        snprintf(newDirPath, sizeof(newDirPath), "%s/%s", dirPath, de->d_name);

        if (strcmp(basename(newDirPath), fileName) == 0) {
            char *result = malloc(strlen(newDirPath) + 1);
            if (result == NULL) {
                perror(MEMORY_ALLOCATION_ERROR);
                exit(EXIT_FAILURE);
            }
            strcpy(result, newDirPath);
            closedir(dir);
            return result;
        }

        if(de->d_type == DT_DIR) {
            char *found = findFileByName(newDirPath, fileName);
            if (found != NULL) {
                closedir(dir);
                return found;
            }
        }
    }

    closedir(dir);
    return NULL;
}
 
char** readFile(char* filename) {
 
    char** pathNames = malloc(1 * sizeof(char*));
    int len = 0;
    FILE* file = fopen(filename, "r");
 
    if (file == NULL) {
        printf(FILE_OPEN_ERROR);
        return NULL;
    }
 
    char* stringInFile = malloc(200);
 
    while (fgets(stringInFile, 200, file)) {
        pathNames[len] = malloc(strlen(stringInFile) + 1);
        if (pathNames[len] == NULL) {
            perror(MEMORY_ALLOCATION_ERROR);
            exit(EXIT_FAILURE);
        }
        strcpy(pathNames[len++], stringInFile);
        pathNames = realloc(pathNames, (len + 1) * sizeof(char*));
        if (pathNames == NULL) {
            perror(MEMORY_ALLOCATION_ERROR);
            exit(EXIT_FAILURE);
        }
    }
 
    free(stringInFile);
    pathNames[len] = NULL;
 
    return pathNames;
}
 
void findMinotaur(char* filename, int* wasFound, char*** visitedFiles, int* visitedCount) {
    if (*wasFound) {
        return;
    }

    char* foundFile = findFileByName("./labyrinth", filename);
    if (foundFile == NULL) {
        printf(FILE_OPEN_ERROR);
        return;
    }
 
    *visitedFiles = realloc(*visitedFiles, (*visitedCount + 1) * sizeof(char*));

    if (*visitedFiles == NULL) {
        perror(MEMORY_ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }

    (*visitedFiles)[*visitedCount] = foundFile;
    (*visitedCount)++;
 
    char** foundFiles = readFile(foundFile);
    char* argToFind = malloc(1000);
 
    for (int i = 0; foundFiles[i]; i++) {
        strcpy(argToFind, processString(foundFiles[i]));
        if (strcmp(argToFind, "Minotaur") == 0) {
            *wasFound = 1;
            free(argToFind);
            for (int j = 0; foundFiles[j]; j++) {
                free(foundFiles[j]);
            }
            free(foundFiles);
            return;
        }
        if (strcmp(argToFind, "Deadlock") == 0) {
            free(argToFind);
            for (int j = 0; foundFiles[j]; j++) {
                free(foundFiles[j]);
            }
            (*visitedCount)--;
            free((*visitedFiles)[*visitedCount]);
            *visitedFiles = realloc(*visitedFiles, (*visitedCount) * sizeof(char*));
            if (*visitedFiles == NULL && *visitedCount > 0) {
                perror(MEMORY_ALLOCATION_ERROR);
                exit(EXIT_FAILURE);
            }
            free(foundFiles);
            return;
        }
 
        findMinotaur(argToFind, wasFound, visitedFiles, visitedCount);
 
        if (*wasFound) {
            free(argToFind);
            for (int j = 0; foundFiles[j]; j++) {
                free(foundFiles[j]);
            }
            free(foundFiles);
            return;
        }
    }
 
    free(argToFind);
    for (int j = 0; foundFiles[j]; j++) {
        free(foundFiles[j]);
    }
    free(foundFiles);
 
    (*visitedCount)--;
    free((*visitedFiles)[*visitedCount]);
    *visitedFiles = realloc(*visitedFiles, (*visitedCount) * sizeof(char*));
    if (*visitedFiles == NULL && *visitedCount > 0) {
        perror(MEMORY_ALLOCATION_ERROR);
        exit(EXIT_FAILURE);
    }
}
 
int main() {

    int wasFound = 0;
    char** visitedFiles = NULL;
    int visitedCount = 0;
 
    findMinotaur("file.txt", &wasFound, &visitedFiles, &visitedCount);
 
    FILE *file = fopen("result.txt", "w");
    if (file == NULL) {
        printf(FILE_OPEN_ERROR);
    }
 
    for (int i = 0; i < visitedCount; i++) {
        if (i < visitedCount - 1) {
            fprintf(file, "%s\n", visitedFiles[i]);
        } else {
            fprintf(file, "%s", visitedFiles[i]);
        }
        free(visitedFiles[i]);
    }
    free(visitedFiles);
 
    return 0;
}

