#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_LEN_PATH 1024
#define MAX_FILES 1024
#define DT_DIR 4

char* find_file(const char* root_name, const char* file_name, char* curr_path)
{
    DIR* dir;
    struct dirent* entry;
    char path[MAX_LEN_PATH];
    if (!(dir = opendir(root_name)))
    {
        return NULL;
    }
    while ((entry = readdir(dir)) != NULL)
    {
        snprintf(path, MAX_LEN_PATH, "%s/%s", root_name, entry->d_name);
        if (entry->d_type == DT_DIR)
        {
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
            {
                continue;
            }
            find_file(path, file_name, curr_path);
        }
        if (!strcmp(entry->d_name, file_name))
        {
            closedir(dir);
            return strcpy(curr_path, path);
        }
    }
    closedir(dir);
    return NULL;
}

int find_minotaur_file(const char* root_name, const char* file_name, char** my_list, int index)
{
    FILE* file;
    char* curr_path = calloc(MAX_LEN_PATH, sizeof(char));
    find_file(root_name, file_name, curr_path);
    if (!curr_path)
    {
        return 1;
    }
    my_list[index++] = curr_path;
    file = fopen(curr_path, "r");
    if (!file)
    {
        return 1;
    }
    char line[MAX_LEN_PATH];
    int res = 1;
    while (fgets(line, MAX_LEN_PATH, file))
    {
        if (!strcmp(line, "Deadlock"))
        {
            my_list[index] = NULL;
            res = 1;
            break;
        } else if (!strcmp(line, "Minotaur"))
        {
            res = 0;
            break;
        } else if (!strncmp(line, "@include ", 9) && line[strlen(line) - 1] == '\n')
        {
            int i = 9;
            for (i; line[i] != '\n'; i++);
            line[i] = '\0';
            if (find_minotaur_file(root_name, &line[9], my_list, index) == 0)
            {
                res = 0;
                break;
            }
        } else
        {
            res = 1;
            break;
        }
    }
    fclose(file);
    return res;
}

int main()
{
    char* my_list[MAX_FILES];
    FILE* file = fopen("./result.txt", "w");
    int index = 0;
    if(find_minotaur_file("./labyrinth", "file.txt", my_list, index) == 0)
    {
        for(int i = 0; my_list[i]; i++)
        {
            fputs(my_list[i], file);
            fputs("\n", file);
        }
    }
    fclose(file);
    return 0;
}