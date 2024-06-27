#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

#define START_DIR "./tmp"
#define NAME_RESULT_FILE "result.txt"
#define FILE_NAME_TEMPLATE " .txt"
#define END_LINE "\n"
#define MAX_STR_LENGTH 100
#define MAX_FILE_NAME_LENGTH 6
#define CURRENT_DIR "."
#define PARENT_DIR ".."

char *path_cat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = (char*) malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);
    return res_path;
}

int is_not_curr_or_parent_dir(const char *dir_name)
{
    if(strcmp(dir_name, CURRENT_DIR) && strcmp(dir_name, PARENT_DIR)) return 1;
    return 0;
}

void search_full_path_file(const char *dir_name, char* name_required_file, FILE *result_file)
{
    DIR *dir = opendir(dir_name);
    struct dirent *de = readdir(dir);
    while (de)
    {
        if(de->d_type == DT_REG && !strcmp(de->d_name, name_required_file))
        {
            fputs(path_cat(dir_name, de->d_name), result_file);
            fputs(END_LINE, result_file);
        }
        else if (de->d_type == DT_DIR && is_not_curr_or_parent_dir(de->d_name))
        {
            char *new_dir = path_cat(dir_name, de->d_name);
            search_full_path_file(new_dir, name_required_file, result_file);
            free(new_dir);
        }
        de = readdir(dir);
    }
    closedir(dir);
}

int main()
{
    char* name_required_file = strcpy(name_required_file, FILE_NAME_TEMPLATE);
    FILE *result_file = fopen(NAME_RESULT_FILE, "w");
    char str_containing_names_of_files[MAX_STR_LENGTH];
    fgets(str_containing_names_of_files, MAX_STR_LENGTH, stdin);

    for(int i = 0; i < strlen(str_containing_names_of_files); i++)
    {
        name_required_file[0] = str_containing_names_of_files[i];
        search_full_path_file(START_DIR, name_required_file, result_file);
    }
    free(name_required_file);
    fclose(result_file);
    return 0;
}
