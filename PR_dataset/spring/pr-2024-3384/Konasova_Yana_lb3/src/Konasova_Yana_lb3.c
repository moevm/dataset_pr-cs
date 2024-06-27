#include <dirent.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MASSIV 100
#define STEP 20
struct Sentence{
    int number;
    char* str;
};
struct Array{
    int position;
    int max_count;
    struct Sentence* data;
};
void get_bigger(struct Array *arr){
    if(arr->position >= arr->max_count){
        arr->max_count += STEP;
        struct Sentence *tmp = realloc(arr->data, arr->max_count * sizeof(struct Sentence));
        if(tmp){ 
            arr->data = tmp;
        }else{
            puts("Failed to allocate memory!");
        }
    }
        
}
int cmp_file_info(const void *a, const void *b){
    struct Sentence *info_a = (struct Sentence *)a;
    struct Sentence *info_b = (struct Sentence *)b;
        if(info_a->number > info_b->number) return 1;
        if(info_a->number < info_b->number) return -1;
        return strcmp(info_a->str, info_b->str); 
            
}
struct Sentence get_sent(char* buf, int number){
    struct Sentence sent;
    sent.number=number;
    sent.str=strdup(buf);
    return sent;
}
char *pathcat(const char *path1, const char *path2){
    int res_path_len = strlen(path1) + strlen(path2) + 2;
    char *res_path = malloc(res_path_len * sizeof(char));
    sprintf(res_path, "%s/%s", path1, path2);
    return res_path;
} 
void list_dir(const char *dirPath, struct Array *arr)
{
    DIR *dir = opendir(dirPath); 
    FILE *file;
    if(dir) { 
        struct  dirent *de = readdir(dir);  
        while (de) { 
            if(de->d_type == DT_REG && strstr(de->d_name, ".txt") && !(strstr(de->d_name, "result.txt"))){
                char *file_path = pathcat(dirPath, de->d_name);
                file= fopen(file_path, "r");
                int num=0;
                fscanf(file, "%d", &num);
                int i=0;
                int size_of_arr =MASSIV;
                char* buf=(char*)malloc(MASSIV*sizeof(char));
                fgetc(file);
                char c;
                while((c=fgetc(file))!=EOF){
                    buf[i]=c;
                    i++;
                    if (i==size_of_arr){
                        size_of_arr+=STEP;
                        char* buf = realloc(buf, size_of_arr*sizeof(char));
                        // if (buf1){
                        //     buf=buf1;
                        // }else{
                        //     puts("Failed to allocate memory!");
                        // }
                    }
                }

                
                
                buf[i]='\0';
                arr->data[arr->position++]=get_sent(buf, num);
                get_bigger(arr);
                free(buf);
                free(file_path);
                fclose(file);
                
            }else if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){
                char *new_dir = pathcat(dirPath, de->d_name); 
                list_dir(new_dir, arr);
                free(new_dir);
                
            }
            de = readdir(dir);
        }
        closedir(dir);
    }else
        printf("Failed to open %s directory\n", dirPath);
     
}
int main(){
    FILE *file=fopen("result.txt", "w");
    struct Array arr;
    arr.position=0;
    arr.max_count=MASSIV;
    arr.data= malloc(arr.max_count * sizeof(struct Sentence)); 
    list_dir(".", &arr);
    qsort(arr.data, arr.position, sizeof(struct Sentence), cmp_file_info);
    

    for (int i=0; i<arr.position; i++){
        fprintf(file, "%d %s\n", arr.data[i].number, arr.data[i].str);
        free(arr.data[i].str);
    }
    free(arr.data);
    fclose(file);
    return 0;
}