#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

//функция для создания путей
char *pathcat(const char *path1, const char *path2)
{
    int res_path_len = strlen(path1) + strlen(path2) + 2; //определение длины новой строки с учетом символов / и символа конца строки
    char *res_path = malloc(res_path_len * sizeof(char)); //выделение памяти под новую строку
    sprintf(res_path, "%s/%s", path1, path2);             //форматный вывод данных в строку return res_path;
    return res_path;
}

//функция поиска файла в директории
char *find_file(const char *dir_name, const char *filename)
{
    char *full_path_file = NULL; //изначально файл не найден
    DIR *dir = opendir(dir_name); //открытие директории
    if (dir)
    {
        struct dirent *de = readdir(dir);
        while (de)
        {
            if (de->d_type == DT_REG && !strcmp(de->d_name, filename))
            {
                //файл найден
                full_path_file = pathcat(dir_name, filename);
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0)
            {
                char *new_dir = pathcat(dir_name, de->d_name);
                //запись результата поиска во вложенной директории
                full_path_file = find_file(new_dir, filename);
                free(new_dir);
            }
            if (full_path_file) //файл найден, завершение поиска
                break;
            de = readdir(dir);
        }
        closedir(dir); //закрытие директории
    }
    else
        printf("Failed to open %s directory\n", dir_name);
    return full_path_file;
}

//функция работы с файлом
int working_with_a_file(const char *file_path, char **result)
{
    FILE *file = fopen(file_path, "r"); //открытие файла на чтение
    if (!file)
    {
        printf("Failed to open %s file\n", file_path);
        exit(0);
    }

    char information[500];
    char *read_result = fgets(information, 500, file);
    while (read_result != NULL)
    {
        if (strcmp(information, "Minotaur") == 0) //поиск слова Minotaur
        {
            fclose(file); //закрытие файла
            return 1; //выход из функции
        }
        else if (strcmp(information, "Deadlock") == 0) //поиск тупика
        {
            break; //выход из цикла
        }
        else
        {
            //считывание строки, которая начинается с @include
            sscanf(information, "@include %s", read_result); //считывание названия другого файла из ссылки
            char *file_from_the_link = find_file("labyrinth", information); //поиск файла
            if (working_with_a_file(file_from_the_link, result))
            {
                strcat(*result, "./"); //запись корня текущего каталога
                strcat(*result, file_from_the_link); //запись полного пути к файлу
                strcat(*result, "\n"); //запись символа переноса строки
                free(file_from_the_link); //очистка памяти
                fclose(file); //закрытие файла
                return 1; //выход из функции
            }
            free(file_from_the_link); //очистка памяти
        }

        read_result = fgets(information, 500, file);
    }
    fclose(file);
    return 0;
}


int main()
{
    char *result = malloc(sizeof(char) * 3000); //выделение памяти под результат
    char *file = find_file("labyrinth", "file.txt"); //поиск файла в директории
    working_with_a_file(file, &result); //проверка содержимого файла
    strcat(result, "./"); //запись корня текущего каталога
    strcat(result, file); //запись файла
    strcat(result, "\n"); //запись символа переноса строки

    int counter = 0; //счётчик
    //объединение данных для последующей записи в файл
    char **result_for_writing_to_a_file = malloc(sizeof(char *));
    char *token = strtok(result, "\n");
    while (token != NULL)
    {
        result_for_writing_to_a_file[counter++] = token;
        result_for_writing_to_a_file = realloc(result_for_writing_to_a_file, sizeof(char *) * (counter + 1));
        token = strtok(NULL, "\n");
    }

    //запись результата в файл
    FILE *res_file = fopen("result.txt", "w");
    for (int i = counter - 1; i > -1; i--)
    {
        if (i == 0)
        {
            fprintf(res_file, "%s", result_for_writing_to_a_file[i]);
        }
        else
        {
            fprintf(res_file, "%s\n", result_for_writing_to_a_file[i]);
        }
    }

    fclose(res_file); //закрытие файла с результатом
    free(result); //очистка памяти
    free(result_for_writing_to_a_file); //очистка памяти
    free(file); //очистка памяти
    return 0;
}