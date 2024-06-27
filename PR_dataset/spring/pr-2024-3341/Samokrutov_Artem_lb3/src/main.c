#include <sys/types.h>
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *pathcat(const char *path1, const char *path2);
long long int add(const char *);
long long int mul(const char *);
int is_child_dir(const struct dirent *);
int is_txt_file(const struct dirent *);
void assign_dir(const char *, const struct dirent *, long long int *);
void add_file(const char *, const struct dirent *, long long int *);
void mul_file(const char *, const struct dirent *, long long int *);
void add_dir(const char *, const struct dirent *, long long int *);
void mul_dir(const char *, const struct dirent *, long long int *);
void process_dir(const char *, long long int *);
void dir_error_check(DIR *);
void file_error_check(FILE *);
void write_ans(const long long int);


long long int main() {
	long long int res = 0;
	process_dir("./tmp", &res);
	write_ans(res);
	return 0;
}

char *pathcat(const char *path1, const char *path2) {
	long long int res_path_len = strlen(path1) + strlen(path2) + 2;
	char *res_path = (char *)malloc(res_path_len * sizeof(char));
	sprintf(res_path, "%s/%s", path1, path2);

	return res_path;
}

long long int add(const char *dir_name) {
	long long int sum = 0;
	
	DIR *dir = opendir(dir_name);

	dir_error_check(dir);
	
	struct dirent *de = readdir(dir);
	while ((de) != NULL) {
		if (is_child_dir(de)) {
			add_dir(dir_name, de, &sum);
		} else if (is_txt_file(de)) {
			add_file(dir_name, de, &sum);
		}
		de = readdir(dir);
	}
	
	closedir(dir);
	
	return sum;
}

long long int mul(const char *dir_name) {
	long long int prod = 1;

	DIR *dir = opendir(dir_name);

	dir_error_check(dir);
	
	struct dirent *de = readdir(dir);
	while ((de) != NULL) {
		if (is_child_dir(de)) {
			mul_dir(dir_name, de, &prod);
		} else if (is_txt_file(de)) {
			mul_file(dir_name, de, &prod);
		}
		
		de = readdir(dir);
	}
	
	closedir(dir);
	
	return prod;
}

int is_child_dir(const struct dirent *de) {
	if (de->d_type == DT_DIR)
        	return (strcmp(de->d_name, ".") != 0 && strcmp(de->d_name, ".."));
	else
        	return 0;
}

int is_txt_file(const struct dirent *de) {
	if (de->d_type == DT_REG)
        	return (strstr(de->d_name, ".txt") != NULL);
	else 
		return 0;
}

void assign_dir(const char *path, const struct dirent *de, long long int *res) {
    char *dir_name = pathcat(path, de->d_name);
    
	if (strcmp(de->d_name, "add") == 0) {
		*res = add(dir_name);
	} else if (strcmp(de->d_name, "mul") == 0) {
		*res = mul(dir_name);
	}
	
	free(dir_name);
}

void add_file(const char *dir_name, const struct dirent *de, long long int *sum) {
	long long int contents;
	
	char *file_name = pathcat(dir_name, de->d_name);
	FILE *file = fopen(file_name, "r");
	
	file_error_check(file);
	
	while (fscanf(file, "%lli", &contents) == 1) {
		*sum += contents;
	}
	fclose(file);
}

void mul_file(const char *dir_name, const struct dirent *de, long long int *prod) {
	long long int contents;
	
	char *file_name = pathcat(dir_name, de->d_name);
	FILE *file = fopen(file_name, "r");
	
	file_error_check(file);
	
	while (fscanf(file, "%lli", &contents) == 1) {
		*prod *= contents;
	}
	
	fclose(file);
}

void add_dir(const char *path, const struct dirent *de, long long int *sum) {
	char *dir_name = pathcat(path, de->d_name);
	
	if (strcmp(de->d_name, "add") == 0) {
		*sum += add(dir_name);
	} else if (strcmp(de->d_name, "mul") == 0) {
		*sum += mul(dir_name);
	}
	
	free(dir_name);
}

void mul_dir(const char *path, const struct dirent *de, long long int *prod) {
	char *dir_name = pathcat(path, de->d_name);
	
	if (strcmp(de->d_name, "add") == 0) {
		*prod *= add(dir_name);
	} else if (strcmp(de->d_name, "mul") == 0) {
		*prod *= mul(dir_name);
	}
	
	free(dir_name);
}

void process_dir(const char *dir_name, long long int *res) {
	DIR *dir = opendir(dir_name);

	dir_error_check(dir);

	struct dirent *de = readdir(dir);
	while ((de) != NULL) {
		if (is_child_dir(de)) {
		    assign_dir(dir_name, de, res);
		}
		
		de = readdir(dir);
	}

	closedir(dir);
}

void dir_error_check(DIR *dir) {
	if (dir == NULL) {
		puts("Error accessing a directory...\n");
		exit(1);
	}
}

void file_error_check(FILE *file) {
	if (file == NULL) {
        	puts("Error opening a file...\n");
        	exit(1);
    	}
}

void write_ans(const long long int res) {
	FILE *file = fopen("result.txt", "w");
	file_error_check(file);

	fprintf(file, "%lli", res);

	fclose(file);
}
