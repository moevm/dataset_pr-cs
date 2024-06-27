#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

enum
{
	OPTYPE_UNKNOWN = 0,
	OPTYPE_ADD,
	OPTYPE_MUL
};

int string_to_operation_type(const char *str)
{
	if (strcmp(str, "add") == 0) return OPTYPE_ADD;
	if (strcmp(str, "mul") == 0) return OPTYPE_MUL;
	return OPTYPE_UNKNOWN;
}

int do_operation(int operation_type, int operand1, int operand2)
{
	switch (operation_type) {
		case OPTYPE_ADD: return operand1 + operand2;
		case OPTYPE_MUL: return operand1 * operand2;
		default:		 return operand1;
	}
}

int get_neutral_value(int operation_type)
{
	switch (operation_type) {
		case OPTYPE_ADD: return 0;
		case OPTYPE_MUL: return 1;
		default:		 return 0;
	}
}

int evaluate_file(const char* path, int operation_type)
{
	FILE *file = fopen(path, "r");
	int result = get_neutral_value(operation_type);
	int tmp    = 0;

	if (file == NULL)
		return INT_MAX;

	while (fscanf(file, "%d", &tmp) != EOF) {
		result = do_operation(operation_type, result, tmp);
	}

	return result;
}

int evaluate_directory(const char *path)
{
	DIR *dir;
	struct dirent *entry;
	int operation_type;
	int result;

	if (chdir(path) != 0)
		return INT_MAX;
	
	dir = opendir(".");
	if (dir == NULL) {
		chdir("..");
		return INT_MAX;
	}

	operation_type = string_to_operation_type(path);
	if (operation_type == OPTYPE_UNKNOWN) {
		chdir("..");
		return INT_MAX;
	}


	result = get_neutral_value(operation_type);

	entry = readdir(dir);
	while (entry != NULL) {
		int entry_value = get_neutral_value(operation_type);

		switch (entry->d_type) {
			case DT_REG:
				entry_value = evaluate_file(entry->d_name, operation_type);
				break;
			case DT_DIR:
				if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
					break;
					
				entry_value = evaluate_directory(entry->d_name);
				break;
		}

		if (entry_value == INT_MAX) {
			chdir("..");
			closedir(dir);
			return INT_MAX;
		}
			
		result = do_operation(operation_type, result, entry_value);	
		entry = readdir(dir);
	}

	chdir("..");
	closedir(dir);
	return result;
}

int main()
{
	FILE *out_file;
	DIR  *root;
	struct dirent *entry;

	out_file = fopen("result.txt", "w");
	if (out_file == NULL)
		return 1;

	chdir("tmp");
	root = opendir(".");
	if (root == NULL) {
		fclose(out_file);
		return 1;
	}

	entry = readdir(root);
	while (entry != NULL) {	
		int operation_type = string_to_operation_type(entry->d_name);
		if (entry->d_type == DT_DIR && operation_type != OPTYPE_UNKNOWN) {
			fprintf(out_file, "%d\n", evaluate_directory(entry->d_name));

			fclose(out_file);
			closedir(root);
			return 0;
		}

		entry = readdir(root);
	}

	fclose(out_file);
	closedir(root);
	return 1;
}
