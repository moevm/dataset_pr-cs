#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>


#define VAL1 200
#define VAL2 2000


char ans[VAL1][VAL2];
char word[VAL1];


void rec(char* path) {
    char newPath[VAL2];
    DIR* dir = opendir(path);
    if (!dir) {
        return;
    }
    struct dirent* dp;
    while ((dp = readdir(dir)) != NULL) {
        if (strcmp(dp->d_name, ".") != 0 && strcmp(dp->d_name, "..") != 0) {
            snprintf(newPath, sizeof(newPath), "%s/%s", path, dp->d_name);
            struct stat statbuf;
            if (stat(newPath, &statbuf) == -1) {
                perror("Ошибка при получении информации о файле");
                continue;
            }
            if (S_ISREG(statbuf.st_mode)) {
                if (strlen(dp->d_name) != 5) {
                    continue;
                }
                for (int i = 0; i < strlen(word); i++) {
                    if (word[i] == dp->d_name[0]) {
                        strcpy(ans[i], newPath);
                        break;
                    }
                }
            }
            if (S_ISDIR(statbuf.st_mode)) {
                rec(newPath);
            }
        }
    }
    closedir(dir);
}


int main() {
    fgets(word, VAL1, stdin);
    char* path = "./tmp";
    rec(path);
    FILE* file = fopen("result.txt", "w");
    if (file == NULL) {
        printf("Ошибка при открытии файла.\n");
        return 1;
    }
    for (int i = 0; i < strlen(word); i++) {
        fprintf(file, "%s\n", ans[i]);
    }
    fclose(file);
    return 0;
}