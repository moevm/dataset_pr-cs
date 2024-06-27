#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/types.h>

#define PATH_NAME 512

int add(const char* path);
int summary(const char* path);
int mul(const char* path);
int multiply(const char* path);

int operation(const char* path) {
	DIR *dir;
	dir = opendir(path);
	struct dirent *entry;
	char pathToOp[PATH_NAME];
	int result;
	if (!dir) return 0;
	while((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		sprintf(pathToOp, "%s//%s", path, entry->d_name);
		if (strcmp(entry->d_name, "add") == 0) {
			result = add(pathToOp);
			continue;
		}
		if (strcmp(entry->d_name, "mul") == 0) {
			result = mul(pathToOp);
			continue;
		}
	}
	closedir(dir);
	return result;
}

int add(const char* path) {
	DIR *dir;
	dir = opendir(path);
	struct dirent *entry;
	int result = 0;
	char nextPath[PATH_NAME];
	if (!dir) return 0;
	while((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}	
		sprintf(nextPath, "%s//%s", path, entry->d_name);
		printf("%s\n", nextPath);
		if (entry->d_type == DT_REG) {
			result += summary(nextPath);
			printf("%d -- FILE\n", result);
			continue;
		}
		if (strcmp(entry->d_name, "add") == 0) {
			result += add(nextPath);
			printf("%d -- add\n", result);
			continue;
		}
		if (strcmp(entry->d_name, "mul") == 0) {
			result += mul(nextPath);
			printf("%d -- mul\n", result);
			continue;
		}
	}
	//printf("%d\n", result);
	closedir(dir);
	return result;
}

int mul(const char* path) {
	DIR *dir;
	dir = opendir(path);
	struct dirent *entry;
	int result = 1;
	char nextPath[PATH_NAME];
	if (!dir) return 0;
	while((entry = readdir(dir)) != NULL) {
		if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
			continue;
		}
		sprintf(nextPath, "%s//%s", path, entry->d_name);
		if (entry->d_type == DT_REG) {
			result *= multiply(nextPath);
			continue;
		}
		if (strcmp(entry->d_name, "add") == 0) {
			result *= add(nextPath);
			continue;
		}
		if (strcmp(entry->d_name, "mul") == 0) {
			result *= mul(nextPath);
			continue;
		}
	}
	closedir(dir);
	return result;
}

int summary(const char* path) {
	FILE *file;
	file = fopen(path, "r");
	int result = 0, num;
	while(fscanf(file, "%d", &num) == 1) {
		result += num;
	}
	fclose(file);
	return result;
}

int multiply(const char* path) {
	FILE *file;
	//printf("%s\n", path);
	file = fopen(path, "r");
	int result = 1, num;
	while (fscanf(file, "%d", &num) == 1) {
		result *= num;
	}
	//printf("%d\n", result);
	fclose(file);
	return result;
}


int main() {
	int result = operation(".//tmp");
	FILE *file;
	file = fopen("result.txt", "w+");
	fprintf(file, "%d", result);	
	fclose(file);
	return 0;
}
