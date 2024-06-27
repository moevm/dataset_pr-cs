#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

#define BUF 64

int cmp_by_number(const void *a, const void *b)
{
    const char *f_line = *(const char **)a;
	const char *s_line = *(const char **)b;
    long f_num = atol(f_line);
	long s_num = atol(s_line);
	if (f_num - s_num > 0)
		return 1;
	if (f_num - s_num < 0)
		return -1;
	return 0;
}

void check_file(char *filename, char ***str_list, int *str_count)
{
    FILE *file = fopen(filename, "r");
    char *line = (char *)malloc(BUF);
	char *tmp_line = (char *)malloc(BUF);
    fgets(line, BUF, file);
    while (fgets(tmp_line, BUF, file)) {
		line = (char *)realloc(line, strlen(line) + strlen(tmp_line) + 1);
		strcat(line, tmp_line);
	}
    (*str_list)[*str_count-1] = line;
	free(tmp_line);
	free(filename);
	fclose(file);
}

void check_dir(char *path, char ***str_list, int *str_count)
{
	DIR *dir = opendir(path);
	if (dir) {
		struct dirent *obj;
		while (obj = readdir(dir)) {
			char *obj_name = obj->d_name;
			if (!strcmp(obj_name, "..") || !strcmp(obj_name, ".") || !strcmp(obj_name, "result.txt")) {
				continue;
			}
			if (obj->d_type == DT_DIR) {
				char *new_path = (char *)malloc(strlen(path) + strlen(obj->d_name) + 2);
				sprintf(new_path, "%s/%s", path, obj->d_name);
				check_dir(new_path, str_list, str_count);
				free(new_path);
			}
			if (obj->d_type == DT_REG && strstr(obj_name, ".txt")) {
				if (*str_count == 0) {
					*str_list = (char **)malloc((++(*str_count)) * sizeof(char *));
				} else {
					*str_list = (char **)realloc(*str_list, (++(*str_count)) * sizeof(char *));
				}
				char *filename = (char *)malloc(strlen(path) + strlen(obj_name) + 2);
				sprintf(filename, "%s/%s", path, obj_name);
				check_file(filename, str_list, str_count);
			}
		}
	}
	closedir(dir);
}

int main()
{
	char **str_list = NULL;
	int str_count = 0;
	check_dir(".", &str_list, &str_count);
	qsort(str_list, str_count, sizeof(char*), cmp_by_number);
	FILE *res = fopen("result.txt", "w");
	for (int i = 0; i < str_count; i++) {
		fprintf(res, "%s\n", str_list[i]);
		free(str_list[i]);
	}
	free(str_list);
	fclose(res);
	return 0;
}