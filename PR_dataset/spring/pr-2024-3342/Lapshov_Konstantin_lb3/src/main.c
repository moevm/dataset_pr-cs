#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


typedef struct fileItem{
    long number;
    char* massage;
}fileItem;

void memoryError(){
    printf("Memory allocation error!");
    exit(0);
}
void fileError(){
    printf("File open error!");
    exit(0);
}

int
comparator(const void *a, const void *b) {
    const fileItem *item_a = a;
    const fileItem *item_b = b;
    if (item_a->number < item_b->number)
        return -1;
    if (item_a->number > item_b->number)
        return 1;
    return 0;
}
fileItem*
getDataFromFile(char *filepath){
    fileItem* newFileItem = malloc(sizeof(fileItem));
    if(newFileItem == NULL){
        memoryError();
    }

    newFileItem->number = 0;
    newFileItem->massage = NULL;

    FILE* currentFile = fopen(filepath, "r");
    if(currentFile == NULL){
        fclose(currentFile);
        fileError();
    }

    //Считываем цифру
    char stringNumber[64];
    char *endPtr;

    if(fscanf(currentFile, "%s", stringNumber) != -1){
        newFileItem->number = strtol(stringNumber, &endPtr, 10);
    };

    //Пропускаем символ
    char c = fgetc(currentFile);

    //Считываем текст
    size_t n = 0;
    size_t capacity = 16;
    char *text = malloc(capacity);
    if(text == NULL){
        memoryError();
    }

    while ((c = fgetc(currentFile)) != EOF && c != '\n') {
        if (n + 1 >= capacity) {
            capacity *= 2;
            text = realloc(text, capacity);
            if(text == NULL){
                memoryError();
            }
        }
        text[n++] = c;
    }
    text[n] = '\0';
    newFileItem->massage = text;

    fclose(currentFile);

    return newFileItem;
}





void dirLookup(const char* dir_name, fileItem** currentArr, size_t * sizeOfArr){
    DIR* dir = opendir(dir_name);
    struct dirent* de;
    while(de = readdir(dir)){
        if(de->d_type == 8 && strstr(de->d_name, ".txt")){

            char str[120];
            strcpy(str, dir_name);
            strcat(str, "/");
            strcat(str, de->d_name);

            fileItem* newFileItem = getDataFromFile(str);
            if(newFileItem->number != 0){
                *currentArr = realloc(*currentArr, sizeof(fileItem)* ((*sizeOfArr)+1));
                if(currentArr == NULL){
                    memoryError();
                }

                (*currentArr)[(*sizeOfArr)] = *newFileItem;
                (*sizeOfArr)++;
            }
        }
        if(de->d_type == 4 && strcmp(de->d_name, ".") && strcmp(de->d_name, "..")){
            char* str = calloc(120, sizeof(char));
            if(str == NULL){
                memoryError();
            }

            strcpy(str, dir_name);
            strcat(str, "/");
            strcat(str, de->d_name);
            dirLookup(str, currentArr, sizeOfArr);
            free(str);
        }
    }
    closedir(dir);
}

int
main(){
    size_t sizeOfArr = 0;
    fileItem * fileItemArr = malloc(sizeof(fileItem));
    if(fileItemArr == NULL){
        memoryError();
    }


    dirLookup("./", &fileItemArr, &sizeOfArr);

    qsort(fileItemArr, sizeOfArr, sizeof(fileItem), comparator);

    FILE* file = fopen("result.txt","w+");
    if(file == NULL){
        fclose(file);
        fileError();
    }

    for (int i = 0; i < sizeOfArr; i++) {
        fprintf(file,"%ld %s\n", fileItemArr[i].number, fileItemArr[i].massage);
    }

    fclose(file);

    for (int i = 0; i < sizeOfArr; i++) {
        free(fileItemArr[i].massage);
    }
    free(fileItemArr);

    return 0;
}