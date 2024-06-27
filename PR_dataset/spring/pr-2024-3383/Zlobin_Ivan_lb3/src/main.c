#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#define BLOCK_SIZE 8
char * input(){
    char sim=getchar();
    char *str=malloc(sizeof(char)*BLOCK_SIZE);
    int i=0;
    for(;sim!='\n';sim=getchar()){
        str[i++]=sim;
        if(i%BLOCK_SIZE==0){
            str=realloc(str, sizeof(char)*(i+BLOCK_SIZE));
        }
    }
    return str;
}

void func(char *dir_path, char *str, char **array){
    DIR *dir=opendir(dir_path);
    if(dir){
        struct dirent *dr;
        while((dr=readdir(dir))!=NULL){
            if(strcmp(".", dr->d_name) && strcmp("..", dr->d_name)){
                char * drp=strdup(dir_path);
                drp=realloc(drp, sizeof(char)*(strlen(dir_path)+strlen(dr->d_name)+3));
                drp=strcat(strcat(drp, "/"), dr->d_name);
                func(drp, str, array);
                free(drp);
            }
            if(dr->d_type==DT_REG && strlen(dr->d_name)==5){
                for(int i=0;i<strlen(str);++i){
                    if(dr->d_name[0]==str[i]){
                        array[i]=malloc(sizeof(char)*(strlen(dir_path)+10));
                        array[i]=strcat(strcat(strcpy(array[i], dir_path), "/"), dr->d_name);
                    }
                }
            }
            
        }
        closedir(dir);
    }
}

int main(void) {
    FILE *file;
    char directory[]="./tmp";
    char *str=input();
    char **array=malloc(sizeof(char*)*strlen(str));
    func(directory, str, array);
    file = fopen("result.txt", "w");
    for(int i=0;i<strlen(str);++i){
        fputs(array[i], file);
        fputs("\n", file);
        free(array[i]);
    }
    free(array);
    free(str);
    fclose(file);
    return 0;
}