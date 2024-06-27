#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

#define FILEPATH_BUFFER 1024
#define STRING_BUFFER 100
#define SEARCH_DIRECTORY "./tmp"
#define ANSWER_FILE "./result.txt"


void match(const char *dirPath, FILE *result, char str);

int main()
{
    char string[STRING_BUFFER];
    scanf("%s", string);
    const char *directory = SEARCH_DIRECTORY;
    int length = strlen(string);

    char path[] = ANSWER_FILE;
    FILE *result = fopen(path, "w");
    result = freopen(path, "a", result);

    for(int i =  0; i < length; i++)
    {
        match(directory, result, string[i]);
    }
    fclose(result);
    
}

void match(const char *dirPath, FILE* result, char str)
{   
    if(result)
    {
        DIR *dir = opendir(dirPath);

        if(dir)
        {
            struct  dirent *file_in_dir = readdir(dir);

            while(file_in_dir)
            {
                struct stat statbuf;
                char filepath[FILEPATH_BUFFER]="";                
                strcat(filepath, dirPath);
                strcat(filepath, "/");
                strcat(filepath, file_in_dir->d_name);

                if(file_in_dir->d_name[0]!='.')
                {
                    if(stat(filepath, &statbuf)==0)
                    {
                        if(S_ISDIR(statbuf.st_mode))
                        {
                            match(filepath, result, str);   
                        }
                    }
                }         

                if(file_in_dir->d_name[0] == str && file_in_dir->d_name[1] == '.')
                {
                    fprintf(result,"%s/%s\n", dirPath, file_in_dir->d_name);
                } 
                file_in_dir = readdir(dir);
            }
        }
        closedir(dir);
    }
}
