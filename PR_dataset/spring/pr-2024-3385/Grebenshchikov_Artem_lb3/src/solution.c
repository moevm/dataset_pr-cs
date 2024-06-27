#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <unistd.h>
#include <ctype.h>

#define MAX_LEN_PATH 1024

int compare(const void *a, const void *b){
    char **string_a = (char **)a;
    char **string_b = (char **)b;
    long a_num = atol(*string_a);
    long b_num = atol(*string_b);
    if(a_num > b_num)
        return 1;
    if(a_num < b_num)
        return -1;
    return 0;
}

void read_file(const char *file_path, char*** sentences, int *counter_sentence) {
    FILE *file = fopen(file_path, "r");
    if(!file){
        printf("Error opening file");
        exit(1);
    }
    char* line = (char*)malloc(sizeof(char));
    int len_line = 0;
    char c;
    while ((c = fgetc(file)) != EOF){
        line[len_line++] = c;
        line = realloc(line, sizeof(char) * (len_line + 1));
    }
    fclose(file);
    line[len_line] = '\0';
    (*sentences)[(*counter_sentence)++] = line;
    *sentences = (char **)realloc(*sentences, sizeof(char*) * (*counter_sentence + 1));
}


void read_sentences(const char *path, char ***sentences, int *counter_sentence){
    DIR *dir = opendir(path);
    if(!dir){
        printf("Error opening directory");
        exit(1);
    }
    struct dirent *entry;
    while ((entry = readdir(dir))){
        char new_path[MAX_LEN_PATH];
        sprintf(new_path, "%s/%s", path, entry->d_name);
        if((entry->d_type == DT_DIR) && strcmp(entry->d_name, ".") && strcmp(entry->d_name, "..")){
            read_sentences(new_path, sentences, counter_sentence);
        }
        if((entry->d_type == DT_REG) && strstr(entry->d_name, ".txt") && !strstr(entry->d_name, "result.txt")){   
            read_file(new_path, sentences, counter_sentence);
        }
    }
    closedir(dir);
}

int main(){
    char file_path[MAX_LEN_PATH];
    if(!getcwd(file_path, sizeof(file_path))){
        printf("Error getting the path");
        return 1;
    }
    int cnt_snt = 0;
    int *counter_sentence = &cnt_snt;
    char** sentences = (char**)malloc(sizeof(char*));
    read_sentences(file_path, &sentences, counter_sentence);
    qsort(sentences, *counter_sentence, sizeof(char*), compare);
    char file_end[] = "/result.txt";
    strcat(file_path, file_end);
    FILE *file = fopen(file_path, "w+");
    if(!file){
        printf("Error opening result.txt");
        return 1;
    }
    int i = 0;
    for(; i < (*counter_sentence) -1; i++){
        fprintf(file, "%s\n", sentences[i]);
        free(sentences[i]);
    }
    fprintf(file, "%s", sentences[(*counter_sentence) -1]);
    free(sentences[(*counter_sentence) -1]);
    free(sentences);
    fclose(file);
    return 0;
}