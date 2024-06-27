#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#define MAX_LEN_PATH 2048

int check(const char* path, int res);
int checkFile(const char* path, int res);

int main(){
    int res = 0;
    DIR* dir;
    struct dirent* de;
    char fullPath[MAX_LEN_PATH];
    dir = opendir("./tmp");
    if (dir){
        while ((de = readdir(dir)) != NULL){
            if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
                continue;
            }
            sprintf(fullPath, "%s/%s", "./tmp", de->d_name);
            if (strcmp(de->d_name, "add") == 0){
                res = check(fullPath, 0);
            } else if (strcmp(de->d_name, "mul") == 0){
                res = check(fullPath, 1);
            }
        }
    }
    closedir(dir);
    FILE* f = fopen("./result.txt", "w");
    fprintf(f, "%d\n", res);
    fclose(f);
    return 0;
}

int check(const char* path, int res){
    int add_mul = res;
    DIR* dir;
    struct dirent* de;
    char fullPath[MAX_LEN_PATH];
    dir = opendir(path);
    if (!dir){ 
        return 0;
    }
    while ((de = readdir(dir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
            continue;
        }
        sprintf(fullPath, "%s/%s", path, de->d_name);
        if (add_mul == 0){
            if (strcmp(de->d_name, "add") == 0){
                res += check(fullPath, 0);
            } else if (strcmp(de->d_name, "mul") == 0){
                res += check(fullPath, 1);
            } else if (de->d_type == DT_REG){
                res += checkFile(fullPath, 0);
            }
        } else{
            if (strcmp(de->d_name, "add") == 0){
                res *= check(fullPath, 0);
            } else if (strcmp(de->d_name, "mul") == 0){
                res *= check(fullPath, 1);
            } else if (de->d_type == DT_REG){
                res *= checkFile(fullPath, 1);
            }
        }
    }
    closedir(dir);
    return res;
}

int checkFile(const char* path, int res){
    FILE* f1 = fopen(path, "r");
    int num;
    if(res == 0){
        while (fscanf(f1, "%d", &num) == 1) {
            res += num;
        }
    } else{
        while (fscanf(f1, "%d", &num) == 1) {
            res *= num;
        }
    }
    fclose(f1);
    return res;    
}