#include <stdio.h>
#include <string.h>
#include <dirent.h>

int add(FILE *file)
{
    int res = 0;
    int n;
    while (fscanf(file, "%d", &n) == 1) res += n;
    return  res;
}

int mul(FILE *file)
{
    int res = 1;
    int n;
    while (fscanf(file, "%d", &n) == 1) res *= n;
    return res;
}

int addValues(int *values, int len)
{
    int res = 0;
    for (int i = 0; i < len; i++) res += values[i];
    return res;
}

int mulValues(int *values, int len)
{
    int res = 1;
    for (int i = 0; i < len; i++) res *= values[i];
    return res;
}

int calc(const char *root)
{
    DIR *dir = opendir(root);
    FILE *file;
    struct dirent *entry;
    char filePath[1000];
    int values[100];
    int len = 0;

    if (dir)
    {
        while ((entry = readdir(dir)) != NULL)
        {
            sprintf(filePath, "%s/%s", root, entry->d_name); 
            if (entry->d_type == DT_DIR)
            {
                if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) 
                    values[len++] = calc(filePath);
            }
            else
            {
                file = fopen(filePath, "r");

                if (strcmp(root + strlen(root) - 3, "add") == 0)
                    values[len++] = add(file);
                else 
                    values[len++] = mul(file);

                fclose(file);
            }
        }
    }

    int res = values[0];

    if (strcmp(root + strlen(root) - 3, "add") == 0) 
        res = addValues(values, len);
    else
        res = mulValues(values, len);

    return res;
}

int main()
{
    char *dirPath = "./tmp";
    FILE *result = fopen("result.txt", "w+");
    int n = calc(dirPath);
    fprintf(result, "%d", n);
    fclose(result);
    return 0;
}