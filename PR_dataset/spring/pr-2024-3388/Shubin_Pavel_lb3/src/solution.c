#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <dirent.h>
#include <unistd.h>

#define MAX_LEN 1024
#define OUTPUT_FILE "result.txt"
#define EXTENSION ".txt"
#define NEXT_DIR "%s/%s"
#define CURR "."
#define PREV ".."
#define READ_MODE "r"
#define WRITE_MODE "w+"

int cmp(const void * str_to_cmp_first, const void  * str_to_cmp_second);
void read_text(const char * cur_path, char *** strs, int * p_cnt);
void start_search();

int main() {
    start_search();
    return 0;
}

int cmp (const void * str_to_cmp_first, const void * str_to_cmp_second) {
    char **first = (char **) str_to_cmp_first;
    char **second = (char **) str_to_cmp_second;
    long tmp_1 = atol(*first);
    long tmp_2 = atol(*second);
    if (tmp_1 < tmp_2) return -1;
    if (tmp_1 > tmp_2) return 1;
    return 0;
}

void read_text(const char * cur_path, char *** strs, int * p_cnt) {
    DIR *dir = opendir(cur_path);
    if (!dir) {
        perror(cur_path);
        exit(EXIT_FAILURE);
    }

    struct dirent * ent;
    while ((ent = readdir(dir))) {
        char path[MAX_LEN];
        sprintf(path, NEXT_DIR, cur_path, ent->d_name);

        if (ent->d_type == DT_DIR) {
            if (strcmp(ent->d_name, PREV) == 0 || strcmp(ent->d_name, CURR) == 0) {
                continue;
            }
            read_text(path, strs, p_cnt);
        }

        if (strstr((ent->d_name), OUTPUT_FILE)) {
            continue;
        }

        if (ent->d_type == DT_REG && strstr(ent->d_name, EXTENSION)) {
            FILE *file;
            file = fopen(path, READ_MODE);

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

void start_search(){
    char cur_path[MAX_LEN];
    if (!getcwd(cur_path, sizeof(cur_path))) {
        perror("getcwd");
        exit(EXIT_FAILURE);
    }

    int cnt = 0;
    int *p_cnt = &cnt;

    char ** strs;
    strs = malloc(sizeof(char *));

    read_text(cur_path, &strs, p_cnt);
    qsort(strs, (*p_cnt), sizeof(char *), (int (*)(const void *, const void *)) cmp);

    char end[] = "/result.txt";
    strcat(cur_path, end);
    FILE *file = fopen(cur_path, WRITE_MODE);

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
}
