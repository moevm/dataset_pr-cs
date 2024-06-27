
#include <dirent.h>
#include <stdio.h>
#include <string.h>


int check_dir(const char *dir_path, int is_add) {
    int result;
    int rec_result = 0;
    if (is_add == 0) rec_result = 1;

    DIR *dir = opendir(dir_path);
    struct dirent *de;
    while ((de = readdir(dir)) != NULL) {
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0) continue;
        char new_path[PATH_MAX];
        sprintf(new_path, "%s/%s", dir_path, de->d_name);
        if (de->d_type == DT_REG) {
            FILE *fptr = fopen(new_path, "r");
            int value;
            while (!feof(fptr)) {
                fscanf(fptr, "%d", &value);
                if (is_add == 1) rec_result += value;
                else rec_result *= value;
            }
            fclose(fptr);
        }
        if (de->d_type == DT_DIR) {
            if (strcmp(de->d_name, "add") == 0) result = check_dir(new_path, 1);
            else if (strcmp(de->d_name, "mul") == 0) result = check_dir(new_path, 0);

            if (is_add == 1) rec_result += result;
            else if (is_add == 0) rec_result *= result;
            else return result;
        }
    }
    closedir(dir);
    return rec_result;
}


int main() {

    int test = check_dir("root", -1);
    FILE *file = fopen("result.txt", "w");

    fprintf(file, "%d\n", test);

    fclose(file);
    return 0;
}