#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define SIZE 256
#define MAXFILES 3000

int flag = 0;
int count = 0;

char *listDir(char* startDir, const char *fileName)
{
    DIR *dir;
    struct dirent *de;
    char *full_path_file = NULL;
    dir = opendir(startDir);
    if(dir)
    {
        de = readdir(dir);
        while(de)
        {
            if (de->d_type == DT_REG && !strcmp(de->d_name, fileName))
            {
                int Len = strlen(startDir) + strlen(fileName) + 2;
                full_path_file = malloc(Len * sizeof(char));
                sprintf(full_path_file, "%s/%s", startDir, fileName);
                break;
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") && strcmp(de->d_name, ".."))
            {
                char *newDirect = malloc(sizeof(char) * (strlen(startDir) + strlen(de->d_name) + 2));
                sprintf(newDirect, "%s/%s", startDir, de->d_name);
                full_path_file = listDir(newDirect, fileName);
                free(newDirect);
                if (full_path_file)
                {
                    break;
                }
            }
            de = readdir(dir);
        }
        closedir(dir);
    }
    return full_path_file;
}

void searchWord(char* filename, char** result)
{
    char *file_path = listDir(".", filename);
    FILE *file = fopen(file_path, "r");
    if (!file)
        return;
    char data[SIZE];
    while(fgets(data, SIZE, file) != NULL && flag == 0)
    {
        if(strstr(data, "Deadlock"))
        {
            return;
        }
        else if(strstr(data, "Minotaur"))
        {
            flag = 1;
            result[count] = malloc(sizeof(char) * SIZE);
            strcpy(result[count++], file_path);
        }
        else if(strncmp(data, "@include ", 9) && data[strlen(data) - 1] == '\n')
        {
            data[strlen(data) - 1] = '\0';
            memmove(&data[0], &data[9], sizeof(char) * SIZE);
            searchWord(data, result);
            if(flag)
            {
                result[count] = malloc(SIZE * sizeof(char));
                strcpy(result[count++], file_path);
            }
        }
    }
    fclose(file);
}

int main()
{
    char** result = (char**)malloc(sizeof(char*) * MAXFILES);

    searchWord("file.txt", result);

    FILE *result_file = fopen("result.txt", "w");
    if(result_file == NULL)
        return 1;

    for (int i = count - 1; i >= 0; --i)
    {
        fprintf(result_file, "%s\n", result[i]);
    }

    fclose(result_file);

    for (int i = 0; i < count; ++i)
    {
        free(result[i]);
    }

    free(result);
    return 0;
}