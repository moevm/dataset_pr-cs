#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
#include<string.h>
#include<ctype.h>

#define PATH_MX 512
#define STRING_MX 100

void read_dir(const char* file_path, const char* sentence, char file_strings[][PATH_MX]) {
	DIR* dir = opendir(file_path);

	struct dirent* dir_element = readdir(dir);

	while (dir_element) {
		if (dir_element->d_type == DT_DIR && strcmp(dir_element->d_name, ".") != 0 && strcmp(dir_element->d_name, "..") != 0) {
			char new_file_path[PATH_MX];
			sprintf(new_file_path, "%s/%s", file_path, dir_element->d_name);
			read_dir(new_file_path, sentence, file_strings);
		}
		else if (dir_element->d_type == DT_REG && strcmp(dir_element->d_name + 1, ".txt") == 0 && isalpha(dir_element->d_name[0])) {
			char letter = dir_element->d_name[0];
			for (int i = 0; sentence[i] != '\n'; i++) {
				if (letter == sentence[i]) {
					sprintf(file_strings[i], "%s/%s", file_path, dir_element->d_name);
				}
			}
		}

		dir_element = readdir(dir);
	}

	closedir(dir);
}

void write_file(const char* file_path, char file_strings[][PATH_MX], size_t size) {
	FILE* file = fopen(file_path, "w");

	if (!file) {
		printf("Error: couldn't open answer file!");
		exit(1);
	}

	for (int i = 0; i < size; i++) {
		fprintf(file, "%s\n", file_strings[i]);
	}
	fclose(file);
}

int main() {
	char sentence[STRING_MX];
	fgets(sentence, STRING_MX, stdin);

	char file_strings[strlen(sentence) - 1][PATH_MX];
	char path[PATH_MX];

	strcpy(path, "./tmp");

	read_dir(path, sentence, file_strings);

	write_file("./result.txt", file_strings, strlen(sentence) - 1);
	return 0;
}