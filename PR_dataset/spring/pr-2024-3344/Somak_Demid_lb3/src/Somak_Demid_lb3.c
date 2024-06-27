#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

int minotaur_flag = 0;
int count = 0;

char *catPaths(const char *first_path,const char *second_path){
  char* res_path = malloc(sizeof(char) * (strlen(first_path)+ strlen(second_path)+2));
  sprintf(res_path, "%s/%s", first_path, second_path);
  return res_path;
}


char *findFileByName(const char *root, const char *fileName)
{
    DIR *root_dir = opendir(root);
    if (root_dir == NULL)
        printf("Failed to open directory: %s \n", root);
    struct dirent* dir = readdir(root_dir);

    char *path = NULL;
    while (dir)
    {
        if (dir->d_type == DT_REG && strcmp(dir->d_name, fileName) == 0)
        {
            path = catPaths(root,fileName);
        }
        else if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && dir->d_type == DT_DIR)
        {

            char *new_root = catPaths(root,dir->d_name);
            path = findFileByName(new_root, fileName);
            free(new_root);
        }
        if (path)
            break;
        dir = readdir(root_dir);
    }
    closedir(root_dir);
    return path;
}


void findPath(char *fileName, char **massOfPaths)
{
    char* file_Path = findFileByName(".",fileName);

    FILE* file = fopen(file_Path, "r");
    if (file == NULL)
        return;

    char file_string[256];
    while (fgets(file_string, 256, file) != NULL && minotaur_flag != 1)
    {
        if (strstr(file_string, "Deadlock") )
        {
            return;
        }
        else if (strstr(file_string, "Minotaur"))
        {
            minotaur_flag = 1;
            massOfPaths[count] = malloc((strlen(file_Path)+1) * sizeof(char));
            strcpy(massOfPaths[count++], file_Path);
            massOfPaths  = realloc(massOfPaths, (count+1) * sizeof(char*));
        }
        else if (strncmp(file_string, "@include", 8) == 0)
        {
            if(file_string[strlen(file_string) - 1] == '\n')
                file_string[strlen(file_string)-1] = '\0';

            memmove(&file_string[0], &file_string[9], sizeof(char) * (strlen(file_Path)+1));

            findPath(file_string, massOfPaths);

            if (minotaur_flag)
            {
            massOfPaths[count] = malloc((strlen(file_Path)+1) * sizeof(char));
            strcpy(massOfPaths[count++], file_Path);
            massOfPaths  = realloc(massOfPaths, (count+1) * sizeof(char*));
            }
        }
    }
    fclose(file);
    return;
}


int main(void)
{
    char** paths = (char**)malloc(sizeof(char*));

    findPath("file.txt", paths);

    FILE *file_result = fopen("result.txt", "w");
    if (file_result == NULL)
    {
        printf("Failed to open file.txt");
        return 0;
    }

    for (int i = count-1; i >= 0; i--)
    {
        fprintf(file_result, "%s\n", paths[i]);
    }
    fclose(file_result);
    return 0;
}
