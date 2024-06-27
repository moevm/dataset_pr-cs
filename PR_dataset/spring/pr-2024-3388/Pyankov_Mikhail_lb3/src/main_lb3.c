#include<stdio.h>
#include<dirent.h>
#include<stdlib.h>
#include<sys/types.h>
#include<string.h>
#define TYPE "txt"
#define SIZE 500
#define SIZE_OF_DATA 5000
#define BASE 10
#define MIN_FILE_NAME_LENGTH 5
#define MAIN_PATH "./"
#define UPPER "."
#define DOUBLE_UPPER ".."
#define FILE_WRITE_FLAG "w+"
#define FILE_READ_FLAG "r"
#define FILE_TO_WRITE "result.txt"

void write__data_in_file(char** data, int data_length)
{
    FILE* file_pnt = fopen(FILE_TO_WRITE, FILE_WRITE_FLAG);
    for(int i = 0; i < data_length; i++)
    {
        strcat(data[i], "\n");
        fputs(data[i], file_pnt);
    }
    fclose(file_pnt);
}

long int first_number_string(char* string)
{
    int end_ind;
    for(int i = 0; i < strlen(string); i++)
    {
        if(string[i] == ' ')
        {
            end_ind = i+1;
        }
    }
    return atol(string);
}

int cmp(const void* first_string, const void* second_string)
{
    if(first_number_string(*(char**)first_string) > first_number_string(*(char**)second_string))
        return 1;
    if(first_number_string(*(char**)first_string) == first_number_string(*(char**)second_string))
        return 0;
    if(first_number_string(*(char**)first_string) < first_number_string(*(char**)second_string))
        return -1;
}

char* get_file_string(char* path)
{
    char* string = malloc(sizeof(char)*SIZE);
    FILE* file_pnt = fopen(path, FILE_READ_FLAG);
    fgets(string, SIZE, file_pnt);
    fclose(file_pnt);
    return string;
}

int check_txt_file(char* file_name)
{
    int length = strlen(file_name);
    if(length >= MIN_FILE_NAME_LENGTH)
    {
        for(int i = 0; i < strlen(TYPE); i++)
        {
            if(TYPE[i] != file_name[length + i - strlen(TYPE)])
                return 0;
        }
        return 1;
    }
    return 0;
}

void find_txt_files(char* dirPath, char* file_name, char** data, int* data_length)
{
    DIR* dir = opendir(dirPath);
    if(dir)
    {
        struct dirent* de;
        char* newPath = malloc(sizeof(char)*SIZE);
        de = readdir(dir);
        while(de != NULL)
        {
            if(strcmp(de->d_name, UPPER) && strcmp(de->d_name, DOUBLE_UPPER))
            {
                strcpy(newPath, dirPath);
                strcat(newPath, "/");
                strcat(newPath, de->d_name);
                find_txt_files(newPath, de->d_name, data, data_length);
            }
            de = readdir(dir);
        }
    }
    if(!dir)
    {
        if(check_txt_file(file_name))
        {
            char* string = get_file_string(dirPath);
            data[*data_length] = string;
            *data_length+=1;
        }
        return;
    }
    closedir(dir);
}

int main()
{
    char* str = MAIN_PATH;
    char** data = malloc(SIZE_OF_DATA*sizeof(char*));
    int data_length = 0;
    find_txt_files(str, " ", data, &data_length);
    qsort(data, data_length, sizeof(char*), cmp);
    write__data_in_file(data, data_length);
}