#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

int counter(char* file_name, int flag);
int bypass_mul(char *dirPath);
int bypass_add(char *dirPath);
char* maker(char* direct, char* name);

int main(){
    DIR *first = opendir("./tmp");
    if (first) {
        struct dirent *folder = readdir(first);
        int result;
        while (folder){
            if (strcmp(folder->d_name, "add") == 0) {
                result = bypass_add("./tmp/add");
                break;
            } else if (strcmp(folder->d_name, "mul") == 0){
                result = bypass_mul("./tmp/mul");
                break;
            }
            folder = readdir(first);
        }
        closedir(first);
        FILE *end = fopen("result.txt", "w");
        fprintf(end, "%d\n", result);
        fclose(end);
    }
    return 0;
}

char* maker(char* direct, char* name){
    char* path = malloc((strlen(direct) + strlen(name) + 2) * sizeof(char));
    path[0] = '\0';
    strcat(path, direct);
    strcat(path, "/");
    strcat(path, name);
    return path;
}

int counter(char* file_name, int flag){
    FILE *f = fopen(file_name, "r");
    int current;
    int count1 = 0;
    int count2 = 1;
    if (f != NULL) {
        while (fscanf(f, "%d", &current) == 1) {
            if (flag == 1){
                count1 += current;
            } else if (flag == 2){
                count2 *= current;
            }
        }
        fclose(f);
        if (flag == 1){
            return count1;
        } else {
            return count2;
        }
    }
}

int bypass_mul(char *dirPath){
    DIR *dir = opendir(dirPath);
    int res = 1;
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de){
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                char* path = maker(dirPath, de->d_name);
                if (de->d_type == DT_DIR) {
                    if (strcmp(de->d_name, "add") == 0) {
                        res *= bypass_add(path);
                    } else if (strcmp(de->d_name, "mul") == 0) {
                        res *= bypass_mul(path);
                    }
                } else {
                    res *= counter(path, 2);
                }
                free(path);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return res;
}

int bypass_add(char *dirPath){
    DIR *dir = opendir(dirPath);
    int res = 0;
    if (dir) {
        struct dirent *de = readdir(dir);
        while (de){
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                char* path = maker(dirPath, de->d_name);
                if (de->d_type == DT_DIR ) {
                    if (strcmp(de->d_name, "add") == 0) {
                        res += bypass_add(path);
                    } else if (strcmp(de->d_name, "mul") == 0) {
                        res += bypass_mul(path);
                    }
                } else {
                    res += counter(path, 1);
                }
                free(path);
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return res;
}
