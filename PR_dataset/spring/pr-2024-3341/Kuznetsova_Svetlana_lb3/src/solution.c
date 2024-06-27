#include <stdio.h>
#include <dirent.h>
#include <string.h>

#define length 500
#define dot '.'


void find_name(FILE *result, char str, const char *dirPath);

int main() {

	const char *directory = "./tmp";
	const char firstpath[] = "./result.txt";

	int i = 0;
	char word[length];
	scanf("%s", word);

	FILE *result = fopen(firstpath, "w");

	while (word[i]) {
		find_name(result, word[i], directory);
		i++;
	}

	fclose(result);
}

int nec_letter(char* d_name, char letter) {
	return (d_name[0] == letter) && (d_name[1] == dot);
}

void find_name(FILE* result, char letter, const char *directory) {
	if (result) {
		DIR *dir = opendir(directory);
		if (dir) {
			struct dirent *entry = readdir(dir);
			while (entry) {
				char path[length];
				sprintf(path, "%s/%s", directory, entry->d_name);

				if (entry->d_type == DT_DIR && entry->d_name[0] != dot) {
					find_name(result, letter, path);
				}

				if (entry->d_type == DT_REG && nec_letter(entry->d_name, letter)) {
					fprintf(result, "%s\n", path);
				}

				entry = readdir(dir);
			}
		}
		closedir(dir);
	}
}