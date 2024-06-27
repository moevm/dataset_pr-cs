#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>


char *pathcat(const char *path1, const char *path2){
    int res_path_len = strlen(path1) + strlen(path2) + 2; // определение длины новой строки с учетом символов / и символа конца строки
    char *res_path = malloc((res_path_len+1) * sizeof(char)); // выделение памяти под новую строку
    sprintf(res_path, "%s/%s", path1, path2); // форматный вывод данных в строку
    return res_path;
}


void searching(const char *dir_name, const char letter, FILE *fout){
    DIR *dir = opendir(dir_name);
    if(dir){
        struct dirent *de = readdir(dir);
        while (de){
            if(de->d_type == DT_REG){
                if(de->d_name[0] == letter && strlen(de->d_name) == 5){
                    char *new_path = pathcat(dir_name, de->d_name);
                    strcat(new_path, "\n");
                    fprintf(fout, "%s", new_path);
                    free(new_path);
                }
            }else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                // элемент директории – директория
                char *new_dir = pathcat(dir_name, de->d_name); //соединение имён директорий
                searching(new_dir, letter, fout); // рекурсивный вызов
                free(new_dir);
            }
            de = readdir(dir);
        }
        closedir(dir);
    }else
        printf("Failed to open %s directory\n", dir_name);
}


int main(){
    FILE *fout;
    fout = fopen("result.txt", "w"); // открытие файла на запись
    if(fout){
        char *word = malloc(100 * sizeof(char)); // выделение памяти под динамическую строку
        int index = 0;
        int max_size = 100;
        char c;
        while(c != '\n'){ // проверка на достигнутый конец
            c = getchar();
            word[index] = c; // запись символа в строку
            index++;
            if(index > max_size){ // увеличение размера строки
                max_size += 100;
                word = realloc(word, max_size);
            }
        }
        int i;
        for (i = 0; i<strlen(word); i++)
            searching("./tmp", word[i], fout);
        free(word);
    }
    fclose(fout); // закрытие файла
    return 0;
}
