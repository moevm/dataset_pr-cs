#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* find_file(const char* dir_name, const char* filename)
{
    DIR* dir = opendir(dir_name);
    struct dirent* de;
    char *full_path_file = NULL, *new_dir;

    while ((de = readdir(dir))) {
        if (de->d_type == DT_REG && !strcmp(de->d_name, filename)) {
            full_path_file = malloc(strlen(dir_name) + strlen(filename) + 2);
            sprintf(full_path_file, "%s/%s", dir_name, filename);
        } else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") && strcmp(de->d_name, "..")) {
            new_dir = malloc(strlen(dir_name) + strlen(de->d_name) + 2);
            sprintf(new_dir, "%s/%s", dir_name, de->d_name);
            full_path_file = find_file(new_dir, filename);
            free(new_dir);
        }
        if (full_path_file)
            break;
    }
    closedir(dir);
    return full_path_file;
}

int check_file(const char* file_path, char** result)
{
    FILE* file = fopen(file_path, "r");
    char data[1024], *read_result, *file_name;

    while ((read_result = fgets(data, 1024, file)) != NULL) {
        if (!strcmp(data, "Minotaur")) {
            fclose(file);
            return 1;
        } else if (!strcmp(data, "Deadlock"))
            break;
        else {
            sscanf(data, "@include %s", read_result);
            file_name = find_file("labyrinth", data);
            if (check_file(file_name, result)) {
                strcat(*result, "./");
                strcat(*result, file_name);
                strcat(*result, "\n");
                free(file_name);
                fclose(file);
                return 1;
            }
            free(file_name);
        }
    }
    fclose(file);
    return 0;
}

int main()
{
    FILE* res_file;
    char *result, *file, **result_table, *res;
    int n = 0, i;

    result = malloc(sizeof(char) * 1000);
    file = find_file("labyrinth", "file.txt");
    check_file(file, &result);
    strcat(result, "./");
    strcat(result, file);
    strcat(result, "\n");
    result_table = malloc(sizeof(char*));
    res = strtok(result, "\n");
    while (res != NULL) {
        result_table[n++] = res;
        result_table = realloc(result_table, sizeof(char*) * (n + 1));
        res = strtok(NULL, "\n");
    }

    res_file = fopen("result.txt", "w");
    for (i = n - 1; i > 0; i--)
        fprintf(res_file, "%s\n", result_table[i]);
    fprintf(res_file, "%s", result_table[0]);
    fclose(res_file);

    free(result);
    free(result_table);
    free(file);
    return 0;
}