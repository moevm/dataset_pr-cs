#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#define STEP 10
struct FileInfo{
 char *full_path; // полный путь
 char FirstL; // сумма цифр
};

struct Array{
 int cur_index; // текущее количество элементов и индекс для записи следующего элемента
 int max_count; // текущий максимальный размер массив
 struct FileInfo *data; // информация о файлах
};

char *pathcat(const char *path1, const char *path2){
 int res_path_len = strlen(path1) + strlen(path2) + 2; //определение длины новой строки с учетом символов / и символа конца стоки
 char *res_path = malloc(res_path_len * sizeof(char)); // выделение памяти под новую строку
 sprintf(res_path, "%s/%s", path1, path2); // форматный вывод данный в строку
 return res_path;
}

void check_and_resize(struct Array *arr){
 if(arr->cur_index >= arr->max_count){// достигнут максимальный размер
 arr->max_count += STEP;
 struct FileInfo *tmp = realloc(arr->data, arr->max_count* sizeof(struct FileInfo));
 if(tmp){ // проверка, что realloc смог выделить память
 arr->data = tmp;
 }else{
 puts("Failed to allocate memory!");
  }
 }
}

struct FileInfo get_file_info(const char *filename, const char *dir_name){
 struct FileInfo info;
 info.full_path = pathcat(dir_name, filename); // получение полного пути
 info.FirstL = filename[0]; // Название для условия
 return info;
}

void list_dir(const char *dir_name, struct Array *arr, char* str){
 DIR *dir = opendir(dir_name);
 if(dir){
 struct dirent *de = readdir(dir);
 while (de){
 char Letter = de->d_name[0];
 if(de->d_type == DT_REG && strchr(str, Letter) && strlen(de->d_name) < 6){// элемент директории – файл
 // Проверка на УСЛОВИЕЕЕ
 arr->data[arr->cur_index++] = get_file_info(de->d_name, dir_name); // запись информации о файле в массив
 check_and_resize(arr); // увеличение размера массива
}else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
 char *new_dir = pathcat(dir_name, de->d_name);
 list_dir(new_dir, arr, str);
 free(new_dir);
}
//++++++++++++++++++++++++++++++++++++++
 de = readdir(dir);
 }
 closedir(dir);
 }else
 printf("Failed to open %s directory\n", dir_name);
}

void print_seq(struct Array *arr, char* str){
    int len = strlen(str);
    FILE *file = fopen("result.txt", "w"); // Открываем файл для записи
    if (file == NULL) {
        printf("Ошибка открытия файла\n");
        return;
    }


    for (int i = 0; i < len; i++) {
        for (int j = 0; j < arr->cur_index; j++) {
            if (arr->data[j].FirstL == str[i]) {
                fprintf(file, "%s\n", arr->data[j].full_path); // Записываем в файл
                break;
            }
        }
    }
}

int main(){
struct Array arr; // создание структуры массива
 arr.cur_index = 0;
 arr.max_count = STEP;
 arr.data = malloc(arr.max_count * sizeof(struct FileInfo));
 char str[100];
 size_t size = 0;
 printf("Входная строка:\n");
 scanf("%s", str);
 list_dir("./tmp", &arr ,str);
 print_seq(&arr, str);
 return 0;
}