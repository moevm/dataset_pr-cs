#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <regex.h>

#define PRESENT_DIR "."
#define PARENT_DIR ".."
#define START_DIR "./root"
#define ENDL "\n"
#define START_DIR_BUFFER_SIZE 7
#define NULL_AND_SLASH_CH_BUFFER_SIZE 2
#define START_SENTENCE_ARRAY_SIZE 1
#define NEW_SENTENCE_BUFFER_SIZE 1

const char *output_file = "./result.txt";
const char *file_extension_pattern = "^.+\\.txt$";

typedef struct Sentence{
    long long num;
    char *text;
} Sentence;

int check_file_extension(char *filename, regex_t regex_compiled){
    return regexec(&regex_compiled, filename, 0, NULL, 0) == 0;
}

void dir_processing(char *current_path, Sentence **result, long long *sentences_num, regex_t regex_compiled){
    DIR *current_dir = opendir(current_path);

    if(current_dir){
        struct dirent *sub_dir = readdir(current_dir);

        while(sub_dir){
            long long path_len = strlen(current_path) + NULL_AND_SLASH_CH_BUFFER_SIZE;
            char *new_path = (char *)calloc(path_len, sizeof(char));

            strcpy(new_path, current_path);
            strcat(new_path, "/");

            if(strcmp(sub_dir->d_name, PRESENT_DIR) == 0 || strcmp(sub_dir->d_name, PARENT_DIR) == 0){
                sub_dir = readdir(current_dir);
                continue;
            }

            new_path = (char *)realloc(new_path, (path_len + strlen(sub_dir->d_name)) * sizeof(char));
            strcat(new_path, sub_dir->d_name);

            if(sub_dir->d_type == DT_DIR)
                dir_processing(new_path, result, sentences_num, regex_compiled);

            else if(sub_dir->d_type == DT_REG && check_file_extension(sub_dir->d_name, regex_compiled)){
                FILE *file = fopen(new_path, "r");
                if(file){
                    fscanf(file, "%lld ", &((*result)[*sentences_num].num));

                    int text_len = 0, memory = 1;
                    char *buffer = (char *)calloc(1, sizeof(char));
                    
                    char ch;
                    while((ch = fgetc(file)) != EOF){
                        buffer[text_len] = ch;
                        text_len++;
                        if(text_len >= memory){
                            memory *= 2;
                            buffer = (char *)realloc(buffer, memory * sizeof(char));
                        }
                    }

                    (*result)[*sentences_num].text = buffer;
                    (*sentences_num)++;
                    *result = (Sentence *)realloc(*result, (*sentences_num + NEW_SENTENCE_BUFFER_SIZE) * sizeof(Sentence));
                    fclose(file);
                }
            }

            sub_dir = readdir(current_dir);
        }

        closedir(current_dir);
    }
}

int compare(const void *first, const void *second){
    if(((Sentence *)first)->num > ((Sentence *)second)->num)
        return 1;
    else if(((Sentence *)first)->num == ((Sentence *)second)->num)
        return 0;
    else
        return -1;
}

void print_to_file(Sentence *result, long long sentences_num){
    FILE *file = fopen(output_file, "w");
    if(file){
        for(long long i = 0; i < sentences_num; i++){
            fprintf(file, "%lld %s", result[i].num, result[i].text);
            if(i < sentences_num - 1)
                fprintf(file, ENDL);
        }

        fclose(file);
    }
}

int main(){
    long long sentences_num = 0;
    Sentence *result = (Sentence *)calloc(START_SENTENCE_ARRAY_SIZE, sizeof(Sentence));

    char *current_path = (char *)calloc(START_DIR_BUFFER_SIZE, sizeof(char));
    strcat(current_path, START_DIR);

    regex_t regex_compiled;
    regcomp(&regex_compiled, file_extension_pattern, REG_EXTENDED);

    dir_processing(current_path, &result, &sentences_num, regex_compiled);

    qsort(result, sentences_num, sizeof(Sentence), compare);

    print_to_file(result, sentences_num);

    return 0;
}