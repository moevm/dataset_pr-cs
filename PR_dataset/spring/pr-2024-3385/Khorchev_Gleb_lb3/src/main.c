#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>

#define MAX_PATHH 256
#define MAX_FILE_NAME 128
#define MAX_NUMBER_LENGHT_IN_FILE 100
#define BLOCK 5


int cmp(const void* a, const void* b)
{
    const char* s = (const char*)a;
    const char* f = (const char*)b;

    char arr1[MAX_NUMBER_LENGHT_IN_FILE];
    char arr2[MAX_NUMBER_LENGHT_IN_FILE];

    for(size_t i=0; i < strlen(s); i++)
    {
        if ( !isdigit(s[i]) && (s[i] != '-'))
        {
            arr1[i] = '\0';
            break;
        }
        arr1[i] = s[i];
    }
    for(size_t j=0; j < strlen(f); j++)
    {
        if ( !isdigit(f[j]) && (f[j]) != '-')
        {
            arr2[j] = '\0';
            break;
        }
        arr2[j] = (f[j]);
    }
    int n1, n2;
    n1 = atoi(arr1);
    n2 = atoi(arr2);

    if ( n1 >= n2) return 1;
    else return 0;
}

void bubble_sort(char** arr, int size_of_arr){
    for(size_t i=0; i<size_of_arr-1;i++){
        for(size_t j=0; j<size_of_arr-1-i; j++){
            if( cmp(arr[j], arr[j+1])){
                char* tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
       }
   }

}

int file_validator(char* file_name)
{
    size_t len = strlen(file_name);
    if ( len >= 5)
    {
        if ( file_name[len-1] == 't' &&  file_name[len-2] == 'x' && file_name[len-3] == 't' && file_name[len-4] == '.' ) return 1;
    }
    return 0;
}

int dir_validator(char* dir_name)
{
    if ( strncmp(dir_name, ".", 1) && strncmp(dir_name, "..", 2) )
    return 1;
    else return 0;
}


char* read_file(char* file_path)
{
    FILE* file = fopen(file_path, "r");
    if (!file )
    {
        fprintf(stderr, "File didnt open sucsessfully");
        fclose(file);
        exit(0);
    }

    char* string = (char*)malloc(sizeof(char)*BLOCK);
    size_t len = 0, Capacity = BLOCK;
    char c = fgetc(file);
    while(1)
    {
        if ( c == EOF ) break;
        string[len++] = c;
        c = fgetc(file);

        if ( len == Capacity - 1)
        {
            Capacity += BLOCK;
            string = (char*)realloc(string, Capacity*sizeof(char));
            if ( !string)
            {
                fprintf(stderr, "Realloc error");
                free(string);
                exit(0);
            }
        }
    }
    string[len] = '\0';
    fclose(file);
    return string;
}

void dir_lookup(char* root, char*** arr, size_t* Capasity, size_t* len)
{
    char tmp_dir[MAX_PATHH];
    strncpy(tmp_dir, root, MAX_FILE_NAME);

    DIR* root_dir = opendir(tmp_dir);
    if ( !root_dir )
    {
        fprintf(stderr, "Directory didnt open sucsessfully");
        return;
    }
    struct dirent* dir = readdir(root_dir);

    while(dir)
    {
        if ( dir->d_type == DT_REG && file_validator(dir->d_name))
        {
            if (strlen(dir->d_name) > MAX_FILE_NAME) {
                perror("Слишком длинное имя файла");
                exit(0);
            }

            strncat(tmp_dir, "/", strlen(tmp_dir)+1);
            strncat(tmp_dir, dir->d_name, strlen(dir->d_name));

            (*arr)[(*len)++] = read_file(tmp_dir);
            if ( (*len) == (*Capasity)-1)
            {
                (*Capasity) += BLOCK;
                (*arr) = (char**)realloc((*arr), (*Capasity)*sizeof(char*));
                if ( !(*arr) )
                {
                    fprintf(stderr, "Realloc error");
                    for (size_t i=0; i < (*len); i++) free((*arr)[i]);
                    free((*arr));
                    exit(0);
                }
            }


            tmp_dir[strlen(tmp_dir) - 1 -strlen(dir->d_name)] = '\0';

        }
         else if ( dir->d_type == DT_DIR && dir_validator(dir->d_name) )
        {
              if (strlen(dir->d_name) > MAX_FILE_NAME) {
                perror("Слишком длинное имя файла");
                exit(0);
            }
            strncat(tmp_dir, "/", strlen(tmp_dir)+1);
            strncat(tmp_dir, dir->d_name, strlen(dir->d_name));
            dir_lookup(tmp_dir, arr, Capasity, len);
            tmp_dir[strlen(tmp_dir) - 1 -strlen(dir->d_name)] = '\0';
        }

        dir = readdir(root_dir);
    }
    closedir(root_dir);
}


int main(){
    char file_path[MAX_PATHH];
    if(!getcwd(file_path, sizeof(file_path))){
        printf("Error getting the path");
        return 1;
    }
    char** arr = (char**)malloc(sizeof(char*)*BLOCK);
    size_t Capacity = BLOCK, len = 0;
    dir_lookup(file_path, &arr, &Capacity, &len);
    bubble_sort(arr, len);
    char file_name[] = "/result.txt";
    strcat(file_path, file_name);
    FILE* result = fopen(file_path, "w+");
    for(size_t i =0; i < len; i++)
    {
        if ( i != 0) fputs("\n", result);
        fprintf(result, "%s", arr[i]);
        free(arr[i]);
    }
    free(arr);
    fclose(result);
    return 0;
}
