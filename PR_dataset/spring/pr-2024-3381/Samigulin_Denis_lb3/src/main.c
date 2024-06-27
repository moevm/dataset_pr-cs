#include <stdio.h>
#include <dirent.h>
#include <string.h>

int isDirectory(const char *path) {
    DIR *directory = opendir(path);
    if (directory) {
        closedir(directory);
        return 1;
    }
    return 0;
}

void getFullPath(const char *directoryPath, const char *name, char *fullPath) {
    strcpy(fullPath, directoryPath);
    strcat(fullPath, "/");
    strcat(fullPath, name);
}

long long int calculateResult(long long int currentResult, long long int subResult, const char *operation) {
    if (strcmp(operation, "mul") == 0) {
        return currentResult * subResult;
    } else {
        return currentResult + subResult;
    }
}

long long int calculateExpressionRecursively(const char *directoryPath, const char *operation) {
    DIR *directory = opendir(directoryPath);
    long long int result = (strcmp(operation, "mul") == 0) ? 1 : 0;
    if (directory) {
        struct dirent *directoryEntry;
        while ((directoryEntry = readdir(directory)) != NULL) {
            if (strcmp(directoryEntry->d_name, ".") != 0 && strcmp(directoryEntry->d_name, "..") != 0) {
                char fullPath[1000];
                getFullPath(directoryPath, directoryEntry->d_name, fullPath);
                if (isDirectory(fullPath)) {
                    long long int subResult = calculateExpressionRecursively(fullPath, directoryEntry->d_name);
                    result = calculateResult(result, subResult, operation);
                } else {
                    FILE *file = fopen(fullPath, "r");
                    if (file) {
                        long long int subResult;
                        while (fscanf(file, "%lld", &subResult) == 1) {
                            result = calculateResult(result, subResult, operation);
                        }
                        fclose(file);
                    }
                }
            }
        }
        closedir(directory);
    }
    return result;
}

long long int calculateExpression(const char *directoryPath, const char *operation) {
    return calculateExpressionRecursively(directoryPath, operation);
}

void saveResultToFile(const char *filePath, long long int result) {
    FILE *file = fopen(filePath, "w");
    if (file) {
        fprintf(file, "%lld", result);
        fclose(file);
    }
}

int main() {
    long long int result = calculateExpression("./tmp", "mul");
    saveResultToFile("./result.txt", result);
    return 0;
}