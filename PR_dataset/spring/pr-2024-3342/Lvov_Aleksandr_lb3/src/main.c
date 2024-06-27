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

void listdir(char * name, long long int * result, int * call);
array * getnumsfile(char * pathtofile);
int getoperation(char * path);
int getresult(array * nums, int operation);

int main() {
    long long int res;
    int call = 0;

    listdir("./tmp", &res, &call);
    FILE * file = fopen("./result.txt", "w");
    if (file == NULL) {
        printf("Cannot open the file!");
        exit(1);
    }
    fprintf(file, "%lld", res);
    fclose(file);
    return 0;
}

void listdir(char *name, long long int * result, int * call) {
    DIR *dir;
    struct dirent *entry;
    char path[MAX_SIZE];

    if (!(dir = opendir(name)))
        return;

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_DIR) {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            snprintf(path, sizeof(path), "%s/%s", name, entry->d_name);
            listdir(path, result, call);
        }
    }

    char strforcopy[sizeof(name)]; // strtok изменяет исходную строку
    strcpy(strforcopy, name);
    enum operation op = getoperation(strforcopy);

    if (*call == 0) { // если мы дошли до папки, в которой нет подпапок
        if (op == ADD) {
            *result = 0;
        } else if (op == MUL){
            *result = 1;
        } else {
            return;
        }
        *call = 1;
    }

    if (op == UNDEFINED){
        return;
    }

    rewinddir(dir);

    while ((entry = readdir(dir)) != NULL) {
        if (entry->d_type == DT_REG) {
            char pathtofile[MAX_SIZE];
            snprintf(pathtofile, sizeof(path), "%s/%s", name, entry->d_name);
            array * nums = getnumsfile(pathtofile);
            int tmpres = getresult(nums, op);
            if (op == ADD) {
                *result += tmpres;
            } else {
                *result *= tmpres;
            }
        }
    }
    closedir(dir);
}

int getoperation(char * path) {
    enum operation op = UNDEFINED;
    char * tmp = strtok(path, "/");
    while (tmp != NULL) {
        if (strcmp(tmp, "add") == 0) {
            op = ADD;
        } else if (strcmp(tmp, "mul") == 0){
            op = MUL;
        }
        tmp = strtok(NULL, "/");
    }
    return op;
}

int getresult(array * nums, int operation) {
    int tmp;
    if (operation == ADD) {
        tmp = 0;
        for (int i = 0; i < nums->size; i++) {
            tmp += nums->arr[i];
        }
    } else {
        tmp = 1;
        for (int i = 0; i < nums->size; i++) {
            tmp *= nums->arr[i];
        }
    }
    return tmp;
}

array * getnumsfile(char * pathtofile) {
    array * nums = (array *)calloc(1, sizeof(array));
    if (nums == NULL) {
        printf("Cannot allocate memory!");
        exit(1);
    }

    int arr[MAX_SIZE];
    int size = 0;
    FILE * file = fopen(pathtofile, "r");
    if (file == NULL) {
        printf("Cannot open file!");
        return NULL;
    }

    while (fscanf(file, "%d", &arr[size++]) == 1) {}

    nums -> arr = arr;
    nums -> size = size - 1;
    fclose(file);
    return nums;
}
