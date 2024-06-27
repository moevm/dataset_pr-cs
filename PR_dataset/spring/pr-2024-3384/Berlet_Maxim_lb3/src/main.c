#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

typedef struct file {
    char* file_path;
    char* file_name;
    int is_used;
}file_t;

void push_back(file_t* arr, char* fname, char* pname){
    arr->file_path = strdup(pname);
    arr->file_name = strdup(fname);
    arr->is_used = 0;
}

void list_dir(const char* dirPath, int* counter, file_t* ans_arr) {
    DIR* dir;
    struct dirent* dir_entry;

    char cur_dir[256];
    char cur_file_name[256];

    if(dir = opendir(dirPath)) {
        while (dir_entry = readdir(dir)) {
            if (!strcmp (dir_entry->d_name,".") || !strcmp(dir_entry->d_name,"..")) {
                continue;
            }

            strcpy(cur_dir, dirPath);
            strcat(cur_dir, "/");
            strcat(cur_dir, dir_entry->d_name);

            if(dir_entry->d_type == DT_DIR) {
                list_dir(cur_dir, counter, ans_arr);
            }
            else {
                strcpy(cur_file_name, dir_entry->d_name);
                char* tmp = strtok(cur_file_name, ".");
                if(strlen(tmp) == 1){
                    push_back(&(ans_arr[*counter]), tmp, cur_dir);
                    (*counter)++;
                }
            }
        }
    }
    else
    {
        printf("Wrong dir path!");
        exit(1);
    }
    closedir(dir);
}

void print_ans(char* name, file_t* arr, int counter) {
    FILE* file = fopen("result.txt", "w");
    int len = strlen(name);
    int i, j;
    for(i = 0; i < len; i++) {
        for(j = 0; j <  counter; j++) {
            if(name[i] == arr[j].file_name[0] & arr[j].is_used == 0){
                fprintf(file, "%s\n", arr[j].file_path);
                arr[j].is_used = 1;
                break;
            }
        }
    }
    fclose(file);
}

int main(int argc, char* argv[]) {
    char word[256];
    fgets(word, 256, stdin);

    int counter = 0;
    file_t ans_arr[256];
    list_dir("./tmp", &counter, ans_arr);

    print_ans(word, ans_arr, counter);
    return 0;
}