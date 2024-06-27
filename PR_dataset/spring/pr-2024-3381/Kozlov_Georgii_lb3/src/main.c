#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MAX_L 128


int list_dir(const char *dirPath, char *operation){
    DIR *dir = opendir(dirPath);
    long long int sum;
    if (strcmp(operation, "mul") == 0){
        sum = 1; 
    }   
    else{
        sum = 0;
    }
    if(dir) {
        struct  dirent *de = readdir(dir);
        while (de != NULL) {
            if (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                if (de->d_type == DT_DIR){
                    char string[MAX_L] = "";
                    long long int n;
                    strcat(string, dirPath);
                    strcat(string, "/");
                    strcat(string, de->d_name);
                    n = list_dir(string, de->d_name);
                    if (strcmp(operation, "mul") == 0){
                        sum *= n;
                    }
                    else{
                        sum += n;
                    }
                }
                else{
                    long long int n;
                    int f = -1;
                    char string[MAX_L] = "";
                    strcat(string, dirPath);
                    strcat(string, "/");
                    strcat(string, de->d_name);
                    FILE *file = fopen(string, "r");
                    do{
                        f = fscanf(file, "%d", &n);
                        if (strcmp(operation, "mul") == 0 && f == 1){
                            sum *= n; 
                        }   
                        else if (f == 1){
                            sum += n;
                        }
                    }while(f == 1);
                }
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
    return sum;
}


int main(){
    FILE *file = fopen("./result.txt", "w");
    long long int n = list_dir("./tmp", "");
    fprintf(file, "%lld", n);
    return 0;
}
