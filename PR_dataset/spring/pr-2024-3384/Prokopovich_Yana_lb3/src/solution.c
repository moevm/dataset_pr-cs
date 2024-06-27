#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>

void readFile(char* filepath, char*** text, int* count){
    FILE* file = fopen(filepath, "r");
    if (file){
        int length = 0;
        char symbol;
        char* string = malloc(sizeof(char)); 
        while((symbol = fgetc(file)) != EOF){
            string = realloc(string, (length + 1) * sizeof(char)); 
            string[length++] = symbol;
        }
        string = realloc(string, (length + 1) * sizeof(char)); 
        string[length] = '\0';
        (*text)[*count] = string;
        (*count)++;
        *text = (char **) realloc(*text, (*count + 1) * sizeof(char *)); 
        fclose(file);
    }
}

void dirLookup(char* root, char*** text, int* count){
    char current_dir[256];
    strncpy(current_dir, root, 256);

    DIR* root_dir = opendir(current_dir);
    struct dirent* dir = readdir(root_dir);

    while(dir){
        if(dir->d_type == DT_REG && strstr(dir->d_name, ".txt") && strcmp(dir->d_name, "result.txt") != 0){  
            char filepath[256];
            snprintf(filepath, sizeof(filepath), "%s/%s", current_dir, dir->d_name);
            readFile(filepath, text, count);
        }
        else if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".") && strcmp(dir->d_name, "..")){ 
            char sub_dir[256];
            snprintf(sub_dir, sizeof(sub_dir), "%s/%s", current_dir, dir->d_name);
            dirLookup(sub_dir, text, count);
        }
        dir = readdir(root_dir);
    }
    closedir(root_dir);
}

int compareByDigit(const void* a, const void* b){
    char *stringA = *(char**) a;
    long int A = strtol(stringA, NULL, 10);
    char *stringB = *(char**) b;
    long int B = strtol(stringB, NULL, 10);
    if(A > B){
        return 1;
    }else if(A < B){
        return -1;
    }   
    return 0;
}

int main(){
    FILE* file = fopen("./result.txt", "w");
    int count = 0;
    char **text = malloc(sizeof(char *));
    dirLookup(".", &text, &count);
    qsort(text, count, sizeof(char *), compareByDigit);
    for(int i = 0; i < count; i++){
        fprintf(file, "%s\n", text[i]);
        free(text[i]);
    }
    free(text);
    fclose(file);
    return 0;
}