#include <stdio.h>
#include <dirent.h>
#include <string.h>

int recfunc(char *path, char *prev);

int main() {
    char *arr = "./tmp";
    FILE *res = fopen("./result.txt", "w");
    if (res) {
        fprintf(res, "%d", recfunc(arr, "firstiter"));
        fclose(res);
    } else printf("Opening file error\n");
    return 0;
}

int recfunc(char *path, char *prev) {
    int tmp, result;
    DIR *dr = opendir(path);
    if (!strncmp(prev, "mul", 3)) {
        result = 1;
        struct dirent *directory;
        for (; (directory = readdir(dr)) != NULL;) {
            char new_path[1024] = "";
            strcat(strcat(strcat(new_path, path), "/"), directory->d_name);
            if (strncmp(directory->d_name, "add", 3) == 0 || strncmp(directory->d_name, "mul", 3) == 0)
                result *= recfunc(new_path, directory->d_name);
            else if (strstr(directory->d_name, ".txt")) {
                FILE *f = fopen(new_path, "r");
                int nums[20], len = 0, n = fscanf(f, "%d", &nums[len++]);
                while (n > 0) n = fscanf(f, "%d", &nums[len++]);
                --len;
                for (int i = 0; i < len; i++) result *= nums[i];
            }
        }
    } else if (!strncmp(prev, "add", 3)) {
        result = 0;
        struct dirent *directory;
        for (; (directory = readdir(dr)) != NULL;) {
            char new_path[1024] = "";
            strcat(strcat(strcat(new_path, path), "/"), directory->d_name);
            if (strncmp(directory->d_name, "add", 3) == 0 || strncmp(directory->d_name, "mul", 3) == 0)
                result += recfunc(new_path, directory->d_name);
            else if (strstr(directory->d_name, ".txt")) {
                FILE *f = fopen(new_path, "r");
                int nums[20], len = 0, n = fscanf(f, "%d", &nums[len++]);
                while (n > 0) n = fscanf(f, "%d", &nums[len++]);
                --len;
                for (int i = 0; i < len; i++) result += nums[i];
            }
        }
    } else {
        if (dr) {
            struct dirent *directory;
            for (; (directory = readdir(dr)) != NULL;) {
                char new_path[1024] = "";
                strcat(strcat(strcat(new_path, path), "/"), directory->d_name);
                if (strncmp(directory->d_name, "add", 3) == 0 || strncmp(directory->d_name, "mul", 3) == 0)
                    result += recfunc(new_path, directory->d_name);
            }
        }
    }
    closedir(dr);
    return result;
}