#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define ADD_SIZE 20
#define LEN_NAME_FILE 5

char* path_maker(char* old_path, char* filename) {
    size_t len_path = strlen(old_path) + strlen(filename) + 2;
    char* new_path = (char*)malloc(len_path * sizeof(char));
    new_path[0] = '\0';
    strcat(new_path, old_path);
    strcat(new_path, "/");
    strcat(new_path, filename);
    return new_path;
}

void DirVoyager(char** storage, char* spl_str, char* path) {
    //Открываем директорию
    DIR* tmp_dir;
    tmp_dir = opendir(path);
    struct dirent* tmp_file;
    while (tmp_file = readdir(tmp_dir)) {
        char* filename = tmp_file->d_name;
        //Если директория, значит открываем
        if (tmp_file->d_type == DT_DIR && strcmp(filename, "..") != 0 && strcmp(filename, ".") != 0) {
            char* new_path = path_maker(path, filename);
            DirVoyager(storage, spl_str, new_path);
        } else {
            //Проверка расширения
            char* ext = strrchr(filename, '.');
            if (!ext) continue;
            if (strcmp(ext, ".txt") == 0 && strlen(filename) == LEN_NAME_FILE) {
                //Ищем индекс символа, чтобы записать адрес в соответствующую ячейку
                char* find_ch = strchr(spl_str, filename[0]);
                if (find_ch) {
                    char* new_path = path_maker(path, filename);
                    storage[find_ch - spl_str] = new_path;
                }
            }
        }
    }
    free(path);
    closedir(tmp_dir);
    return;
}

int main() {
    //Ввод строки
    char *spl_str = malloc(sizeof(char) * ADD_SIZE);
    char ch;
    int count_ch = 0, buf_str = ADD_SIZE;
    while (isspace((ch = getchar())) == 0) {
        if (count_ch >= buf_str) {
            buf_str += ADD_SIZE;
            spl_str = realloc(spl_str, buf_str);
        }
        spl_str[count_ch] = ch;
        count_ch++;
    }
    //Выделение памяти под хранения путей
    char** storage = malloc(sizeof(char*) * count_ch);
    //Запуск обхода
    char* path = path_maker(".", "tmp");
    DirVoyager(storage, spl_str, path);
    //Запись результата
    FILE * res;
    res = fopen("result.txt", "wt");
    for (int i = 0; i < count_ch; i++) {
        fprintf(res, "%s\n", storage[i]);
        free(storage[i]);
    }
    free(spl_str);
    free(storage);
    fclose(res);
    return 0;
}