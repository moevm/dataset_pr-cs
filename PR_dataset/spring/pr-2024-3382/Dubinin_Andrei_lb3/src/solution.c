#include <stdio.h>
#include <dirent.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

int process_directory(char *path, int operation);

int main() {
    DIR *dir = opendir("./tmp");
    FILE *f = fopen("result.txt", "w");
    
    if (dir) {
        struct dirent *object = readdir(dir);
        while (object) {
            if (strcmp(object->d_name, "add") == 0) {
                fprintf(f, "%d\n", process_directory("./tmp/add", 0));
                break;
            } else if (strcmp(object->d_name, "mul") == 0) {
                fprintf(f, "%d\n", process_directory("./tmp/mul", 1));
                break;
            }
            object = readdir(dir);
        }
        closedir(dir);
    }
    
    fclose(f);
    return 0;
}

int process_directory(char *path, int operation) {
    char *file_path;
    int file_path_len, sub_result;
    
    int result = operation;
    
    DIR *dir = opendir(path);
    if (dir) {
        struct dirent *object = readdir(dir);
        
        while (object) {
            if (strcmp(".", object->d_name) && strcmp("..", object->d_name)) {
                
                file_path_len = strlen(path) + strlen(object->d_name) + 2;          
                file_path = malloc(file_path_len * sizeof(char));            
                snprintf(file_path, file_path_len, "%s/%s", path, object->d_name);
                
                if (object->d_type == DT_DIR) {
                    if (strcmp(object->d_name, "mul") == 0)
                        sub_result = process_directory(file_path, 1);
                    else
                        sub_result = process_directory(file_path, 0);
    				
    				if (operation)
    				    result *= sub_result;
    				else
    				    result += sub_result;
    
                } else {
                    FILE *f = fopen(file_path, "r");

					char c;
					char num[100];
					size_t num_len = 0;
					while ((c = fgetc(f)) != EOF) {
						if (!isdigit(c) && c != '-') {
							num[num_len] = '\0';
							int int_num = atoi(num);
							result  = (operation) ? (result * int_num) : (result + int_num);
							num_len = 0;
						}
						num[num_len ++] = c;
					}
                    fclose(f);
                }
                
                free(file_path);
            }
            object = readdir(dir);
        }
    }
    closedir(dir);
    return result;
}

