
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#include <stdlib.h>

void read_numfile(char *filepath, int mode, int *res)
{
    FILE *f = fopen(filepath, "r");
    if (f == NULL)
    {
        return;
    }
    char string[256];
    fgets(string, 256, f);
    char *number = strtok(string, " ");
    while (number != NULL)
    {
        if (mode == 1)
        {
            (*res) += atoi(number);
        }
        if (mode == -1)
        {
            (*res) = (*res) * atoi(number);
        }

        number = strtok(NULL, " ");
    }
    fclose(f);
}

char *file_allocpath(char *path, char *name)
{
    int res_len = strlen(path) + strlen(name) + 2;
    char *res = calloc(res_len, sizeof(char));
    sprintf(res, "%s/%s", path, name);
    return res;
}

int dir_lookup(char *root, int mode)
{
    int tmp;
    int res = 0;
    if (mode == 1)
    {
        res = 0;
    }
    if (mode == -1)
    {
        res = 1;
    }
    DIR *root_dir = opendir(root);
    struct dirent *de;
    while ((de = readdir(root_dir)) != NULL)
    {
        char *new_path = file_allocpath(root, de->d_name);
        if (strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0)
        {
            continue;
        } // когда открывается файл

            // когда открывается папка
        else if (de->d_type == 4)
        {

            // tmp = dir_lookup(:MODE = 1)
            if (strcmp(de->d_name, "add") == 0)
            {
                tmp = dir_lookup(new_path, 1);
            }
            else if (strcmp(de->d_name, "mul") == 0)
            {
                tmp = dir_lookup(new_path, -1);
            }

            if (mode == 1)
            {
                res = res + tmp;
            }
            else if (mode == -1)
            {
                res = res * tmp;
            }
            else if (mode == 0)
            {
                return tmp;
            }
        }
        else
        {


            read_numfile(new_path, mode, &res);
        }
    }
    closedir(root_dir);
    return res;
}

int main()
{
    char *dir = "./tmp";
    FILE *file = fopen("./result.txt", "w");
    fprintf(file, "%d\n", dir_lookup(dir, 0));
    fclose(file);
    printf("%d\n", dir_lookup(dir, 0));
    return 0;
}
