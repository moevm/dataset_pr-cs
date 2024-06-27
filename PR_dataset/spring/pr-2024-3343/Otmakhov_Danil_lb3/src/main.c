#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

#define STEP 10
#define ROOT_DIR "root"
#define RESULT_FILE "result.txt"


typedef struct fileinfo_t{
    char *text;
    int number;
} FileInfo;

typedef struct array_t{
    size_t cur_index;
    size_t max_count;
    FileInfo *data;
} Array;


char *pathcat(const char *path1, const char *path2){
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);

    return res_path;
}


void check_and_resize(Array *arr){
    if(arr->cur_index >= arr->max_count){
        arr->max_count += STEP;
        FileInfo *tmp = realloc(arr->data, arr->max_count * sizeof(FileInfo));
        arr->data = tmp;
    }
}


int cmpFileInfo(const void *obj_a, const void *obj_b){
    FileInfo *info_a = (FileInfo *)obj_a;
    FileInfo *info_b = (FileInfo *)obj_b;
    if (info_a->number < info_b->number)
        return -1;
    if (info_a->number > info_b->number)
        return 1;
    return info_a->number == info_b->number;
}


FileInfo getFileInfo(char *dir_name, char *file_name){
    char* file_path = pathcat(dir_name, file_name);

    FileInfo info;
    info.text = malloc(256);

    FILE *file = fopen(file_path, "r");
    char str[256];
    fgets(str, 256, file);

    snprintf(info.text, sizeof(str), "%s", str);

    char *num = strtok (str, " ");
    info.number = atoi(num);

    free(file_path);
    fclose(file);

    return info;
}


void listDir(char *dir_name, Array *arr){
    DIR *root_dir = opendir(dir_name);

    if (!root_dir)
        return;

    struct dirent *dir = readdir(root_dir);
    while (dir){
        char* new_dir = pathcat(dir_name, dir->d_name);

        if(dir->d_type == DT_REG){
            arr->data[arr->cur_index++] = getFileInfo(dir_name, dir->d_name);
            check_and_resize(arr);
            free(new_dir);
        }

        else if (dir->d_type == DT_DIR && strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0){
            listDir(new_dir, arr);
            free(new_dir);
        }

        dir = readdir(root_dir);
    }

    closedir(root_dir);
}


int main(){
    Array info_arr;
    info_arr.cur_index = 0;
    info_arr.max_count = STEP;
    info_arr.data = malloc(info_arr.max_count * sizeof(FileInfo));

    listDir(ROOT_DIR, &info_arr);
    qsort(info_arr.data, info_arr.cur_index, sizeof(FileInfo), cmpFileInfo);

    FILE *res_file = fopen(RESULT_FILE, "w");

    for (size_t i = 0; i < info_arr.cur_index; i++){
        fprintf(res_file, "%s\n", info_arr.data[i].text);
        free(info_arr.data[i].text);
    }

    free(info_arr.data);
    fclose(res_file);

    return 0;
}
