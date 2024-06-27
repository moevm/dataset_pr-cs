#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_LEN 1024

int cmp (const void * s1, const void * s2) {
    char **str_a = (char **) s1;
    char **str_b = (char **) s2;
    long a = atol(*str_a);
    long b = atol(*str_b);
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

void readText(const char * cur_path, char *** strs, int * p_cnt) {
    DIR *dir = opendir(cur_path);
    if (!dir) {
        perror(cur_path);
        exit(EXIT_FAILURE);
    }

    struct dirent * ent;
    while ((ent = readdir(dir))) {
        char path[MAX_LEN];
        sprintf(path, "%s/%s", cur_path, ent->d_name);

        if (ent->d_type == DT_DIR) {
            if (strcmp(ent->d_name, "..") == 0 || strcmp(ent->d_name, ".") == 0) {
                continue;
            }
            readText(path, strs, p_cnt);
        }

        if (strstr((ent->d_name), "result.txt")) {
            continue;
        }

        if (ent->d_type == DT_REG && strstr(ent->d_name, ".txt")) {  
            FILE *file;
            file = fopen(path, "r");

            if (file) {
                char *str = malloc(sizeof(char));
                char symbol;
                int str_len = 0;
                while ((symbol = fgetc(file)) != EOF) {
                    str[str_len++] = symbol;
                    str = realloc(str, (str_len + 1)*sizeof(char));
                }
                str[str_len] = '\0';

                (*strs)[(*p_cnt)] = str;
                (*p_cnt)++;
                *strs = (char **) realloc(*strs, (*p_cnt + 1)*sizeof(char *));
                fclose(file);
            }
        }
    }
    closedir(dir);
}

int main() {
    char cur_path[MAX_LEN];
    if (!getcwd(cur_path, sizeof(cur_path))) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int *p_cnt = &cnt;

    char ** strs;
    strs = malloc(sizeof(char *));

    readText(cur_path, &strs, p_cnt);
    qsort(strs, (*p_cnt), sizeof(char *), (int (*)(const void *, const void *)) cmp);
    
    char end[] = "/result.txt";
    strcat(cur_path, end);
    FILE *file = fopen(cur_path, "w+");

    for (int i = 0; i < (*p_cnt); i++) {
        if (!i) {
            fprintf(file, "%s", strs[0]);
        } else {
            fprintf(file, "\n%s", strs[i]);
        }
        free(strs[i]);
    }

    free(strs);
    fclose(file);
    return 0;
}
