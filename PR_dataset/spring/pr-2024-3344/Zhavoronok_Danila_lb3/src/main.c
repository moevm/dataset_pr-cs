#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

typedef struct dirent dirent;

int calc(FILE *file, char *dirname)
{
    if (!file)
        return -1;

    int mode = strcmp(dirname, "add") == 0;

    int result = mode ? 0 : 1;
    int temp = 0;
    while (fscanf(file, "%d ", &temp) == 1)
    {
        if (mode)
            result += temp;
        else
            result *= temp;
    }
    return result;
}

int iterate_over_dir(const char *dirname, char *prev_dir)
{
    DIR *dir;
    dirent *entry;

    dir = opendir(dirname);
    if (!dir)
        exit(-1);

    int is_add = strcmp(prev_dir, "add") == 0;
    int is_mul = strcmp(prev_dir, "mul") == 0;
    int result = is_mul;

    while ((entry = readdir(dir)) != NULL)
    {
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                continue;
            char *path = malloc(strlen(dirname) + strlen(entry->d_name) + 2);
            snprintf(path, strlen(dirname) + strlen(entry->d_name) + 2, "%s/%s", dirname, entry->d_name);
            int n = iterate_over_dir(path, entry->d_name);
            if (is_add)
                result += n;
            else if (is_mul)
                result *= n;
            else
            {
                return n;
            }
        }
        else
        {
            char *temp = malloc(strlen(dirname) + strlen(entry->d_name) + 2);
            snprintf(temp, strlen(dirname) + strlen(entry->d_name) + 2, "%s/%s", dirname, entry->d_name);
            FILE *file = fopen(temp, "r");
            int n = calc(file, prev_dir);
            fclose(file);
            if (is_add)
                result += n;
            else if (is_mul)
                result *= n;
        }
    }
    closedir(dir);
    return result;
}

int main(void)
{
    int result = iterate_over_dir("./tmp", ".");
    FILE *file = fopen("result.txt", "w");
    if (!file)
        return -1;

    fprintf(file, "%d", result);
    fclose(file);
    return 0;
}
