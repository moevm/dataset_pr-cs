#include <stdio.h>
#include <wchar.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define SIZE 256
#define MAXFILES 3000

int flag = 0;
int count = 0;

char *pathcat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2;

    char *res_path = malloc(res_path_len * sizeof(char));

    sprintf(res_path, "%s/%s", path1, path2);

    return res_path;
}

char *find_file(const char *dir_name, const char *filename)
{
    char *full_path_file = NULL;
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (de->d_type == DT_REG && !strcmp(de->d_name, filename))
            {
                full_path_file = pathcat(dir_name, filename);
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {

                char *new_dir = pathcat(dir_name, de->d_name);
                full_path_file = find_file(new_dir, filename);
                free(new_dir);
            }
            if (full_path_file)
                break;
            de = readdir(dir);
        }
        closedir(dir);
    }
    else
        printf("Failed to open %s directory\n", dir_name);
    return full_path_file;
}

void process(char* filename, char** result)
{
    char* file_path = find_file(".", filename);

    FILE* file = fopen(file_path, "r");
    if (file==NULL) return;

    char data[SIZE];
    while (fgets(data, SIZE, file) != NULL && flag==0){
        if (strstr(data, "Deadlock") ) return;
        
        else if (strncmp(data, "@include ", 9) == 0 && data[strlen(data) - 1] == '\n')
        {

            data[strlen(data)-1] = '\0';
            memmove(&data[0], &data[9], sizeof(char) * SIZE);
            process(data, result);
            if (flag)
            {                result[count] = malloc(SIZE * sizeof(char));
                strcpy(result[count++], file_path);            }
        }else if (strstr(data, "Minotaur"))        {
            flag = 1;            result[count] = malloc(SIZE * sizeof(char));
            strcpy(result[count++], file_path);        }
    }
    fclose(file);
    return;}
int main()
{    char** result = (char**)malloc(sizeof(char*) * MAXFILES);
    process("file.txt", result);
    FILE *fp = fopen("result.txt", "w");
    if (fp == NULL)
        return 1;
    int i;    for (i = count - 1; i >= 0; --i){
        fprintf(fp, "%s\n", result[i]);    }
    fclose(fp);
    for (int i = 0; i < count; i++){
        free(result[i]);        }
    free(result);
    return 0;}