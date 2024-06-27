#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#define BLOCK 100

typedef struct data{
    char text[BLOCK];
    int n;
}data;

int compar(const void *a, const void *b) {
    const data* data_a = *(data**)a;
    const data* data_b = *(data**)b;
    if (data_a->n < data_b->n) return -1;
    if (data_a->n > data_b->n) return 1;
    return data_a->n == data_b->n;
}

data* read_file(const char *file_name){
    char str_file[BLOCK]; 
    FILE *fin = fopen(file_name,"r");
    data* f = NULL;
    if (fin){
        f = (data*)malloc(sizeof(data));
        fscanf(fin, "%d", &(f->n));
        fgets(str_file, BLOCK, fin);
        strncpy(f->text, str_file, BLOCK);
        fclose(fin);
    }else{
        printf("Failed to open %s file\n", file_name);
    }
    return f;
}
void write_to_file(const char *file_name, int* count, data** strings){
    FILE *fout = fopen(file_name, "w");
    if (fout){
        for (int i = 0; i<(*count); i++){
            fprintf(fout, "%d%s\n", strings[i]->n, strings[i]->text);
            free(strings[i]);
        }
        free(strings);
        fclose(fout);
    } else{
        printf("Failed to open %s file\n", file_name);
    }
}

char *pathcat(const char *path1, const char *path2){
    int res_path_len = strlen(path1) + strlen(path2) + 2; 
    char *res_path = malloc(res_path_len * sizeof(char)); 
    sprintf(res_path, "%s/%s", path1, path2); 
    return res_path;
}

data** list_dir(const char *dir_name, int* count, data** strings){
    DIR *dir = opendir(dir_name);
    if(dir){
        struct dirent *de = readdir(dir);
        while (de){
            if(de->d_type == DT_REG && strstr(de->d_name, ".txt") != NULL && strstr(de->d_name, "result.txt") == NULL){
                char *name_file = pathcat(dir_name, de->d_name);
                data* buf = read_file(name_file);
                if (buf){
                    strings[(*count)++] = buf;
                }
                free(name_file);
            }else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                char *new_dir = pathcat(dir_name, de->d_name); 
                list_dir(new_dir, count, strings); 
                free(new_dir);
            }
            de = readdir(dir);
        }
        closedir(dir);
    }else
        printf("Failed to open %s directory\n", dir_name);   
     
}
int main(){
    int count;
    count = 0;
    data** strings = (data**)malloc(50*BLOCK*sizeof(data*));
    list_dir(".", &count, strings);
    qsort(strings, count, sizeof(data*), compar);
    write_to_file("result.txt", &count, strings);
    return 0;
}
