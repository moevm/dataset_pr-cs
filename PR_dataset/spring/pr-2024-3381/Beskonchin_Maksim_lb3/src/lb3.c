#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

typedef struct {
    char words[100];
    int count_symbol;
} Word;

void listFiles(const char* dirname, Word* text, size_t* num) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return;
    }
    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            listFiles(path, text, num);
        }
        else if (entity->d_type == DT_REG && strstr(entity->d_name, ".txt") != NULL){
            char path[100] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);
            FILE *f_input;
            f_input = fopen(path, "r");
            if (f_input != NULL) {
                fscanf(f_input, "%d", &text[*num].count_symbol);
                fgets(text[*num].words, 100, f_input);
                fclose(f_input);
                (*num)++;
            }
        }
        entity = readdir(dir);
    }
    closedir(dir);
}

int compare(const void *a, const void *b) {
    if (((Word*)a)->count_symbol > ((Word*)b)->count_symbol) return 1;
    else if (((Word*)a)->count_symbol < ((Word*)b)->count_symbol) return -1;
    else return 0;
}

int main() {
    Word* text = malloc(sizeof(Word) * 3000);
    size_t num = 0;
    listFiles(".", text, &num);
    qsort(text, num, sizeof(Word), compare);
    FILE *file = fopen("result.txt", "w");
    if (file != NULL) {
        for(size_t j = 0; j < num; j++) {
             fprintf(file, "%d%s\n", text[j].count_symbol, text[j].words);
        }
        fclose(file);
    }
    free(text);
    return 0;
}
