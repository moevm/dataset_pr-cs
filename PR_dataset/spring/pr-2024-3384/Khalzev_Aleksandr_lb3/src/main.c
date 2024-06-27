#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

int* strToNum(char* input, int* size) {
    int count = 0;

    for (unsigned long i = 0; i < strlen(input); i++) {
        if (input[i] != ' ' && (i == 0 || input[i-1] == ' ')) {
            count++;
        }
    }

    int* numbersArray = (int*)malloc(count * sizeof(int));

    int index = 0;
    char* token = strtok(input, " ");
    while (token != NULL) {
        numbersArray[index++] = (int)atoi(token);
        token = strtok(NULL, " ");
    }

    *size = count;
    return numbersArray;
}

int list_dir(char *dirPath, int y_n)
{
    DIR *dir = opendir(dirPath);
    struct  dirent *de = readdir(dir);
    int res;
    if(y_n == 1){
        res = 0;
    }else{
        res = 1;
    }
    while (de){
        if(de->d_type == DT_REG && strstr(de->d_name, ".txt") != NULL){
            int num = strlen(dirPath) + strlen(de->d_name) + 2, n = 1;
            char* nw_way = (char*)malloc(sizeof(char) * num);
            strcpy(nw_way, dirPath);
            strcat(nw_way, "/");
            strcat(nw_way, de->d_name);
            FILE *file;
            file = fopen(nw_way, "r");
            int buf = 10, i = 0;
            char* str = (char*)malloc(buf * sizeof(char));
            str[0] = '\0';
            while(fscanf(file, "%c", &str[i]) != EOF){
                i++;
                str[i + 1] = '\0';
                if((i + 1) == (buf - 1)){
                    buf *= 2;
                    str = (char*)realloc(str, buf * sizeof(char));
                }
            }
            int size = 0;
            if (strlen(str) == 0){
                n = 0;
            }
            if(n == 1){
                int* mas = strToNum(str, &size);
                if(y_n == 1){
                    for(int i = 0; i < size; i++){
                        res = res + mas[i];
                    }
                }else{
                    for(int i = 0; i < size; i++){
                        res = res * mas[i];
                    }
                }
                free(mas);
            }
            free(nw_way);
            free(str);
            fclose(file);
        }else if(de->d_type == DT_DIR && (strcmp(de->d_name, "add") == 0 || strcmp(de->d_name, "mul") == 0)){
            int add_y_n;
            if(strcmp(de->d_name, "add") == 0){
                add_y_n = 1;
            }else{
                add_y_n = 0;
            }
            int num = strlen(dirPath) + strlen(de->d_name) + 2;
            char* nw_adr = (char*)malloc(sizeof(char) * num);
            strcpy(nw_adr, dirPath);
            strcat(nw_adr, "/");
            strcat(nw_adr, de->d_name);
            int res1 = list_dir(nw_adr, add_y_n);
            if(y_n == 1){
                res = res + res1;
            }else if (y_n == 0){
                res = res * res1;
            }
            free(nw_adr);
        }
        de = readdir(dir);
    }
    return res;

    closedir(dir);
}

int main(){
    FILE* file = fopen("result.txt", "w");
    fprintf(file, "%d", list_dir("/home/box/tmp", 0));
    return 0;
}


