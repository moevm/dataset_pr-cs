#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define MUL 1
#define ADD 2
#define SIZE_NAME_DIR 1000

#define LINK_PARRENT_DIR "."
#define LINK_CURRENT_DIR ".."
#define ADD_DIR "add"
#define MUL_DIR "mul"

int operation_file(char* file_name, int check_operation) {
	FILE* file = fopen(file_name, "r");
	int number = 0;
	int result = 0;
	if (check_operation == ADD) {
		while (fscanf(file, "%d", &number) == 1) {
			result += number;
		}
	}
	else {
		result = 1;
		while (fscanf(file, "%d", &number) == 1) {
			result *= number;
		}
	}
	fclose(file);
	return result;
}

int operation(const char* name_dir, int check_operation) {
	DIR* dir = opendir(name_dir);
	struct dirent* de = readdir(dir);
	int result = 0;
	if (check_operation == MUL) {
		result = 1;
	}
	int result_iteration = 0;
	int check_iteration;
	while (de) {
		check_iteration = 0;
		if (de->d_type == DT_DIR && strcmp(de->d_name, LINK_PARRENT_DIR) != 0 && strcmp(de->d_name, LINK_CURRENT_DIR) != 0) {
			char subdir_name[SIZE_NAME_DIR];
			sprintf(subdir_name, "%s/%s", name_dir, de->d_name);
			if (strcmp(de->d_name, ADD_DIR) == 0) {
				result_iteration = operation(subdir_name, ADD);
				check_iteration = 1;
			}
			if (strcmp(de->d_name, MUL_DIR) == 0) {
				result_iteration = operation(subdir_name, MUL);
				check_iteration = 1;
			}
		}
		if (de->d_type == DT_REG) {
			char file_name[1000];
			sprintf(file_name, "%s/%s", name_dir, de->d_name);
			result_iteration = operation_file(file_name, check_operation);
			check_iteration = 1;
		}
		if (check_iteration) {
			if (check_operation == 0) {
				return result_iteration;
			}
			if (check_operation == ADD) {
				result += result_iteration;
			}
			else {
				result = result * result_iteration;
			}
		}
		de = readdir(dir);
	}
	closedir(dir);
	return result;
}

void result_to_file(int result) {
	FILE* result_file = fopen("/home/box/result.txt", "w");
	fprintf(result_file, "%d", result);
	fclose(result_file);
}

int main() {
	const char* name_first_dir = "./tmp";
	int result = 0;
	result = operation(name_first_dir, 0);
	result_to_file(result);
	return 0;
}
