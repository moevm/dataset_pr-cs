#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>

#define SIZE_LINE 250
#define DEFAULT_DIR "labyrinth"
#define FINAL_WORD "Minotaur"
#define DEAD_WORD "Deadlock"

char *pathcat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2; // определение длины новой строки с учетом символов / и символа конца строки
    char *res_path = malloc(res_path_len * sizeof(char)); // выделение памяти под новую строку
    sprintf(res_path, "%s/%s", path1, path2);             // форматный вывод данных в строку return res_path;
    return res_path;
}

char *find_file(const char *dir_name, const char *filename)
{
    char *full_path_file = NULL; // изначально файл не найден
    DIR *dir = opendir(dir_name);
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (de->d_type == DT_REG && !strcmp(de->d_name, filename))
            {
                // файл найден
                full_path_file = pathcat(dir_name, filename);
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                char *new_dir = pathcat(dir_name, de->d_name);
                // запись результата поиска во вложенной директории
                full_path_file = find_file(new_dir, filename);
                free(new_dir);
            }
            if (full_path_file) // файл найден, завершение поиска
                break;
            de = readdir(dir);
        }
        closedir(dir);
    }
    else
        printf("Failed to open %s directory\n", dir_name);
    return full_path_file;
}

int check_file(const char *file_path, char **result)
{
    FILE *file = fopen(file_path, "r"); // открытие файла на чтение
    if (!file)
    {
        printf("Failed to open %s file\n", file_path);
        exit(0);
    }
    char data[SIZE_LINE];
    char *read_result;
    while ((read_result = fgets(data, SIZE_LINE, file)) != NULL)
    {
        if (strcmp(data, FINAL_WORD) == 0)
        {
            fclose(file);
            return 1;
        }
        else if (strcmp(data, DEAD_WORD) == 0)
        {
            break;
        }
        else
        {
            sscanf(data, "@include %s", read_result);
            char *file_name = find_file(DEFAULT_DIR, data);
            if (check_file(file_name, result))
            {
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
    char *result = malloc(sizeof(char) * 1000);
    char *file = find_file(DEFAULT_DIR, "file.txt");
    check_file(file, &result);
    strcat(result, "./");
    strcat(result, file);
    strcat(result, "\n");
    int n = 0;
    char **result_table = malloc(sizeof(char *));
    char *res = strtok(result, "\n");
    while (res != NULL)
    {
        result_table[n++] = res;
        result_table = realloc(result_table, sizeof(char *) * (n + 1));
        res = strtok(NULL, "\n");
    }
    FILE *res_file = fopen("result.txt", "w");

    for (int i = n - 1; i > -1; i--)
    {
        if (i == 0)
        {
            fprintf(res_file, "%s", result_table[i]);
        }
        else
        {
            fprintf(res_file, "%s\n", result_table[i]);
        }
    }
    fclose(res_file);
    free(result);
    free(result_table);
    free(file);
    return 0;
}