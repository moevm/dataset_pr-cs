#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <stdlib.h>

#define PATH                "./tmp"   // обрабатываемая директория
#define MAX_FILES           3000      // макисмальное количество файлов в директории
#define ONECHAR_FNAME_LEN   5         // длина имени файла с именем из одного символа
#define INPUT_STR_SIZE      100       // размер строки, подаваемой на вход программе
#define DIR_FILE_TYPE       4         // номер типа массива

#define SUCCESS             0         // флаг удачного нахождения путей к каждому символу строки
#define FAILURE             1         // флаг неудачи операции выше

typedef struct FileInfo {
	char *fname;
	char *fpath;
} FileInfo;

FileInfo **fsarr;
size_t fsarr_len;

FileInfo **result;
size_t result_len;

// компаратор для быстрой сортировки массива FileInfo
int qsort_cmp(const void *arg1, const void *arg2)
{
	char *name1 = (*((FileInfo**)arg1))->fname;
	char *name2 = (*((FileInfo**)arg2))->fname;

	return strcmp(name1, name2);
}

// компаратор для бинарного поиска имени файла в массиве FileInfo
int binsrch_cmp(const void *key, const void *fname)
{
	const char *name1 = (char*)key;
	const char *name2 = (*((FileInfo**)fname))->fname;

	return strcmp(name1, name2);
}

// сохраняет пути ко всем файлам директории и имена этих файлов в массив структур FileInfo
void index_directory(const char *dirPath)
{
	DIR *dir = opendir(dirPath);

	char *file_path; 
	int file_path_len;                                                                                                                                   

	if (dir) {
		struct dirent *de = readdir(dir);                                           

		while (de) {
			if (strcmp(".", de->d_name) && strcmp("..", de->d_name)) {
				// цифра 2 в длине - память под / и символ конца строки
				file_path_len = strlen(dirPath) + strlen(de->d_name) + 2;          
                file_path = (char*)malloc(file_path_len * sizeof(char));            
                snprintf(file_path, file_path_len, "%s/%s", dirPath, de->d_name);
				
				if (de->d_type == DIR_FILE_TYPE) {
					index_directory(file_path);                  
					free(file_path);
				}
				else if (strlen(de->d_name) == ONECHAR_FNAME_LEN) {
					// заполняем структуру информации о файле
					fsarr[fsarr_len] = (FileInfo*)malloc(sizeof(FileInfo));
					fsarr[fsarr_len]->fpath = file_path;
					fsarr[fsarr_len]->fname = (char*)malloc((ONECHAR_FNAME_LEN + 1) * sizeof(char));
					strcpy(fsarr[fsarr_len]->fname, de->d_name);

					fsarr_len++;
				}
				else {
					free(file_path);
				}
			}
			de = readdir(dir);                                                  
		}
	}
	closedir(dir);                                                                     
}

int main()
{
	// входная строка, считывание и её длина
	char *input = (char*)malloc(INPUT_STR_SIZE * sizeof(char));
	fgets(input, INPUT_STR_SIZE, stdin);
	// если на конце строки \n - убираем его
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	size_t input_len = strlen(input);

	// массив FileInfo для хранения имён и путей к файлам
	fsarr = (FileInfo**)malloc(MAX_FILES * sizeof(FileInfo*));
	fsarr_len = 0;

	// массив FileInfo для хранения результата выполнения программы
	result = (FileInfo**)malloc(input_len * sizeof(FileInfo*));
	result_len = 0;

	index_directory(PATH);
 	
	// сортируем массив fsarr для бинарного поиска
	qsort(fsarr, fsarr_len, sizeof(FileInfo*), qsort_cmp);

	FileInfo **file;
	int flag = SUCCESS;
	char *file_name = (char*)malloc(ONECHAR_FNAME_LEN * sizeof(char));

	for (size_t i = 0; i < input_len; i++) {
		snprintf(file_name, ONECHAR_FNAME_LEN + 1, "%c.txt", input[i]);
		file = (FileInfo**)bsearch(file_name, fsarr, fsarr_len, sizeof(FileInfo*), binsrch_cmp);
		if (file)
			result[result_len++] = *file;
		else {
			flag = FAILURE;
			break;
		}
	}

	if (flag == SUCCESS) {
		FILE *resp = fopen("result.txt", "w");
		for (size_t i = 0; i < result_len; i++) {
			fputs(result[i]->fpath, resp);
			fputs("\n", resp);
		}
		fclose(resp);
	}
	else
		printf("Some symbol was not found\n");

	// очищаем выделенную в ходе программы динамическую память
	for (size_t i = 0; i < fsarr_len; i++) {
		free(fsarr[i]->fname);
		free(fsarr[i]->fpath);
		free(fsarr[i]);
	}
	free(fsarr);
	free(result);
	free(input);
	free(file_name);
	
	return 0;
}
