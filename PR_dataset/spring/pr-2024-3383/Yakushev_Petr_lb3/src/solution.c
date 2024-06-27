#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int ProMul(char *path);

int SumAdd(char* path){
    int sum=0;
    DIR *directory = opendir(path);
    if (directory){
        struct dirent *de = readdir(directory);
        while (de){
            if (strcmp(de->d_name,"add")==0){
                char* new_path=malloc(sizeof(char)*(strlen(path)+5));
                strcpy(new_path,path);
                strcat(new_path,"add/");
                sum+=SumAdd(new_path);
            }
            else {
                if (strcmp(de->d_name, "mul") == 0) {
                    char *new_path = malloc(sizeof(char) * (strlen(path) + 5));
                    strcpy(new_path, path);
                    strcat(new_path, "mul/");
                    sum += ProMul(new_path);
                } 
                else {
                    if (strstr(de->d_name, ".txt") != 0) {
                        char *new_path = malloc(sizeof(char) * (strlen(path) + strlen(de->d_name) + 1));
                        strcpy(new_path, path);
                        strcat(new_path, de->d_name);
                        FILE *file = fopen(new_path, "r");
                        int ch;
                        while (fscanf(file, "%d", &ch) == 1) {
                            sum += ch;
                        }
                        fclose(file);
                    }
                }
            }
            de = readdir(directory);
        }
        closedir(directory);
    }
    return sum;
}

int ProMul(char* path){
    int pro=1;
    DIR *directory=opendir(path);
    if (directory){
        struct dirent *de=readdir(directory);
        while (de){
            if (strcmp(de->d_name,"add")==0){
                char* new_path=malloc(sizeof(char)*(strlen(path)+5));
                strcpy(new_path,path);
                strcat(new_path,"add/");
                pro=pro*SumAdd(new_path);
            }
            else {
                if (strcmp(de->d_name, "mul") == 0) {
                    char *new_path = malloc(sizeof(char) * (strlen(path) + 5));
                    strcpy(new_path, path);
                    strcat(new_path, "mul/");
                    pro = pro * ProMul(new_path);
                } else {
                    if (strstr(de->d_name, ".txt") != 0) {
                        char *new_path = malloc(sizeof(char) * (strlen(path) + strlen(de->d_name) + 1));
                        strcpy(new_path, path);
                        strcat(new_path, de->d_name);
                        FILE *file = fopen(new_path, "r");
                        int ch;
                        while (fscanf(file, "%d", &ch) == 1) {
                            pro = pro * ch;
                        }
                        fclose(file);
                    }
                }
            }
            de = readdir(directory);
        }
        closedir(directory);
    }
    return pro;
}
int main(){
    int result=0;
    DIR *directory = opendir("./tmp");
    if (directory){
        struct dirent *de = readdir(directory);
        while (de){
            if (strcmp(de->d_name,"add")==0){
                result=SumAdd("./tmp/add/");
                break;
            }
            else {
                if (strcmp(de->d_name, "mul") == 0) {
                    result = ProMul("./tmp/mul/");
                    break;
                }
            }
            de = readdir(directory);
        }
        closedir(directory);
    }
    FILE *file;
    file = fopen("result.txt", "w");
    if (file){
        fprintf(file, "%d\n", result);
        fclose(file);
    }
    return 0;
}
