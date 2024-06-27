#include <stdio.h>  
#include <string.h>  
#include <stdlib.h>  
#include <dirent.h>  
  
char *pathcat(char *path1, char *path2){  
    char *res_path = malloc((strlen(path1) + strlen(path2) + 2) * sizeof(char));  
    res_path[0] = '\0';  
    strcat(res_path, path1);  
    strcat(res_path, "/");  
    strcat(res_path, path2);  
    res_path[strlen(path1) + strlen(path2) + 1] = '\0';  
    return res_path;  
}  
  
  
/*char *get_file_content(char *file_path){  
    FILE *file;  
    file = fopen(file_path, "r");  
    char *text = calloc(1, sizeof(char));  
    int n = 0;  
    char ch;  
    while ((ch = fgetc(file)) != EOF) {  
        text[n++] = ch;  
        text = realloc(text, (n+1) * sizeof(char));  
          
    }  
    text[n] = '\0';  
    fclose(file);  
    return text;  
}
  
void list_dir(char *dir_name, char ***arr, int *k){ 
    DIR *dir = opendir(dir_name); 
    struct dirent *de; 
    while (de = readdir(dir)){ 
        char *filename = de->d_name; 
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){ 
            char *new_dir = pathcat(dir_name, filename); 
            list_dir(new_dir, arr, k); 
            free(new_dir); 
        } 
        else{ 
            char *file_extension = strrchr(de->d_name, '.'); 
            if (file_extension){ 
                if (strcmp(file_extension, ".txt") == 0 && (strcmp(filename, "result.txt")!=0)){ 
                    char *new_path = pathcat(dir_name, filename);
                    char *text = get_file_content(new_path);
                    free(new_path);
                    (*arr)[*k] = malloc(strlen(text) + 1 *sizeof(char));
                    strcpy((*arr)[*k], text);
                    (*k)++;
                    *arr = realloc(*arr, (*k+1)*sizeof(char*));  
                } 
            } 
        } 
    } 
    closedir(dir); 
    return; 
}*/
 
void list_dir(char *dir_name, char ***arr, int *k){ 
    DIR *dir = opendir(dir_name); 
    struct dirent *de; 
    while (de = readdir(dir)){ 
        char *filename = de->d_name; 
        if (de->d_type == DT_DIR && strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, "..") != 0){ 
            char *new_dir = pathcat(dir_name, filename); 
            list_dir(new_dir, arr, k); 
            free(new_dir); 
        } 
        else{ 
            char *file_extension = strrchr(de->d_name, '.'); 
            if (file_extension){ 
                if (strcmp(file_extension, ".txt") == 0 && (strcmp(filename, "result.txt")!=0)){ 
                    char *new_path = pathcat(dir_name, filename);
                    FILE *file;
                    file = fopen(new_path, "r");
                    free(new_path);
                    char str[1024];  
                    while (fgets(str, 1024, file) != NULL){
                        (*arr)[*k] = malloc(strlen(str) + 1 *sizeof(char));
                        strcpy((*arr)[*k], str);
                        (*k)++;
                        *arr = realloc(*arr, (*k+1)*sizeof(char*));
                    }
                } 
            } 
        } 
    } 
    closedir(dir); 
    return; 
}
  
long get_digit(char *input){  
    char *str = strdup(input);  
    char *token = strtok(str, " ");  
    long res = atol(token);  
    free(str);  
    return res;  
}  
  
int cmp(const void *a, const void *b) {  
    char *sen1 = *((char **) a);  
    char *sen2 = *((char **) b); 
    long dig1 = get_digit(sen1); 
    long dig2 = get_digit(sen2); 
    if (dig1 > dig2){ 
        return 1; 
    } 
    else if (dig1<dig2){ 
        return -1; 
    } 
    else if (dig1 == dig2){ 
        return 0; 
    } 
}  
  
int main(){  
    int tmp = 0; 
    int *k = &tmp;  
    char **arr = calloc(1, sizeof(char *));  
    list_dir(".", &arr, k); 
    qsort(arr, *k, sizeof(char*), cmp);  
    FILE *res;  
    res = fopen("result.txt", "w");
    int i;  
    for (i = 0; i < *k; i++) {  
        fprintf(res, "%s\n", arr[i]);  
        free(arr[i]);  
    } 
    fclose(res);  
    free(arr);  
    return 0;  
}
