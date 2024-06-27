#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SIZE 256
#define MAXFILES 3000

int flag = 0;
int count = 0;

char *inDirect(const char *directName, const char *fileName)
{
    DIR *dir;
    struct dirent *entry;
    char *full_path_file = NULL;
    dir = opendir(directName);
    if (dir)
    {
        entry = readdir(dir);
        while (entry)
        {
            if (entry->d_type == DT_REG && !strcmp(entry->d_name, fileName))
            {
                int resPathLen = strlen(directName) + strlen(fileName) + 2;
                full_path_file = malloc(resPathLen * sizeof(char));
                sprintf(full_path_file, "%s/%s", directName, fileName);
                break;
            }
            else if (entry->d_type == DT_DIR && strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
            {
                char *newDirect = malloc((strlen(directName) + strlen(entry->d_name) + 2) * sizeof(char));
                sprintf(newDirect, "%s/%s", directName, entry->d_name);
                full_path_file = inDirect(newDirect, fileName);
                free(newDirect);
                if (full_path_file)
                {
                    break;
                }
            }
            entry = readdir(dir);
        }
        closedir(dir);
    }
    return full_path_file;
}

void searchWord(char *filename, char **result)
{
    char *file_path = inDirect(".", filename);

    FILE *file = fopen(file_path, "r");
    if (!file)
    {
        return;
    }

    char data[SIZE];
    while (fgets(data, SIZE, file) != NULL && flag == 0)
    {
        if (strstr(data, "Deadlock"))
        {
            return;
        }
        else if (strstr(data, "Minotaur"))
        {
            flag = 1;
            result[count] = malloc(SIZE * sizeof(char));
            strcpy(result[count++], file_path);
        }
        else if (strncmp(data, "@include ", 9) == 0 && data[strlen(data) - 1] == '\n')
        {
            data[strlen(data) - 1] = '\0';
            memmove(&data[0], &data[9], sizeof(char) * SIZE);
            searchWord(data, result);
            if (flag)
            {
                result[count] = malloc(SIZE * sizeof(char));
                strcpy(result[count++], file_path);
            }
        }
    }

    fclose(file);
    return;
}

int main()
{
    char **result = (char **)malloc(sizeof(char *) * MAXFILES);

    searchWord("file.txt", result);

    FILE *result_file = fopen("result.txt", "w");
    if (result_file == NULL)
    {
        return 1;
    }

    for (int i = count - 1; i >= 0; --i)
    {
        fprintf(result_file, "%s\n", result[i]);
    }

    fclose(result_file);

    for (int i = 0; i < count; i++)
    {
        free(result[i]);
    }

    free(result);

    return 0;
}