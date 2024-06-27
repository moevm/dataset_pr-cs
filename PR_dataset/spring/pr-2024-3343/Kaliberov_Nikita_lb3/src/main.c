#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate_expression(const char* directory) {
    // Проверяем, является ли директория папкой "add" или "mul"
    if (strcmp(directory, "add") == 0 || strcmp(directory, "mul") == 0) {
        int result = (strcmp(directory, "add") == 0) ? 0 : 1;
        int file_count = 0;
        int subdirectory_count = 0;
        
        // Открываем текущую директорию
        DIR* dir = opendir(directory);
        if (dir == NULL) {
            printf("Ошибка при открытии директории: %s\n", directory);
            exit(1);
        }
        
        struct dirent* entry;
        
        // Обходим все файлы и поддиректории внутри текущей директории
        while ((entry = readdir(dir)) != NULL) {
            // Игнорируем "." и ".."
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
            
            // Формируем полный путь к текущему элементу
            char path[PATH_MAX];
            snprintf(path, PATH_MAX, "%s/%s", directory, entry->d_name);
            
            if (entry->d_type == DT_REG && strstr(entry->d_name, ".txt") != NULL) {
                // Если текущий элемент - текстовый файл, выполняем операцию
                FILE* file = fopen(path, "r");
                if (file == NULL) {
                    printf("Ошибка при открытии файла: %s\n", path);
                    exit(1);
                }
                
                int value;
                while (fscanf(file, "%d", &value) == 1) {
                    if (strcmp(directory, "add") == 0) {
                        result += value;
                    } else {
                        result *= value;
                    }
                }
                
                fclose(file);
                file_count++;
            } else if (entry->d_type == DT_DIR) {
                // Если текущий элемент - поддиректория, рекурсивно вычисляем значение выражения внутри нее
                int sub_result = calculate_expression(path);
                if (sub_result == -1) {
                    printf("Ошибка при вычислении выражения в папке: %s\n", path);
                    exit(1);
                }
                
                if (strcmp(directory, "add") == 0) {
                    result += sub_result;
                } else {
                    result *= sub_result;
                }
                
                subdirectory_count++;
            }
        }
        
        closedir(dir);
        
        // Если в текущей директории нет файлов и поддиректорий, возвращаем -1 (ошибка)
        if (file_count == 0 && subdirectory_count == 0) {
            return -1;
        }
        
        return result;
    }
    
    // Если текущая директория не является папкой "add" или "mul", возвращаем -1 (ошибка)
    return -1;
}

int main() {
    const char* root_directory = ".";
    int result = calculate_expression(root_directory);
    FILE *output = fopen("result.txt", "w");
    if(output){
        fprintf(output, printf("%d\n", result););
        fclose(output);
    }
 
    
    return 0;
}