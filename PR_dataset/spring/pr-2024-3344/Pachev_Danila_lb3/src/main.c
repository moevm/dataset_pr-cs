#include <stdio.h>
#include <dirent.h>
#include <string.h>


int count_numbers(char* path, char* operation){
    FILE *file;
    file = fopen(path, "r");
    if (file == NULL){
        printf("File not found\n");
        return 0;
    }

    if (strcmp(operation, "add") == 0){
        int sum = 0;
        int number;
        while (fscanf(file, "%d", &number) != EOF){
            sum += number;
        }
        return sum;
    }
    else if (strcmp(operation, "mul") == 0){
        int mul = 1;
        int number;
        while (fscanf(file, "%d", &number) != EOF){
            mul *= number;
        }
        return mul;
    }

}
char* check_first_directory(char* path){
    DIR* d;
    struct dirent *dir;
    d = opendir(path);
    if (d) {
        while ((dir = readdir(d)) != NULL) {
            if (dir->d_type == DT_DIR) {
                if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 &&
                    strcmp(dir->d_name, ".DS_Store") != 0) {
                    return dir->d_name;
                }
            }
        }
        closedir(d);
    }

}

int traverse_directory(char* path,char* operation){
    int result;
    if (strcmp(operation, "add") == 0){
        result = 0;
    }
    else if(strcmp(operation, "mul") == 0){
        result = 1;
    }
    DIR *d;
    struct dirent *dir;
    d = opendir(path);
    if (d){
        while ((dir = readdir(d)) != NULL){
            if (dir->d_type == DT_DIR){
                if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0 && strcmp(dir->d_name, ".DS_Store") != 0){
                    char new_path[1000];
                    snprintf(new_path, sizeof(new_path), "%s/%s", path, dir->d_name);

                    int subdir_result = traverse_directory(new_path,dir->d_name);
                    if (strcmp(operation, "add") == 0){
                        result +=subdir_result;
                    }
                    else if(strcmp(operation, "mul") == 0){
                        result*= subdir_result;
                    }
                }
            }
            else{
                if (strstr(dir->d_name,".txt")){
                    char copy_path[1000];
                    strcpy(copy_path, path);
                    char *token = strtok(copy_path, "/");
                    char *last_token = token;
                    while (token != NULL){
                        last_token = token;
                        token = strtok(NULL, "/");
                    }
                    char new_path[1000];
                    snprintf(new_path, sizeof(new_path), "%s/%s", path, dir->d_name);
                    if (strcmp(last_token, "add") == 0){
                        int res = count_numbers(new_path, "add");
                        result+=res;
                    }
                    else if (strcmp(last_token, "mul") == 0){
                        int res = count_numbers(new_path, "mul");
                        result*=res;
                    }
                }

            }
        }
        closedir(d);
    }
    return result;
}

int main(void) {
    char* first_directory = check_first_directory("tmp");
    int result = traverse_directory("tmp",
                                    first_directory);
    FILE *output = fopen("result.txt", "w");
    fprintf(output, "%d\n", result);
    fclose(output);

    return 0;
}