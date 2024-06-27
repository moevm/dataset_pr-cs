#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <ctype.h> 
#include <dirent.h> 
#include <unistd.h> 


int cmp(const void *a, const void *b) 
{ 
    char **line_a = (char **)a; 
    char **line_b = (char **)b; 
    long a_num = atol(*line_a); 
    long b_num = atol(*line_b); 
    if (a_num < b_num) 
        return -1; 
    if (a_num > b_num) 
        return 1; 
    return 0; 
} 

void get_text(char* path, char*** array_text, int* count){
    DIR *dir = opendir(path);
    if(dir){
        struct  dirent *de = readdir(dir);
        while(de){
            char current_path[1024];
            sprintf(current_path, "%s/%s", path, de->d_name);
            if(de->d_type == DT_DIR){
                if(strcmp(de->d_name, ".") == 0 || strcmp(de->d_name, "..") == 0){
                    de = readdir(dir);
                    continue;
                }
                get_text(current_path, array_text, count);
            }
            if(de->d_type == DT_REG && strstr(de->d_name, ".txt")){
                if(strstr(de->d_name, "result.txt")){
                    continue;
                }
                FILE *file;
                file = fopen(current_path, "r");
                if(file){
                    char ch = fgetc(file);
                    int i = 0;
                    int len_str = 40;
                    (*array_text)[(*count)] = malloc(sizeof(char)*len_str);
                    while(ch != EOF){
                        (*array_text)[(*count)][i] = ch;
                        i++;
                        if(i + 2 == len_str){
                            len_str += 20;
                            (*array_text)[(*count)] = realloc((*array_text)[(*count)], sizeof(char)*len_str);
                        }
                        ch = fgetc(file);
                    }
                    (*array_text)[(*count)][i] = '\0';
                    (*array_text)[(*count)] = realloc((*array_text)[(*count)], (i+1)*sizeof(char));
                    (*count) += 1;
                    (*array_text) = realloc((*array_text), sizeof(char*)*((*count)+1));
                    fclose(file);
                }
            }
            de = readdir(dir);
        }
    }
    closedir(dir);
}




int main(){
    char path[1024];
    getcwd(path, sizeof(path));
    char** array_text = malloc(sizeof(char*));
    int count = 0;
    get_text(path, &array_text, &count);
    qsort(array_text, count, sizeof(char*), cmp);
    char end[] = "/result.txt"; 
    strcat(path, end); 
    FILE *file = fopen(path, "w+");
    fprintf(file, "%s", array_text[0]);
    free(array_text[0]);
    for(int j = 1; j < count; j++){
        fprintf(file, "\n%s", array_text[j]);
        free(array_text[j]);
    }
    free(array_text);
    fclose(file);
    return 0;
}
