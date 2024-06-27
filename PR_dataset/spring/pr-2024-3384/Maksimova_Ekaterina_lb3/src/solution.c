#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>
#define PATH_NAME 512

int calculate(int neutural, int num1, int num2)
{
    switch (neutural) {
        case 0: return num1 + num2;
        case 1: return num1 * num2;
        default:     return num1;
    }
}
int calculateFile(const char* path, int neutural)
{
    FILE *file = fopen(path, "r");
    int result = neutural;
    int tmp    = 0;

    while (fscanf(file, "%d", &tmp) != EOF) {
        result = calculate(neutural, result, tmp);
    }

    return result;
}
int findNeutural(struct dirent *de){
    if (strcmp(de->d_name, "add") == 0)
        return 0; //for sum
    else if (strcmp(de->d_name, "mul") == 0)
        return 1; //for mult

}

int operation(char* path, int neutural) {
    DIR  *dir = opendir(path);
    char pathToOp[PATH_NAME];
    int cur_value = neutural;
    if(!dir)
        return INT_MAX;
    struct dirent *de = readdir(dir); //element
    while(de){
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
            sprintf(pathToOp, "%s/%s", path, de->d_name); // path
            int neutural2 = findNeutural(de);
            cur_value = calculate(neutural, operation(pathToOp, neutural2), cur_value);
        }
        if(de->d_type == DT_REG ){
            sprintf(pathToOp, "%s/%s", path, de->d_name); // path
            cur_value = calculate(neutural, calculateFile(pathToOp, neutural), cur_value);
        }
        de = readdir(dir);
    }
    closedir(dir);
    return cur_value;
}
int main() {
    int result = operation("tmp", 0);
    FILE *file;
    file = fopen("result.txt", "w");
    fprintf(file, "%d", result);
    fclose(file);
    return 0;
}

