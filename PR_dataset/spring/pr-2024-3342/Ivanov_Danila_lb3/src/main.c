#include <dirent.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

void memory_error(){
    fprintf(stderr, "Error with memory allocation!");
    exit(1);
}

long long sum(char* str){
    long long res = 0;
    char* istr = strtok(str, " ");
    while (istr != NULL)
    {
        res += atoi(istr);
        istr = strtok (NULL, " ");
    }
    return res;
}

long long pr(char* str){
    long long res = 1;
    char* istr = strtok(str, " ");
    while (istr != NULL)
    {
        res *= atoi(istr);
        istr = strtok (NULL, " ");
    }
    return res;
}

long long list_dir(const char *dirPath, long long result)
{
    DIR *dir = opendir(dirPath);
    if(dir) {
        struct  dirent *de = readdir(dir);
        while (de) {
            char* new_dir = calloc(strlen(dirPath) + 4, sizeof(char));
            char* file_dir;
            char* line = calloc(100, sizeof(char));
            if (new_dir == NULL || line == NULL){
                memory_error();
            }
            FILE *file;
            if (de->d_type == 4 && strstr(de->d_name, "add") != NULL){
                sprintf(new_dir, "%s/%s", dirPath, de->d_name);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += list_dir(new_dir, 0);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= list_dir(new_dir, 0);
                }
            }
            if (de->d_type == 4 && strstr(de->d_name, "mul") != NULL){
                sprintf(new_dir, "%s/%s", dirPath, de->d_name);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += list_dir(new_dir, 1);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= list_dir(new_dir, 1);
                }
            }
            if (de->d_type == 8){
                file_dir = calloc(strlen(dirPath) + strlen(de->d_name) + 3, sizeof(char));
                if (file_dir == NULL){
                    memory_error();
                }
                sprintf(file_dir, "%s/%s", dirPath, de->d_name);
                file = fopen(file_dir, "r");
                fgets(line, 100, file);
                if (dirPath[strlen(dirPath) - 1] == 'd'){
                    result += sum(line);
                }
                if (dirPath[strlen(dirPath) - 1] == 'l'){
                    result *= pr(line);
                }
                fclose(file);
                free(file_dir);
            }
            de = readdir(dir);
            free(line);
            free(new_dir);
        }
    }
    closedir(dir);
    return result;
}

int main(){
    DIR *dir = opendir("./tmp");
    struct  dirent *de = readdir(dir);
    long long result = 0;
    while (de){
        if (strstr(de->d_name, "add") != NULL){
            result = list_dir("./tmp/add", 0);
            break;
        }
        if (strstr(de->d_name, "mul") != NULL){
            result = list_dir("./tmp/mul", 1);
            break;
        }
        de = readdir(dir);
    }
    char * filename = "result.txt";
    FILE *fp = fopen(filename, "w");
    if(fp)
    {
        char result_str[128];
        sprintf(result_str, "%lld", result);
        fputs(result_str, fp);
        fclose(fp);
    }
    closedir(dir);
    return 0;
}
