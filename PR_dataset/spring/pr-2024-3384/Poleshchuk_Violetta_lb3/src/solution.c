#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_SIZE 1024

enum operation {
    ADD,
    MUL,
    UNDEFINED
};

typedef struct array {
    int * arr;
    int size;
} array;

array* getnum(char* path);
int operationfile(char* path);
int getfileresult(array* num, int currOperation);
void listOfDir(char* name, long long int* result, int* call);

void listOfDir(char* name, long long int* result, int* call){
    DIR* dir;
    struct dirent *entry;
    char path[MAX_SIZE];

    dir = opendir(name);
    if (dir == NULL) {
        perror("Unable to open directory");
        exit(EXIT_FAILURE);
    }

    while((entry = readdir(dir)) != NULL){
        if(entry->d_type == DT_DIR){
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0){
                continue;
            }
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listOfDir(path, result, call);
        }
    }

    char copy[sizeof(name)];
    strcpy(copy, name);
    enum operation currOperation = operationfile(copy);

    if (*call == 0){
        if (currOperation == ADD){
            *result = 0;
        }else if(currOperation == MUL){
            *result = 1;
        } else{
            return;
        }
        *call = 1;
    }
    rewinddir(dir);

    while((entry = readdir(dir)) != NULL){
        if (entry->d_type == DT_REG){
            char pathFile[MAX_SIZE];
            snprintf(pathFile, sizeof(pathFile), "%s/%s", name, entry->d_name);
            array* num = getnum(pathFile);
            int res = getfileresult(num, currOperation);
            if(currOperation == ADD){
                *result += res;
            }else{
                *result *= res;
            }
        }
    }
    closedir(dir);
}

int getfileresult(array* num, int currOperation){
    int res;
    if (currOperation == ADD){
        res = 0;
        int i;
        for (i = 0; i < num->size; i++){
            res += num->arr[i];
        }
    }else{
        res = 1;
        int i;
        for (i = 0; i < num->size; i++){
            res *= num->arr[i];
        }
    }
    return res;
}

array* getnum(char* path) {
    array *num = (array *)malloc(sizeof(array));
    if (num == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    num->arr = (int *)malloc(MAX_SIZE * sizeof(int));
    if (num->arr == NULL) {
        perror("Memory allocation failed");
        exit(EXIT_FAILURE);
    }

    FILE *file = fopen(path, "r");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }

    int size = 0;
    while (fscanf(file, "%d", &num->arr[size]) == 1) {
        size++;
        if (size >= MAX_SIZE) {
            fprintf(stderr, "Array is too big!\n");
            exit(EXIT_FAILURE);
        }
    }

    num->size = size;
    fclose(file);
    return num;
}


int operationfile(char* path){
    enum operation currOperation = UNDEFINED;
    char* token = strtok(path, "/");
    while(token != NULL){
        if (strcmp(token, "mul") == 0){
            currOperation = MUL;
        }else if(strcmp(token, "add") == 0){
            currOperation = ADD;
        }
        token = strtok(NULL, "/");
    }
    return currOperation;
}

int main(){
    long long int result;
    int call = 0;
    listOfDir("./tmp", &result, &call);
    FILE * file = fopen("./result.txt", "w");
    if (file == NULL) {
        perror("Unable to open file");
        exit(EXIT_FAILURE);
    }
    fprintf(file, "%lld", result);
    fclose(file);
    return 0;
}