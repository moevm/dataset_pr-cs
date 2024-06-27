#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#define MAX_STRING 1000
#define BLOCK 1000
#define RESET_DIR ".."
#define PREV_DIR "."
#define CUR_DIR "./"
#define TEXT_FOR ".txt"


typedef struct Line{
    long long num;
    char* text;
} Line;

char* pathcat(char* cur_path, char* new_dir){
    char* new_path = malloc((strlen(cur_path) + strlen(new_dir) + 2) * sizeof(char));
    sprintf(new_path, "%s/%s", cur_path, new_dir);
    return new_path;
}

void line_finder(char* fpath, Line** line_list, long long* number_of_lines){
    FILE* file = fopen(fpath, "r");

    if(file){
        fscanf(file, "%lld ", &((*line_list)[*number_of_lines].num));

        int line_size = 0;
        int capacity = 1;
        char *new_line = (char *)calloc(1, BLOCK * sizeof(char));

        char new_char;
        while((new_char = fgetc(file)) != EOF){
            new_line[line_size] = new_char;
            line_size++;
            if(line_size - 1 >= capacity * BLOCK){
                capacity *= 2;
                new_line = (char *)realloc(new_line, capacity * BLOCK * sizeof(char));
            }
        }

        (*line_list)[*number_of_lines].text = new_line;
        (*number_of_lines)++;
    }
    fclose(file);
}

void file_searcher(char* cur_path, Line** line_list, long long* number_of_lines, int* capacity){
    DIR* cur_dir = opendir(cur_path);

    if(cur_dir){
        struct dirent* dir = readdir(cur_dir);
        while(dir){
            char* new_path = pathcat(cur_path, dir->d_name);

            if(dir->d_type == DT_REG && strstr(dir->d_name, TEXT_FOR) != NULL){
                if((*capacity)*BLOCK < (*number_of_lines) + 1){
                    (*capacity)++;
                    *line_list = (Line*)realloc(*line_list, (*capacity) * BLOCK * sizeof(Line));
                } 
                line_finder(new_path, line_list, number_of_lines);
            } else if(dir->d_type == DT_DIR && strcmp(dir->d_name, PREV_DIR) != 0 && strcmp(dir->d_name, RESET_DIR) != 0){
                file_searcher(new_path, line_list, number_of_lines, capacity);
            }
            dir = readdir(cur_dir);
        }
        closedir(cur_dir);
    }
}

void output(Line** line_list, long long number_of_lines, char* file_name){
    FILE *file = fopen(file_name, "w");

    if(file){
        for(long long i = 0; i < number_of_lines; i++){
            fprintf(file, "%lld %s", (*line_list)[i].num, (*line_list)[i].text);
            if(i < number_of_lines - 1)
                fprintf(file, "\n");
        }
    }
    fclose(file);
}

int cmp(const void* a, const void* b){
    return ((Line*)a)->num > ((Line*)b)->num;
}

int main(){
    Line* line_list = (Line*)calloc(BLOCK, sizeof(Line));
    long long number_of_lines = 0;
    int capacity = 1;

    file_searcher(CUR_DIR, &line_list, &number_of_lines, &capacity);
    qsort(line_list, number_of_lines, sizeof(Line), cmp);
    output(&line_list, number_of_lines, "./result.txt");

    return 0;
}
