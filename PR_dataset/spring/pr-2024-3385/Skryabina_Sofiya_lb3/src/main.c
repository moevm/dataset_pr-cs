#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>

#define MAX_FILENAME_SZ 256
#define MAX_FILEPATH_SZ 4096
#define MAX_NUM 100

int
file_validator(char* filename) {
    int res = 0;
    if (strlen(filename)>3)
        res = !(strcmp(filename + strlen(filename) - 4, ".txt"));
    return res;
}

int
dir_validator(char *filename) {
    int res;
    res = !((strcmp(filename, "mul")) && (strcmp(filename, "add")));
    return res;
}

int
read_num(char* filepath, int nums[]) {
    *(filepath + strlen(filepath)-1) = '\0';
    FILE* file = fopen(filepath, "r");
    if (file == NULL){
        perror("Can't open the file");
        return 0;
    }
    int cur_num, count;
    count = 0;
    while (!feof(file)) {
        int tmp = fscanf(file, "%d", &cur_num);
        if (tmp > 0) { 
            nums[count] = cur_num;
            count++;
        }
    }
    fclose(file);
    return count;
}

int calculation (char* previous) {
    DIR* previous_dir = opendir(previous);
    if (!previous_dir){
        perror("Can't open dir");
        return 0;
    }
    struct dirent* entry = readdir(previous_dir);
    char file_path[MAX_FILEPATH_SZ];
    int result;
    if ((strcmp(previous + strlen(previous) - 4, "add/") == 0)) {
        result = 0;
    }
    else {
        result = 1;
    }

    while (entry) {
        while(!(dir_validator(entry->d_name) && (entry->d_type == DT_DIR)) && !file_validator(entry->d_name)) {
            entry = readdir(previous_dir);
            if (!entry) {
                return result;
            }
            continue;
        }
        sprintf(file_path, "%s%s/", previous, entry->d_name);
        if ((strcmp(previous + strlen(previous) - 4, "add/") == 0)) {
            if(entry->d_type == DT_DIR) {
                result += calculation(file_path);
            }
            else {
                int nums_buf[MAX_NUM];
                int count = read_num(file_path, nums_buf); 
                for (int i = 0; i < count; i++){
                    result+= nums_buf[i];
                }
            }
        }

        if ((strcmp(previous + strlen(previous) - 4, "mul/") == 0)) {
            if(entry->d_type == DT_DIR){
                result *= calculation(file_path);
            }
            else {
                int nums_buf[MAX_NUM];
                int count = read_num(file_path, nums_buf);
                for (int i = 0; i < count; i++){
                    result *= nums_buf[i];
                }
            }
        }
        entry = readdir(previous_dir);
    }
    closedir(previous_dir);
    return result;
}

int main() {
    int result;
    DIR* start_dir = opendir("tmp");
    struct dirent* entry = readdir(start_dir);
    while(!(dir_validator(entry->d_name))) {
            entry = readdir(start_dir);
            continue;
    }
    char start_path[10] = "tmp/";
    strcat(start_path, entry->d_name);
    strcat(start_path, "/");
    result = calculation(start_path);
    closedir(start_dir);
    FILE *output = fopen("result.txt", "w");
    fprintf(output, "%d\n", result);
    fclose(output);
    return 0;
}
