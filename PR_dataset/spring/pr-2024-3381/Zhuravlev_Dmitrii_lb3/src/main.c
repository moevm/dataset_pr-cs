#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define WORK_DIR "./root"
#define MAX_LINE 1024
#define MAX_FILES 4096
#define DT_REG 8
#define DT_DIR 4


char* get_file_content(const char *file_path) {
    FILE *file = fopen(file_path, "r"); // открытие файла на чтение
    if (!file) { // не удалось открыть файл
        printf("Failed to open %s file\n", file_path);
        exit(1);
    }

    char *data = malloc(sizeof(char) * MAX_LINE); 
    fgets(data, MAX_LINE, file); // чтение строки из файла

    fclose(file); // закрытие файла
    return data;
}


int qsort_compare(const void *a, const void *b) {
    const char *str_a = *(const char **)a;
    const char *str_b = *(const char **)b;
    int x, y;
    sscanf(str_a, "%d", &x);
    sscanf(str_b, "%d", &y);
    if (x < y) {
        return -1;
    } else if (x > y) {
        return 1;
    } else {
        return 0;
    }
}

void list_dir(const char *dir_name, char **file_array, size_t* file_array_len) {
    DIR *dir = opendir(dir_name); // открытие директории
    int file_path_len;
    char *file_path;
    if (dir) {
        struct dirent *de = readdir(dir); // чтение элемента директории

        while (de) {
            file_path_len = strlen(dir_name) + strlen(de->d_name) + 2; // вычисление длины пути к файлу
            file_path = (char*) malloc(file_path_len * sizeof(char)); // выделение памяти под путь к файлу
            snprintf(file_path, file_path_len, "%s/%s", dir_name, de->d_name); // формирование пути к файлу

            if (de->d_type == DT_REG) {
                // элемент директории – файл
                file_array[*file_array_len] = get_file_content(file_path); // добавление содержимого файла в массив
                *file_array_len += 1;
            }
            else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0) {
                // элемент директории – директория
                list_dir(file_path, file_array, file_array_len); // рекурсивный вызов
                free(file_path);
            }
            de = readdir(dir); // чтение следующего элемента директории
        }
        closedir(dir); // закрытие директории
    }
    else {
        printf("Failed to open %s directory\n", dir_name);
    }
}

int main() {
    char** file_array = malloc(MAX_FILES * sizeof(char*));
    size_t* file_array_len = malloc(sizeof(size_t));
    list_dir(WORK_DIR, file_array, file_array_len);

    qsort(file_array, *file_array_len, sizeof(char*), qsort_compare);

    FILE *result = fopen("result.txt", "w");
    for (size_t i = 0; i < (*file_array_len); i++) {
        fprintf(result, "%s\n", file_array[i]);
        free(file_array[i]);
    }
    fclose(result);
    free(file_array);
}