#include <linux/limits.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>
#include <stdio.h>

#define BUFFER 1024
#define LABYRINTH_DIR "labyrinth"
#define RESULT_FILE "result.txt"
#define INCLUDE_REGEX "^\\@include (\\w+\\.\\w+)\n$"

void freeAnswer(char** answer, int pathCounter) {
    for (int i = 0; i < pathCounter; ++i) {
        free(answer[i]);
    }
    free(answer);
}

int isInclude(const char *filename, regmatch_t matchptr[], size_t nmatch) {
    regex_t regexComp;
    if (regcomp(&regexComp, INCLUDE_REGEX, REG_EXTENDED)) {
        return 0;
    }
    int result = regexec(&regexComp, filename, nmatch, matchptr, 0);
    regfree(&regexComp);
    return result == 0;
}

void findFile(const char *startDir, const char *filename, char *pathToFile) {
    DIR *dir = opendir(startDir);
    if (!dir) {
        return;
    }
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        if (de->d_type == DT_REG && strcmp(de->d_name, filename) == 0) {
            snprintf(pathToFile, PATH_MAX, "%s/%s", startDir, de->d_name);
            closedir(dir);
            return;
        }
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            char nextDir[PATH_MAX];
            snprintf(nextDir, PATH_MAX, "%s/%s", startDir, de->d_name);
            findFile(nextDir, filename, pathToFile);
        }
    }
    closedir(dir);
}

int isDeadlock(const char *filename) {
    FILE *f = fopen(filename, "r");
    if (!f) {
        return 1;
    }
    char line[BUFFER];
    fgets(line, BUFFER, f);
    if (strstr(line, "Deadlock")) {
        fclose(f);
        return 1;
    }
    fclose(f);
    return 0;
}

int check(const char *pathToFile, char **answer, int *pathCounter) {
    FILE *f = fopen(pathToFile, "r");
    if (!f) {
        return 0;
    }
    char line[BUFFER];
    regmatch_t matchptr[2];
    int x = 0;
    while (fgets(line, BUFFER, f)) {
        if (strstr(line, "Minotaur")) {
            answer[*pathCounter] = malloc(strlen(pathToFile) + 1);
            if (!answer[*pathCounter]) {
                perror("Memory allocation error");
                return 0;
            }
            strcpy(answer[*pathCounter], pathToFile);
            (*pathCounter)++;
            fclose(f);
            return 1;
        } else if (isInclude(line, matchptr, 2) && x != 1) {
            char newFileName[BUFFER] = {0};
            char pathToNewFile[PATH_MAX] = {0};
            strcat(newFileName, &line[matchptr[1].rm_so]);
            newFileName[strlen(newFileName) - 1] = '\0';
            findFile(LABYRINTH_DIR, newFileName, pathToNewFile);
            if (x != 1 && !isDeadlock(pathToNewFile)) {
                x = check(pathToNewFile, answer, pathCounter);
            }
        }
    }
    if (x == 1) {
        answer[*pathCounter] = malloc(strlen(pathToFile) + 1);
        strcpy(answer[*pathCounter], pathToFile);
        (*pathCounter)++;
    }
    fclose(f);
    return x;
}

int main() {
    char start[PATH_MAX] = "";
    FILE *fp = fopen(RESULT_FILE, "w");
    if (!fp) {
        perror("Error opening file");
        return 1;
    }
    int pathCounter = 0;
    char **answer = malloc(sizeof(char *) * 1000);
    if (!answer) {
        perror("Memory allocation error");
        fclose(fp);
        return 1;
    }
    findFile(LABYRINTH_DIR, "file.txt", start);
    if (!check(start, answer, &pathCounter)) {
        printf("Minotaur not found in labyrinth.\n");
        fclose(fp);
        freeAnswer(answer, pathCounter);
        return 1;
    }
    for (int i = pathCounter - 1; i >= 0; i--) {
        fprintf(fp, "./%s\n", answer[i]);
    }
    fclose(fp);
    freeAnswer(answer, pathCounter);
    return 0;
}
