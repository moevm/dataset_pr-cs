#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define MAX_FILENAME 128
#define MAX_PATH 256

char **array = NULL;
int size = 0;

int file_validator(char *filename) {
    int res = 1;
    if (strstr(filename, ".txt") == NULL) {
        res = 0;
    }
    return res;
}

int dir_validator(char *dirname) {
    int res = 0;
    if(strcmp(dirname, ".") && strcmp(dirname, "..")) {
        res = 1;
    }
    return res;
}

void read_file(char *filepath) {
    size++;
    FILE *f = fopen(filepath, "r");
    if (f == NULL) {
        printf("Не удалось открыть файл %s\n", filepath);
        return;
    }
    char sentence[MAX_PATH];
    fgets(sentence, sizeof(sentence), f);

    char **temp_array = (char **)realloc(array, size * sizeof(char *));
    if (temp_array == NULL) {
        printf("Не удалось выделить память\n");
        fclose(f);
        return;
    }
    array = temp_array;

    array[size - 1] = (char *)malloc((strlen(sentence) + 1) * sizeof(char));
    if (array[size - 1] == NULL) {
        printf("Не удалось выделить память\n");
        fclose(f);
        return;
    }
    strcpy(array[size - 1], sentence);
    fclose(f);
}

void dir_lookup(char *root) {
    char tmp_dir[MAX_PATH];
    strncpy(tmp_dir, root, MAX_FILENAME);

    DIR *root_dir = opendir(tmp_dir);
    if (root_dir == NULL) {
        return;
    }
    struct dirent *dir = readdir(root_dir);

    while (dir) {
        if (dir->d_type == DT_REG && file_validator(dir->d_name)) {
            if (strlen(dir->d_name) > MAX_FILENAME) {
                perror("Слишком большая длина имени");
                exit(0);
            }
            strncat(tmp_dir, "/", strlen(tmp_dir) + 1);
            strncat(tmp_dir, dir->d_name, strlen(dir->d_name));

            read_file(tmp_dir);
            tmp_dir[strlen(tmp_dir) - 1 - strlen(dir->d_name)] = '\0'; 

        } else if (dir->d_type == DT_DIR && dir_validator(dir->d_name)) {
            if (strlen(dir->d_name) > MAX_FILENAME) {
                perror("Слишком большая длина имени");
                exit(0);
            }
            strncat(tmp_dir, "/", strlen(tmp_dir) + 1);
            strncat(tmp_dir, dir->d_name, strlen(dir->d_name));
            printf("DIR: [%s]\n", tmp_dir);

            dir_lookup(tmp_dir);   
            tmp_dir[strlen(tmp_dir) - 1 - strlen(dir->d_name)] = '\0';      
        }
        dir = readdir(root_dir);
    }
    closedir(root_dir);
}

int compare(const void *a, const void *b) {
    const char *sentenceA = *(const char **)a;
    const char *sentenceB = *(const char **)b;
    int numberA, numberB;
    sscanf(sentenceA, "%d", &numberA);
    sscanf(sentenceB, "%d", &numberB);
    if (numberA < numberB) {
        return -1;
    } else if (numberA > numberB) {
        return 1;        
    } else {
    return 0;  
    }
}

void sortSentences(char **sentences, int numSentences) {
    qsort(sentences, numSentences, sizeof(char *), compare);
}

int main() {
    dir_lookup("./root");
    sortSentences(array, size);

    FILE *f = fopen("result.txt", "w");
    for (int i = 0; i < size; i++) {
        if (f == NULL) {
            printf("Не удалось открыть файл");
            return 0;
        }
        fputs(array[i], f);
        fputs("\n", f);
        free(array[i]);
    }

    fclose(f);
    free(array);
    return 0;
}