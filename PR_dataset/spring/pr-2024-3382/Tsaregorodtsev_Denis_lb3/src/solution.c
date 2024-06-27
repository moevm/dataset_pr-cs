#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define PATH "./tmp"
#define MAX_FILES 3000

enum operation {
	ADD = 1,
	MUL = 2
};

int find_sum(const char *dirPath, enum operation op)
{
	char* file_path;
	int file_path_len;

	int result = (op == ADD) ? 0 : 1;

	DIR *dir = opendir(dirPath);
	if (dir) {
		struct dirent *de = readdir(dir);
                                           
		while (de) {
			if (strcmp(".", de->d_name) && strcmp("..", de->d_name)) {
			
				file_path_len = strlen(dirPath) + strlen(de->d_name) + 2;          
    		file_path = (char*)malloc(file_path_len * sizeof(char));            
      	snprintf(file_path, file_path_len, "%s/%s", dirPath, de->d_name);

				if (de->d_type == DT_DIR) {
					int new_operation = (!strcmp(de->d_name, "add")) ? ADD : MUL;
					int ret = find_sum(file_path, new_operation);
					result = (op == ADD) ? (result + ret) : (result * ret);
					
				} else {
					FILE *fd = fopen(file_path, "r");

					char c;
					char num[100];
					size_t num_len = 0;
					while ((c = fgetc(fd)) != EOF) {
						if (!isdigit(c) && c != '-') {
							num[num_len] = '\0';
							int int_num = atoi(num);
							result  = (op == ADD) ? (result + int_num) : (result * int_num);
							num_len = 0;
						}
						num[num_len++] = c;
					}
				}

				free(file_path);
			}
			de = readdir(dir);                                                  
		}
	}
	closedir(dir);

	return result;
}

int main()
{
	DIR *cdir = opendir(PATH);
	enum operation op;

	FILE *fd = fopen("result.txt", "w");
	
	if (cdir) {
		struct dirent *de = readdir(cdir);
		while (de) {
			if (!strcmp(de->d_name, "add")) {
				op = ADD;
				fprintf(fd, "%d\n", find_sum("./tmp/add", op));
				break;
			} else if(!strcmp(de->d_name, "mul")) {
				op = MUL;
				fprintf(fd, "%d\n", find_sum("./tmp/mul", op));
				break;
			}
			de = readdir(cdir);
		}
		closedir(cdir);
	}

	fclose(fd);
	return 0;
}
