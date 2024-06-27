#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

char* FileCheck(char letter,char* path_to_file)
{
    DIR* dir = opendir(path_to_file);
    if(dir)
    {
        struct dirent* de = readdir(dir);
        while(de)
        {
            char* dirName = de -> d_name;
            char NewPath_to_file[strlen(path_to_file) + strlen(dirName) + 1];
            strcpy(NewPath_to_file, path_to_file);
            strcat(NewPath_to_file, "/");
            strcat(NewPath_to_file, dirName);
            
            if(de->d_type == DT_DIR)
            {
                if(strcmp(dirName, ".") && strcmp(dirName, ".."))
                {
                    if(FileCheck(letter, NewPath_to_file) != NULL)
                    {
                        return FileCheck(letter, NewPath_to_file);
                    }
                }
            }
            else
            {
                if(dirName[0]==letter && dirName[1]=='.' && dirName[2]=='t' && dirName[3]=='x' && dirName[4]=='t' && strlen(dirName) == 5)
                {
                    char* result = malloc( sizeof(char) * (strlen(path_to_file) + strlen(dirName) + 1) );
                    strcpy(result, NewPath_to_file);
                    return result;
                }
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}

int main()
{
    char* input=malloc(sizeof(char)*100);
    scanf("%s",input);
    int ln=strlen(input);
    FILE* result = fopen("result.txt", "w");
    char* path_to_file = "./tmp";
    for(int i=0;i<ln;i++)
    {
        char* path = FileCheck(input[i], path_to_file);
        fprintf(result,"\n%s",path);
        free(path);
    }
    fclose(result);
}