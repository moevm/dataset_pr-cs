#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>
#define PATH_NAME 512
#define DOT "."
#define DOUBLE_DOT ".."
#define READ "r"
#define WRITE "w+"
#define START_DIR ".//tmp"
#define ADD "add"
#define MUL "mul"
#define RESULT "result.txt"

int add_func(const char* path);
int sum(const char* path);
int mul_func(const char* path);
int mult(const char* path);

int process_directory(const char* path) {
	DIR *direct;
	direct = opendir(path);
	struct dirent *way;
	char pathToOp[PATH_NAME];
	int result;
	if (!direct) return 0;
	while((way = readdir(direct)) != NULL) {
		if (strcmp(way->d_name, DOT) == 0 || strcmp(way->d_name, DOUBLE_DOT) == 0) {
			continue;
		}
		sprintf(pathToOp, "%s//%s", path, way->d_name);
		if (strcmp(way->d_name, ADD) == 0) {
			result = add_func(pathToOp);
			continue;
		}
		else if (strcmp(way->d_name, MUL) == 0) {
			result = mul_func(pathToOp);
			continue;
		}
	}
	closedir(direct);
	return result;
}
int add_func(const char* path) {
	DIR *direct;
	direct = opendir(path);
	struct dirent *way;
	int result = 0;
	char nextPath[PATH_NAME];
	if (!direct) return 0;
	while((way = readdir(direct)) != NULL) {
		if (strcmp(way->d_name, DOT) == 0 || strcmp(way->d_name, DOUBLE_DOT) == 0) {
			continue;
		}	
		sprintf(nextPath, "%s//%s", path, way->d_name);
		if (way->d_type == DT_REG) {
			result += sum(nextPath);
			continue;
		}
		if (strcmp(way->d_name, ADD) == 0) {
			result += add_func(nextPath);
			continue;
		}
		else if (strcmp(way->d_name, MUL) == 0) {
			result += mul_func(nextPath);
			continue;
		}
	}
	closedir(direct);
	return result;
}
int mul_func(const char* path) {
	DIR *direct;
	direct = opendir(path);
	struct dirent *way;
	int result = 1;
	char nextPath[PATH_NAME];
	if (!direct) return 0;
	while((way = readdir(direct)) != NULL) {
		if (strcmp(way->d_name, DOT) == 0 || strcmp(way->d_name, DOUBLE_DOT) == 0) {
			continue;
		}
		sprintf(nextPath, "%s//%s", path, way->d_name);
		if (way->d_type == DT_REG) {
			result *= mult(nextPath);
			continue;
		}
		if (strcmp(way->d_name, ADD) == 0) {
			result *= add_func(nextPath);
			continue;
		}
		else if (strcmp(way->d_name, MUL) == 0) {
			result *= mul_func(nextPath);
			continue;
		}
	}
	closedir(direct);
	return result;
}
int sum(const char* path) {
	FILE *file;
	file = fopen(path, READ);
	int result = 0;
    int number_in_file;
	while(fscanf(file, "%d", &number_in_file) == 1) {
		result += number_in_file;
	}
	fclose(file);
	return result;
}
int mult(const char* path) {
	FILE *file;
	file = fopen(path, READ);
	int result = 1;
    int number_in_file;
	while (fscanf(file, "%d", &number_in_file) == 1) {
		result *= number_in_file;
	}
	fclose(file);
	return result;
}
int main() {
	int result = process_directory(START_DIR);
	FILE *file;
	file = fopen(RESULT, WRITE);
	fprintf(file, "%d", result);	
	fclose(file);
	return 0;
}
