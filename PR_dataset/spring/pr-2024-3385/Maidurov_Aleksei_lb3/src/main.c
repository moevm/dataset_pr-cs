#define _DEFAULT_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char *pathcat(const char *path, const char *new_dir)
{
    unsigned res_path_len = strlen(path) + strlen(new_dir) + 2;
    char *res_path = malloc(sizeof(char) * res_path_len);
    sprintf(res_path, "%s/%s", path, new_dir);
    return res_path;
}

int calculate(const char *dir_name, const char *mod)
{
    DIR *dir = opendir(dir_name);
    if (!dir)
    {
        printf("Failed to open %s\n", dir_name);
        return 0;
    }

    int k, total, flag = strcmp(mod, "add");
    total = (flag ? 1 : 0);
    FILE *file;

    struct dirent *de = readdir(dir);
    while (de)
    {
        char *new_path = pathcat(dir_name, de->d_name);
        if (de->d_type == DT_REG)
        {
            file = fopen(new_path, "r");
            if (!file)
            {
                printf("Failed to open %s\n", new_path);
                return 0;
            }
            while ((fscanf(file, "%d", &k)) != EOF)
                if (flag)
                    total *= k;
                else
                    total += k;
            fclose(file);
        }
        else if (de->d_type == DT_DIR && !strchr(de->d_name, '.'))
        {
            if (flag)
                total *= calculate(new_path, de->d_name);
            else
                total += calculate(new_path, de->d_name);
        }
        free(new_path);
        de = readdir(dir);
    }
    closedir(dir);
    return total;
}

int main()
{
    DIR *dir = opendir("./tmp");
    if (!dir)
    {
        puts("Failed to open tmp");
        return 0;
    }

    FILE *file = fopen("result.txt", "w");
    if (!file)
    {
        puts("Failed to open result.txt");
        return 0;
    }

    struct dirent *de = readdir(dir);
    while (de)
    {
        if (!strcmp(de->d_name, "add") || !strcmp(de->d_name, "mul"))
        {
            char *path = pathcat("./tmp", de->d_name);
            fprintf(file, "%d", calculate(path, de->d_name));
            free(path);
        }
        de = readdir(dir);
    }

    fclose(file);
    closedir(dir);
    return 0;
}
