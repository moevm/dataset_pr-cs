#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>

typedef struct Text
{
    char text[200];
    int number;
} Text;

char *pathcat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);
    return res_path;
}

Text *readfile(const char *file_name)
{
    char str[200];
    FILE *new_file = fopen(file_name, "r");
    Text *file = NULL;
    if (new_file)
    {
        file = (Text *)malloc(sizeof(Text));
        fscanf(new_file, "%d", &(file->number));
        fgets(str, 200, new_file);
        strncpy(file->text, str, 200);
        fclose(new_file);
    }
    return file;
}

Text **list_dir(const char *dir_name, int *size, Text **strings)
{
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (de->d_type == DT_REG && strstr(de->d_name, ".txt") != NULL && strstr(de->d_name, "result.txt") == NULL)
            {
                char *file_name = pathcat(dir_name, de->d_name);
                Text *s = readfile(file_name);
                if (s)
                {
                    strings[(*size)++] = s;
                }
                free(file_name);
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                char *new_dir = pathcat(dir_name, de->d_name);
                list_dir(new_dir, size, strings);
                free(new_dir);
            }
            de = readdir(dir);
        }
        closedir(dir);
    }
    else
    {
        printf("error open dir %s\n", dir_name);
    }
}

void write(const char *name_file, int size, Text **strings)
{
    FILE *f = fopen(name_file, "w");
    if (f)
    {
        for (int i = 0; i < size; i++)
        {
            fprintf(f, "%d%s\n", strings[i]->number, strings[i]->text);
            free(strings[i]);
        }
        free(strings);
        fclose(f);
    }
    else
    {
        printf("error open result.txt");
    }
}

int compar(const void *a, const void *b)
{
    const Text *Text_a = *(Text **)a;
    const Text *Text_b = *(Text **)b;
    if (Text_a->number < Text_b->number)
        return -1;
    if (Text_a->number > Text_b->number)
        return 1;
    return Text_a->number == Text_b->number;
}

int main()
{
    int size;
    size = 0;
    Text **strings = (Text **)malloc(200 * 200 * sizeof(Text));
    list_dir(".", &size, strings);
    qsort(strings, size, sizeof(Text *), compar);
    write("result.txt",size, strings);
    return 0;
}